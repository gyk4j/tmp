# Build

In current top level `/wreck` project directory.

> [!NOTE]
> Currently, `Makefile` uses Windows/DOS commands, assuming that a Linux/Unix 
> POSIX environment is *NOT available*. So it should only be used on Windows 
> machine only, with MinGW's `make` or `mingw32-make`.
>   
> The `build.bat` batch file naturally should run only on Windows.

```Batchfile
make
```

or

```Batchfile
mingw32-make
```

or

```Batchfile
build.bat
```

# Clean

```Batchfile
make clean
```