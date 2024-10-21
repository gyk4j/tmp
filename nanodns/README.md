# Build

NanoDNS uses the [CMake](https://cmake.org) build system.

In the NanoDNS source directory:

```bat
mkdir build
cd build
```

[CMake](https://cmake.org) allows the use of various build tools. Common ones 
include the traditional [GNU make](https://www.gnu.org/software/make/), and 
the newer [Ninja](https://ninja-build.org/).

## GNU make

To use Unix makefile *(default)*:

```bat
cmake ..
make
```

## MinGW

To use MinGW:

```bat
cmake -G "MinGW Makefiles" ..
mingw32-make
```

## Visual Studio

To use Visual Studio 17 2022:

```bat
cmake -G "Visual Studio 17 2022" -A Win32 ..
msbuild
```

## Ninja

To use Ninja:

```bat
cmake -G Ninja ..
ninja
```

The built executable binary `nanodns.exe` will be in the build directory, or
for multi-configuration build in Visual Studio either in `build\Release` or 
`build\Debug` sub-directory.

# Run

NanoDNS always bind to `0.0.0.0`. There is no way to change this currently.

To run, specify the fake IP address to be returned for all DNS queries as a 
command line argument.

```bat
nanodns.exe <IP Address>
```

Example: To make NanoDNS always return `123.234.123.234`, run:

```bat
nanodns.exe 123.234.123.234
```
