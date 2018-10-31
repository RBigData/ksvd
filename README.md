# ksvd 

* **Version:** 0.1-0
* **License:** [BSD 3-Clause](https://opensource.org/licenses/BSD-3-Clause)
* **Project home**: https://github.com/RBigData/ksvd
* **Bug reports**: https://github.com/RBigData/ksvd/issues


TODO


## Installation

ksvd requires:

* A system installation of MPI
* R version 3.0.0 or higher
* The pbdDMAT, pbdSLAP, and pbdMPI packages, as well as their dependencies.

At this time we recommend using the development versions:

```r
remotes::install_github("RBigData/pbdMPI")
remotes::install_github("RBigData/pbdSLAP")
remotes::install_github("RBigData/pbdBASE")
remotes::install_github("RBigData/pbdDMAT")
```

<!-- Assuming you meet the system dependencies, you can install the stable version from CRAN using the usual `install.packages()`:

```r
install.package("ksvd")
``` -->

The development version is maintained on GitHub, and can easily be installed by any of the packages that offer installations from GitHub:

```r
remotes::install_github("RBigData/ksvd")
```
