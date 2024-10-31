CC = gcc
CCFLAGS =
CXX = g++
CXXFLAGS = -D_WIN32 -DUNICODE -D_UNICODE
LIBS = -loleaut32 -lole32 -luuid

PROG = 7zcl.exe
MY_CONSOLE = 1

CURRENT_OBJS = \
  Client7z.o

COMMON_OBJS = \
  IntToString.o \
  NewHandler.o \
  MyString.o \
  StringConvert.o \
  StringToInt.o \
  MyVector.o \
  Wildcard.o

WIN_OBJS = \
  DLL.o \
  FileDir.o \
  FileFind.o \
  FileIO.o \
  FileName.o \
  PropVariant.o \
  PropVariantConv.o

7ZIP_COMMON_OBJS = \
  FileStreams.o 
  
CURRENT_SRCS = \
  CPP/7zip/UI/Client7z/Client7z.cpp

COMMON_SRCS = \
  CPP/Common/IntToString.cpp \
  CPP/Common/NewHandler.cpp \
  CPP/Common/MyString.cpp \
  CPP/Common/StringConvert.cpp \
  CPP/Common/StringToInt.cpp \
  CPP/Common/MyVector.cpp \
  CPP/Common/Wildcard.cpp

WIN_SRCS = \
  CPP/Windows/DLL.cpp \
  CPP/Windows/FileDir.cpp \
  CPP/Windows/FileFind.cpp \
  CPP/Windows/FileIO.cpp \
  CPP/Windows/FileName.cpp \
  CPP/Windows/PropVariant.cpp \
  CPP/Windows/PropVariantConv.cpp

7ZIP_COMMON_SRCS = \
  CPP/7zip/Common/FileStreams.cpp
	
default: compile $(PROG)

compile: $(7ZIP_COMMON_SRCS) $(WIN_SRCS) $(COMMON_SRCS) $(CURRENT_SRCS)
	$(CXX) -c $(CXXFLAGS) $?

$(PROG): $(CURRENT_OBJS) $(7ZIP_COMMON_OBJS) $(WIN_OBJS) $(COMMON_OBJS)
	$(CXX) -o $(PROG) -mconsole -Os -s $? $(LIBS)
	
clean:
	del *.o