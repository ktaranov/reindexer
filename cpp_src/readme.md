# Reindexer

**Reindexer** is an embeddable, in-memory, document-oriented database with a high-level Query builder interface.
Reindexer's goal is to provide fast search with complex queries.

The Reindexer is compact and fast. It has not heavy dependencies. Complete reindexer docker image with all libraries and web interface size is just 15MB.
Reindexer is fast. Up to 5x times faster, than mongodb, and 10x times than elastic search. See [benchmaks section](../benchmarks) for details.

# Installation

## Docker image

The simplest way to get reindexer, is pulling & run docker image from [dockerhub](https://hub.docker.com/r/reindexer/reindexer/)

````bash
docker run -p9088:9088 -p6534:6534 -it reindexer/reindexer
````

## OSX brew

````bash
brew tap restream/reindexer
brew install reindexer
````

## Linux

Repositories with packages is comming soon. Now it is possible to install reindexer from sources

## Installing from sources

### Dependencies

Reindexer's core is written in C++11 and uses LevelDB as the storage backend, so the Cmake, C++11 toolchain and LevelDB must be installed before installing Reindexer.  To build Reindexer, g++ 4.8+ or clang 3.3+ is required.  
Dependencies can be installed automatically by this script:

```bash
curl https://github.com/restream/reindexer/raw/master/dependencies.sh | bash -s
```

### Build 

The typical steps for building and configuring the reindexer looks like this

````bash
git clone github.com/restream/reindexer
cd reindexer/cpp_src
mkdir -p build && cd build
cmake ..
make -j4
# optional: step for build swagger documentation
make swagger
# optional: step for build web pages of Reindexer's face
make face
# install to system
sudo make install
````

## Using reindexer server

- Start server
```
service start reindexer
```
- open in web browser http://127.0.0.1:9088/swagger  to see reindexer REST API interactive documentation

- open in web browser http://127.0.0.1:9088/face to see reindexer web interface


# Optional dependencies

- `Doxygen` package is also required for building a documentation of the project.
- `gtest`,`gbenchmark` for run C++ tests and benchmarks
- `gperftools` for memory and performance profiling
