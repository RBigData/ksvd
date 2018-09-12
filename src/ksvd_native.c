/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP R_pdgeqsvd(SEXP JOBU, SEXP JOBVT, SEXP EIGTYPE, SEXP A, SEXP DESCA, SEXP DESCU, SEXP DESCVT, SEXP LDIM_U, SEXP LDIM_VT);

static const R_CallMethodDef CallEntries[] = {
  {"R_pdgeqsvd", (DL_FUNC) &R_pdgeqsvd, 9},
  {NULL, NULL, 0}
};

void R_init_ksvd(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
