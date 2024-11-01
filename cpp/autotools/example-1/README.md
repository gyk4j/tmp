# Prepare `autoconf` and `automake` file

`configure.ac` describes how the project should be built. These include:

- Project name and version
- Temporary files/cache location
- Compiler and linker switches
- Checks for existence of C compiler and source files
- Type of make file to output

`Makefile.am` specifies the output and source code files involved. It is a 
higher-level form of abstract Makefile that is not tool or system-specific.

# Generate the configure script

Prepare script that describes the required files, macros and variables for the 
build. 

Requires `automake`, `autoconf` and `libtool` package.

```sh
autoreconf --verbose --install --force
```

The outputs should be checked in to version control repository.

# Generate the Makefile

Search for the required compiler tools, include files, libraries.

Generate the Makefile with the system-specific file paths and variables found
during configuration time.

```sh
./configure
```

or specify a non-`make` Make tool:

```sh
MAKE="gmake" ./configure
```

# Build using `make` (or user-specified Make tool)

```sh
make
```
