#ifndef KSVD_WRAPPERS_H_
#define KSVD_WRAPPERS_H_


#define CHARPT(x,i) ((char*)CHAR(STRING_ELT(x,i)))
#define FREE(x) if(x)free(x)
#define MIN(a,b) ((a)<(b)?(a):(b))
#define IJ 1


void get_BLACS_APTS_from_R();

// NOTE: always returns 0
int pdgeqsvd(const char *const restrict jobu, const char *const restrict jobvt,  const char *const restrict eigtype, 
  const int m, const int n, 
  double *const restrict A, const int iA, const int jA, const int *const restrict descA, 
  double *const restrict S, 
  double *const restrict U,     const int iU, const int jU, const int *const restrict descU,
  double *const restrict VT,    const int iVT, const int jVT, const int *const restrict descVT,
  double *const restrict Work,  const int lWork,
  int    *const restrict iWork, const int liWork, int *const restrict info);


#endif
