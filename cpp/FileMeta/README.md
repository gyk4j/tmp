# ExifToolWrapper
A C++ Wrapper for Phil Harvey's Excellent ExifTool

## About ExifTool
[ExifTool](https://sno.phy.queensu.ca/~phil/exiftool/) is a command-line 
application that can retrieve and update metadata in media files produced by 
cameras and other devices. It originally handled 
[EXIF](https://en.wikipedia.org/wiki/Exif) data embedded in .jpg files produced 
by digital cameras. As Harvey has improved the tool over the years it now 
processes embedded metadata in a variety of formats — principally those 
produced by digital cameras and video recorders. 

## About ExifToolWrapper
ExifToolWrapper is written in C++. It loads ExifTool and calls it to retrieve 
metadata from media files. A future version may include the ability to set 
metadata properties. The purpose is to make the features of ExifTool 
conveniently usable from C++ applications.

In this case, the CodeBit is the `ExifToolWrapper.cpp` and `ExifToolWrapper.h` 
file. It is intended to be reused in other applications.

## About the Project
This project includes `ExifToolWrapper.cpp` and `ExifToolWrapper.h`. It was 
created in a text editor and uses [MinGW-w64](https://www.mingw-w64.org/).
