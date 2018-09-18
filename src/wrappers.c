#include <R.h>
#include <Rinternals.h>
#include "wrappers.h"


static inline void rev_vec(const int len, double *const restrict x)
{
  int j = len-1;
  
  for (int i=0; i<len/2; i++)
  {
    const double tmp = x[i];
    x[i] = x[j];
    x[j] = tmp;
    j--;
  }
}



SEXP R_pdgeqsvd(SEXP JOBU, SEXP JOBVT, SEXP EIGTYPE, SEXP A, SEXP DESCA, SEXP DESCU, SEXP DESCVT, SEXP LDIM_U, SEXP LDIM_VT)
{
  SEXP ret, retnames;
  SEXP S, U, VT;
  double *a, *u, *vt;
  int info = 0;
  double *work;
  int *iwork;
  int lwork, liwork = 0;
  
  get_BLACS_APTS_from_R();
  
  const char jobu = CHARPT(JOBU, 0)[0];
  const char jobvt = CHARPT(JOBVT, 0)[0];
  const char eigtype = CHARPT(EIGTYPE, 0)[0];
  const int *const restrict desca = INTEGER(DESCA);
  const int *const restrict descu = INTEGER(DESCU);
  const int *const restrict descvt = INTEGER(DESCVT);
  const int m = desca[2];
  const int n = desca[3];
  const int min_mn = MIN(m, n);
  
  int ptct = 3;
  PROTECT(ret = allocVector(VECSXP, 3));
  PROTECT(retnames = allocVector(STRSXP, 3));
  PROTECT(S = allocVector(REALSXP, min_mn));
  
  
  if (jobu == 'V' || jobu == 'v')
  {
    PROTECT(U = allocMatrix(REALSXP, INTEGER(LDIM_U)[0], INTEGER(LDIM_U)[1]));
    u = REAL(U);
    ptct++;
  }
  else
  {
    U = R_NilValue;
    u = NULL;
  }
  
  if (jobvt == 'V' || jobvt == 'v')
  {
    PROTECT(VT = allocMatrix(REALSXP, INTEGER(LDIM_VT)[0], INTEGER(LDIM_VT)[1]));
    vt = REAL(VT);
    ptct++;
  }
  else
  {
    VT = R_NilValue;
    vt = NULL;
  }
  
  double lwork_dbl;
  pdgeqsvd(&jobu, &jobvt, &eigtype, m, n, 
    NULL, IJ, IJ, desca,
    REAL(S), 
    u, IJ, IJ, descu,
    vt, IJ, IJ, descvt,
    &lwork_dbl, -1, &liwork, -1, &info);
  
  lwork = (int) lwork_dbl;
  work = malloc(lwork * sizeof(*work));
  iwork = malloc(liwork * sizeof(*iwork));
  const size_t len_a = (size_t) nrows(A)*ncols(A);
  a = malloc(len_a * sizeof(*a));
  
  if (work == NULL || iwork == NULL || a == NULL)
  {
    FREE(work);
    FREE(iwork);
    FREE(a);
    
    SET_VECTOR_ELT(ret, 0, R_NilValue);
    SET_VECTOR_ELT(ret, 1, R_NilValue);
    SET_VECTOR_ELT(ret, 2, R_NilValue);
    
    UNPROTECT(ptct);
    return ret;
  }
  else
  {
    SET_VECTOR_ELT(ret, 0, S);
    SET_VECTOR_ELT(ret, 1, U);
    SET_VECTOR_ELT(ret, 2, VT);
  }
  
  SET_STRING_ELT(retnames, 0, mkChar("s"));
  SET_STRING_ELT(retnames, 1, mkChar("u"));
  SET_STRING_ELT(retnames, 2, mkChar("vt"));
  setAttrib(ret, R_NamesSymbol, retnames);
  
  memcpy(a, REAL(A), len_a*sizeof(*a));
  
  pdgeqsvd(&jobu, &jobvt, &eigtype, m, n, 
    a, IJ, IJ, desca,
    REAL(S), 
    u, IJ, IJ, descu,
    vt, IJ, IJ, descvt,
    work, lwork, iwork, liwork, &info);
  
  free(work);
  free(iwork);
  free(a);
  
  rev_vec(min_mn, REAL(S));
  
  UNPROTECT(ptct);
  if (info != 0)
    error("pdgeqsvd returned error code %d\n", info);
  
  return ret;
}
