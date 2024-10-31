# MinGW Makefile for 7-Zip's Client7z

A working Makefile for building the [Client7z][client7z] demo program to test 
`7z.dll` DLL loading and usage. This is useful if you need to build it using 
GCC/MinGW compiler toolchain, instead of MSVC.

Adapted from 7-Zip's Microsoft Visual C++ Makefiles.

7-Zip earlier than version 21 were originally buildable using Microsoft Visual 
C++, thus only MSVC compatible Makefiles were provided.

> [!NOTE]
> Tested with *[MinGW-w64][mingw]* and *[7-Zip 24.07][7zip]*.  
>
> But should work with any newer GCC, MinGW-x64 and 7-Zip if there is no major 
> change in file organization or API interface.

## Building 

### Check for prerequisites and required tools

The required tools are `make` or `mingw32-make` and `g++` compiler/linker. Both
tools are provided by a working installation of *MinGW* and should be set in 
the system path.

```shell

C:\>g++ -v
Reading specs from .../lib/gcc/mingw32/X.X.X/specs
... snip for brevity ...
gcc version X.X.X (mingw-special)

C:\>make -v
GNU Make X.X.X
Copyright (C) 20XX  Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.

C:\>mingw32-make -v
GNU Make X.X.X
Copyright (C) 20XX  Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.

```

### Download 7-Zip source codes

Choose your preferred 7-Zip version. Most people would choose the latest 
version.

Download the source codes (`7zXXXX-src.7z`) in .7z archive format, where *XXXX* 
is the version number e.g. `7z2407-src.7z` for version 24.07. The various 
versions can be found [here][download].

Extract the files after downloading. Let's assume the files are extracted to
`C:\7zXXXX-src`.

```shell
C:\>cd 7zXXXX-src
C:\7zXXXX-src>dir
 ... snip ...

 Directory of C:\7zXXXX-src

31/10/2024  01:49 PM    <DIR>          .
31/10/2024  01:49 PM    <DIR>          ..
31/10/2024  08:15 AM    <DIR>          Asm
31/10/2024  08:15 AM    <DIR>          C
31/10/2024  08:15 AM    <DIR>          CPP
31/10/2024  08:15 AM    <DIR>          DOC

```

### Add the Makefile

Copy `Makefile` into `C:\7zXXXX-src` directory.

```shell
C:\7zXXXX-src>dir
 ... snip ...

 Directory of C:\7zXXXX-src

31/10/2024  01:49 PM    <DIR>          .
31/10/2024  01:49 PM    <DIR>          ..
31/10/2024  08:15 AM    <DIR>          Asm
31/10/2024  08:15 AM    <DIR>          C
31/10/2024  08:15 AM    <DIR>          CPP
31/10/2024  08:15 AM    <DIR>          DOC
**31/10/2024  01:47 PM             1,339 Makefile**
```
### Compile and Build

Run `make` or `mingw32-make`

```shell
C:\7zXXXX-src>make

  ... snip ...

C:\7zXXXX-src>dir
 ... snip ...

 Directory of C:\7zXXXX-src

31/10/2024  01:49 PM    <DIR>          .
31/10/2024  01:49 PM    <DIR>          ..
31/10/2024  08:15 AM    <DIR>          Asm
31/10/2024  08:15 AM    <DIR>          C
31/10/2024  08:15 AM    <DIR>          CPP
31/10/2024  08:15 AM    <DIR>          DOC
31/10/2024  01:47 PM             1,339 Makefile
**31/10/2024  01:49 PM           131,072 7zcl.exe**
... snip .o output object files ...
```

If the build is successful, it is output as `7zcl.exe`.

## Adding files

Before running this `7zcl.exe`, it requires the pre-built `7z.dll` Windows 
dynamic library from 7-Zip.

Download one of the binary EXE or MSI installer.

- `7zXXXX.exe` (32-bit)
- `7zXXXX.msi` (32-bit)
- `7zXXXX-x64.exe` (64-bit)
- `7zXXXX-x64.exe` (64-bit)

Take note of the *version number* and *architecture (x86 or x64)*. The 
architecture must match your Client7z executable (32-bit or 64-bit).

Using 7-Zip, extract `7z.dll` into `C:\7zXXXX-src`

```shell
C:\7zXXXX-src>dir
  ... snip ...

 Directory of C:\7zXXXX-src

31/10/2024  01:49 PM    <DIR>          .
31/10/2024  01:49 PM    <DIR>          ..
31/10/2024  08:15 AM    <DIR>          Asm
31/10/2024  08:15 AM    <DIR>          C
31/10/2024  08:15 AM    <DIR>          CPP
31/10/2024  08:15 AM    <DIR>          DOC
31/10/2024  01:47 PM             1,339 Makefile
**19/06/2024  03:00 PM         1,891,840 7z.dll**
31/10/2024  01:49 PM           131,072 7zcl.exe
  ... snip .o output object files ...
```

## Running Client7z

### View use cases / examples

Let's run `7zcl.exe` without any parameters to view the help with use cases and
examples.

```shell
C:\7zXXXX-src>7zcl

7-Zip 24.07 (7z.dll client) Igor Pavlov : Public domain 2024-06-19

Usage: Client7z.exe [a | l | x ] archive.7z [fileName ...]
Examples:
  Client7z.exe a archive.7z f1.txt f2.txt  : compress two files to archive.7z
  Client7z.exe l archive.7z   : List contents of archive.7z
  Client7z.exe x archive.7z   : eXtract files from archive.7z

C:\7zXXXX-src>
```

### List contents of archive file

Let's use `7zcl.exe` to list the contents of a 7Z archive. Assuming the source 
code archive file (e.g. `7z2407-src.7z`) is available, let's reuse it as a test
file.

```shell
C:\7zXXXX-src>7zcl l ..\7z2407-src.7z | more

7-Zip 24.07 (7z.dll client) Igor Pavlov : Public domain 2024-06-19

1466  Asm\arm\7zCrcOpt.asm
3146  Asm\arm64\7zAsm.S
37757  Asm\arm64\LzmaDecOpt.S
5785  Asm\x86\7zAsm.asm
6711  Asm\x86\7zCrcOpt.asm
17101  Asm\x86\AesOpt.asm
13837  Asm\x86\LzFindOpt.asm
34838  Asm\x86\LzmaDecOpt.asm

  ... snip for brevity ...

C:\7zXXXX-src>
```

We have successfully demonstrated that `7zcl.exe` is able to load and use 
`7z.dll` to open archive files.

[client7z]: https://github.com/ip7z/7zip/blob/main/CPP/7zip/UI/Client7z/Client7z.cpp
[mingw]: https://www.mingw-w64.org/
[7zip]: https://sourceforge.net/projects/sevenzip/files/7-Zip/24.07/
[download]: https://sourceforge.net/projects/sevenzip/files/7-Zip/