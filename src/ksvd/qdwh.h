#ifndef _QDWH_H_
#define _QDWH_H_

void pdgenm2( double *A, int M, int N, int descA[9], double *W, int descW[9], double *Sx, int descSx[9], double *e, double tol);
int pdgeqdwh( char *jobh, int m, int n,
	      double *A, int iA, int jA, int *descA, 
              double *H, int iH, int jH, int *descH,
              double *Work1, int lWork1, 
              double *Work2, int lWork2, 
              int *info);

#endif
