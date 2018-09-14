#include <R.h>
#include <Rinternals.h>

#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
#define FREE(x) if(x)free(x)
#define MIN(a,b) ((a)<(b)?(a):(b))
#define IJ 1


// NOTE: always return 0
int pdgeqsvd(const char *const restrict jobu, const char *const restrict jobvt,  const char *const restrict eigtype, 
  const int m, const int n, 
  double *const restrict A, const int iA, const int jA, const int *const restrict descA, 
  double *const restrict S, 
  double *const restrict U,     const int iU, const int jU, const int *const restrict descU,
  double *const restrict VT,    const int iVT, const int jVT, const int *const restrict descVT,
  double *const restrict Work,  const int lWork,
  int    *const restrict iWork, const int liWork, int *const restrict info);


void Cblacs_get(int, int, int*);
void Cblacs_gridinit(int *ConTxt, char *order, int nprow, int npcol);


SEXP R_pdgeqsvd(SEXP JOBU, SEXP JOBVT, SEXP EIGTYPE, SEXP A, SEXP DESCA, SEXP DESCU, SEXP DESCVT, SEXP LDIM_U, SEXP LDIM_VT)
{
  int ictxt = 0;
  char order = 'R';
  Cblacs_get(-1, 0, &ictxt);
  Cblacs_gridinit(&ictxt, &order, 1, 1);
  
  
  
  SEXP ret, retnames;
  SEXP S, U, VT;
  double *a, *u, *vt;
  int info = 0;
  double *work;
  int *iwork;
  int lwork, liwork = 0;
  
  
  const char jobu = CHARPT(JOBU, 0)[0];
  const char jobvt = CHARPT(JOBVT, 0)[0];
  const char eigtype = CHARPT(EIGTYPE, 0)[0];
  const int *const restrict desca = INTEGER(DESCA);
  const int *const restrict descu = INTEGER(DESCU);
  const int *const restrict descvt = INTEGER(DESCVT);
  const int m = desca[2];
  const int n = desca[3];
  
  int ptct = 3;
  PROTECT(ret = allocVector(VECSXP, 3));
  PROTECT(retnames = allocVector(STRSXP, 3));
  PROTECT(S = allocVector(REALSXP, MIN(m, n)));
  
  
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
  
  printf("%d\n", info);
  
  free(work);
  free(iwork);
  free(a);
  
  UNPROTECT(ptct);
  if (info != 0)
    error("pdgeqsvd returned error code %d\n", info);
  
  return ret;
}
