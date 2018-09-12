#' Singular Value Decomposition
#' 
#' TODO
#' 
#' @details
#' TODO
#' 
#' @param x
#' numeric distributed matrix
#' @param nu
#' number of left singular vectors to return when calculating singular values.
#' @param nv 
#' number of right singular vectors to return when calculating singular values.
#' 
#' @return 
#' TODO
#' 
#' @export
ksvd = function(x,  nu = min(m, n), nv = min(m, n))
{
  m = nrow(x)
  n = ncol(x)
  min_mn = min(m, n)
  
  bldim = x@bldim
  ICTXT = x@ICTXT
  
  dim_a = dim(x)
  ldim_a = pbdBASE::base.numroc(dim=dim_a, bldim=bldim, ICTXT=ICTXT)
  desca = pbdBASE::base.descinit(dim_a, bldim, ldim_a, ICTXT)
  
  if (nu == 0)
  {
    jobu = 'N'
    dim_u = c(1L, 1L)
    ldim_u = c(-1L, -1L)
  }
  else
  {
    jobu = 'V'
    dim_u = c(m, min_mn)
    ldim_u = pbdBASE::base.numroc(dim=dim_u, bldim=bldim, ICTXT=ICTXT)
  }
  
  if (nv == 0)
  {
    jobvt = 'N'
    dim_vt = c(1L, 1L)
    ldim_vt = c(-1L, -1L)
  }
  else
  {
    jobvt = 'V'
    dim_vt = c(min_mn, n)
    ldim_vt = pbdBASE::base.numroc(dim=dim_vt, bldim=bldim, ICTXT=ICTXT)
  }
  
  descu = pbdBASE::base.descinit(dim_u, bldim, ldim_u, ICTXT)
  descvt = pbdBASE::base.descinit(dim_vt, bldim, ldim_vt, ICTXT)
  
  
  out = rpdgeqsvd(jobu, jobvt, eigtype='D', x@Data, desca, descu, descvt)
  
  
  if (nu > 0)
  {
    u = new("ddmatrix", Data=out$u, dim=dim_u, ldim=ldim_u, bldim=bldim, ICTXT=ICTXT)
    if (nu < u@dim[2L])
      u = u[, 1L:nu]
  }
  else
    u = NULL
  
  if (nv > 0)
  {
    vt = new("ddmatrix", Data=out$vt, dim=dim_vt, ldim=ldim_vt, bldim=bldim, ICTXT=ICTXT)
    if (nv < vt@dim[1L])
      vt = vt[1L:nv, ]
  }
  else
    vt = NULL
  
  ret = list(d=out$s)
  ret$u = u
  ret$vt = vt
  
  ret
}
