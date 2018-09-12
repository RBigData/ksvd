#' rpdgeqsvd
#' 
#' TODO
#' 
#' @details
#' For advanced users only.
#' 
#' @param jobu
#' TODO
#' @param jobvt
#' TODO
#' @param eigtype
#' TODO
#' @param A
#' TODO
#' @param desca,descu,descvt
#' TODO
#' 
#' @return 
#' TODO
#' 
#' @export
rpdgeqsvd = function(jobu, jobvt, eigtype, A, desca, descu, descvt)
{
  if (jobu == 'V' || jobu == 'v')
    ldim_u = base.numroc(descu[3:4], descu[5:6], ICTXT=descu[2L])
  else
    ldim_u = c(-1L, -1L)
  
  if (jobvt == 'V' || jobvt == 'v')
    ldim_vt = base.numroc(descvt[3:4], descvt[5:6], ICTXT=descvt[2L])
  else
    ldim_vt = c(-1L, -1L)
  
  ldim_u = as.integer(ldim_u)
  ldim_vt = as.integer(ldim_vt)
  
  .Call(R_pdgeqsvd, jobu, jobvt, eigtype, A, desca, descu, descvt, ldim_u, ldim_vt)
}
