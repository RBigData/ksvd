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
#' @param A
#' TODO
#' @param desca,descu,descvt
#' TODO
#' 
#' @return 
#' TODO
#' 
#' @export
rpdgeqsvd = function(jobu, jobvt, A, desca, descu, descvt)
{
  .Call("R_pdgeqsvd", jobu, jobvt, A, desca, descu, descvt)
}