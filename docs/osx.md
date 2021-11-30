# Build on OSX

**IMPORTANT**
Since the latest Matlab R2021b version is still not running natively on Apple Silicon (M1 processor) you can not use the building process described below on an Apple Silicon computer. You can use the libraries found in [builds](builds/macOS). Simply copy the libs in that directory - **NOT** in the `arm64` directory - to the `/usr/local/lib` directory (need `sudo` command for copying) before you starting the matlab mex-ing process.

> **NOTE** Check [https://www.wwdcnotes.com/notes/wwdc20/10214/](https://www.wwdcnotes.com/notes/wwdc20/10214/) for information how to get your Mac app running on Apple silicon (arm 64 native architecture)

## Pre-requisites


### Brew

Install _brew_ on OSX.

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### wget

After installing brew, we can use brew to install wget (so you can download files from the command-line):

```
brew install wget
```

### CMake

We need cmake to configure and build OpenMesh and MeshMonk.

1.  Download the latest binary distribution for Mac OSX from the [Downloads page](https://cmake.org/download/)
    
2.  Open the resulting .dmg-file you just downloaded
    
3.  Drag and drop the CMake icon to the Applications folder icon.
    
4.  Launch CMake (from you Applications folder, for example)
    
5.  Add CMake to your path so you can call it from command-line:
    

```
sudo mkdir -p /usr/local/bin
sudo /Applications/CMake.app/Contents/bin/cmake-gui --install=/usr/local/bin
```

1.  Verify your installation (you might have to close and open a new Terminal):
    

```
cmake --version
```

Download MeshMonk
-----------------

Make a 'projects' folder in your home directory and go into it(or go into a directory you are already using for GitHub projects):

```
mkdir ~/projects
cd ~/projects
```

Clone the online MeshMonk repository

```
git clone https://gitlab.kuleuven.be/mirc/meshmonk.git
```

Install libraries
-----------------

### 1\. Install eigen

*   Use brew to install eigen
    

```
brew install eigen
```

or upgrade:

```
brew upgrade eigen
```

*   Make a symlink to the main 'Eigen' folder from /usr/local/include/ so that you can include Eigen in your projects.
    

Check where brew installs the eigen package (e.g. `/opt/homebrew/Cellar/eigen` or `/usr/local/Cellar/eigen`) and adapt the `ln` command hereunder

```
sudo mkdir -p /usr/local/include
sudo ln -s /opt/homebrew/Cellar/eigen/3.4.0_1/include/eigen3/Eigen /usr/local/include/Eigen
```

### 2. _(optional)_ 'Install' nanoflann

Like Eigen, nanoflann is also a header-only library. There is only one header file you need, so we deliver that in the meshmonk repository under '/vendor' directory. So all that's left is to copy that to /usr/local/include:

```
sudo cp ~/projects/meshmonk/vendor/nanoflann.hpp /usr/local/include/
```

### 3\. Install OpenMesh

See [https://www.graphics.rwth-aachen.de/media/openmesh\_static/Documentations/OpenMesh-Doc-Latest/a04315.html#compilers](https://www.graphics.rwth-aachen.de/media/openmesh_static/Documentations/OpenMesh-Doc-Latest/a04315.html#compilers)

```
cd ~/Downloads/
wget https://www.graphics.rwth-aachen.de/media/openmesh_static/Releases/8.1/OpenMesh-8.1.zip
unzip OpenMesh-8.1.zip
cd OpenMesh-8.1
mkdir build
cd build
cmake .. -DBUILD_APPS=OFF
make
```

Copy/paste the _.dylib_ files:

```
sudo cp Build/lib/*.* /usr/local/lib/
```

Copy/paste the header files

```
sudo cp -R ~/Downloads/OpenMesh-8.1/src/OpenMesh /usr/local/include/
```

MeshMonk
--------

### Compile

Enter the subfolder with the c++ sourcecode and use `make` to compile it. As an alternative to this step, you may use the precompiled version of 'libmeshmonk.dylib' in the 'builds' folder of the meshmonk download.

```
cd ~/projects/meshmonk
make
```

From the meshmonk folder, copy the shared library object libmeshmonk.dylib to /usr/local/lib

```
sudo cp libmeshmonk.dylib /usr/local/lib
```

Copy the header files to /usr/local/include/

```
(cd ~/projects/meshmonk/ && find . -name '*.hpp' -print | tar --create --files-from -) | (cd /usr/local/include/ && sudo tar xvfp -)
```
