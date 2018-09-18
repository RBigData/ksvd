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
  
  if (m < n)
    comm.stop("only m>=n is supported in ksvd()")
  
  min_mn = min(m, n)
  bldim = x@bldim
  ICTXT = x@ICTXT
  
  dim_a = dim(x)
  ldim_a = base.numroc(dim=dim_a, bldim=bldim, ICTXT=ICTXT)
  desca = base.descinit(dim_a, bldim, ldim_a, ICTXT)
  
  dim_u = c(m, min_mn)
  if (nu == 0)
  {
    jobu = 'N'
    ldim_u = c(-1L, -1L)
  }
  else
  {
    jobu = 'V'
    ldim_u = base.numroc(dim=dim_u, bldim=bldim, ICTXT=ICTXT)
  }
  
  dim_vt = c(min_mn, n)
  if (nv == 0)
  {
    jobvt = 'N'
    ldim_vt = c(-1L, -1L)
  }
  else
  {
    jobvt = 'V'
    ldim_vt = base.numroc(dim=dim_vt, bldim=bldim, ICTXT=ICTXT)
  }
  
  descu = base.descinit(dim_u, bldim, ldim_u, ICTXT)
  descvt = base.descinit(dim_vt, bldim, ldim_vt, ICTXT)
  
  # eigtype: "r", "d"
  out = rpdgeqsvd(jobu, jobvt, eigtype='d', x@Data, desca, descu, descvt)
  
  
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
