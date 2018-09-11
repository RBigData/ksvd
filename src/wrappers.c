#include <R.h>
#include <Rinternals.h>

#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
#define FREE(x) (if(x)free(x))

#define IJ 1

// NOTE: always return 0
int pdgeqsvd( char *jobu, char *jobvt, char *eigtype, 
              int m, int n, 
              double *A, int iA, int jA, int *descA, 
              double *S, 
              double *U,     int iU,     int jU, int *descU,
              double *VT,    int iVT,    int jVT, int *descVT,
              double *Work,  int lWork,
              int    *iWork, int liWork, int *info);


SEXP R_pdgeqsvd(SEXP JOBU, SEXP JOBVT, SEXP A, SEXP DESCA, SEXP DESCU, SEXP DESCVT)
{
  SEXP ret, retnames;
  SEXP S, U, VT;
  int m, n;
  char jobu, jobvt, eigtype;
  int info = 0;
  double *work;
  int lwork;
  int *liwork;
  int liwork;
  
  jobu = CHARPT(JOBU, 0)[0];
  jobvt = CHARPT(JOBVT, 0)[0];
  
  PROTECT(ret = allocVector(VECSXP, 3));
  PROTECT(retnames = allocVector)
  
  PROTECT(S = allocVector(REALSXP, ));
  PROTECT(U = allocMatrix(REALSXP, , ));
  PROTECT(VT = allocMatrix(REALSXP, , ));
  
  
  double work_dbl;
  pdgeqsvd(&jobu, &jobvt, &eigtype, m, n, 
    REAL(A), IJ, IJ, desc,
    S, 
    U, IJ, IJ, descu,
    VT, IJ, IJ, descvt,
    &work_dbl, -1, &liwork, -1, &info);
  
  lwork = (int) work_dbl;
  work = malloc(lwork * sizeof(*work));
  iwork = malloc(liwork * sizeof(*iwork));
  if (work == NULL || iwork == NULL)
  {
    FREE(work);
    FREE(iwork);
    
    SET_VECTOR_ELT(ret, 0, R_NilValue);
    SET_VECTOR_ELT(ret, 1, R_NilValue);
    SET_VECTOR_ELT(ret, 2, R_NilValue);
    
    UNPROTECT(5);
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
  
  pdgeqsvd(&jobu, &jobvt, &eigtype, m, n, 
    REAL(A), IJ, IJ, desc,
    S, 
    U, IJ, IJ, descu,
    VT, IJ, IJ, descvt,
    work, lwork, iwork, liwork, &info);
  
  UNPROTECT(5);
  return ret;
}
