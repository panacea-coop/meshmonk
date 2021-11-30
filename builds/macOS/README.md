# macOS libraries
These libraries were build for intel x86_64 architecture

**on Apple Silicon (M1 processor)** - You can't use the installation description on [OSX](docs/osx.md). Simply copy the libs in this directory - **NOT** in the `arm64` directory - to the `/usr/local/lib` directory (need `sudo` command for copying) before you starting the matlab `mex-ing` process.

## arm64 subdirectory
in the `arm64` subdirectory you will find the libraries build on arm64 (Apple Silicon)
For the moment these libraries can not be used with matlab since the current version of Matlab (R2021b) is still not running natively on arm64

