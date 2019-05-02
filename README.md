
# RICC - Railway Interactive Control Centre

## Linux

### Dependecies

* cmake
* gcc
* g++ (gcc-g++ on fedora)
* libcurl-devel

### Build

* git submodule update --init --recursive
* mkdir build
* cd build
* cmake .. -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
* make
* make test
