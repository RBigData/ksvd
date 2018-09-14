suppressMessages(library(ksvd))
init.grid()

.pbd_env$bldim = c(2, 2)
m = 5
n = 5
x = ddmatrix("rnorm", m, n)

# ret = ksvd(x, nu=0, nv=0)
# comm.print(rev(ret$d))
# ret = La.svd(x, nu=0, nv=0)
# comm.print(ret$d)

ret = ksvd(x)
comm.print(rev(ret$d))
ret = La.svd(x, nu=0, nv=0)
comm.print(ret$d)


# .pbd_env$bldim = c(64, 64)
# m = 512
# n = 512
# x = ddmatrix("rnorm", m, n)
# 
# ret = comm.timer(d_ksvd <- ksvd(x)$d)
# comm.print(ret)
# d_ksvd = rev(d_ksvd)
# ret = comm.timer(d_svd <- La.svd(x)$d)
# comm.print(ret)
# 
# comm.print(head(d_ksvd))
# comm.print(head(d_svd))
# comm.print(all.equal(d_ksvd, d_svd))


finalize()
