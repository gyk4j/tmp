CC = gcc
CCFLAGS =
CXX = g++
CXXFLAGS = -D_WIN32 -DUNICODE -D_UNICODE
LIBS = -loleaut32 -lole32 -luuid

PROG = 7zcl.exe
MY_CONSOLE = 1

ifeq ($(MY_CONSOLE),1)
	SUBSYSTEM = -mconsole
else
	SUBSYSTEM = -mwindows
endif

MUNICODE = -municode

$(PROG): Client7z.o IntToString.o NewHandler.o MyString.o StringConvert.o \
	StringToInt.o MyVector.o Wildcard.o DLL.o FileDir.o FileFind.o FileIO.o \
	FileName.o PropVariant.o PropVariantConv.o FileStreams.o
	$(CXX) -o $@ $(SUBSYSTEM) $(MUNICODE) -Os -s $^ $(LIBS)

Client7z.o: CPP/7zip/UI/Client7z/Client7z.cpp
	$(CXX) -c $(CXXFLAGS) $<

IntToString.o: CPP/Common/IntToString.cpp CPP/Common/IntToString.h
	$(CXX) -c $(CXXFLAGS) $<

NewHandler.o: CPP/Common/NewHandler.cpp CPP/Common/NewHandler.h
	$(CXX) -c $(CXXFLAGS) $<

MyString.o: CPP/Common/MyString.cpp CPP/Common/MyString.h
	$(CXX) -c $(CXXFLAGS) $<

StringConvert.o: CPP/Common/StringConvert.cpp CPP/Common/StringConvert.h
	$(CXX) -c $(CXXFLAGS) $<

StringToInt.o: CPP/Common/StringToInt.cpp CPP/Common/StringToInt.h
	$(CXX) -c $(CXXFLAGS) $<

MyVector.o: CPP/Common/MyVector.cpp CPP/Common/MyVector.h
	$(CXX) -c $(CXXFLAGS) $<

Wildcard.o: CPP/Common/Wildcard.cpp CPP/Common/Wildcard.h
	$(CXX) -c $(CXXFLAGS) $<

DLL.o: CPP/Windows/DLL.cpp CPP/Windows/DLL.h
	$(CXX) -c $(CXXFLAGS) $<

FileDir.o: CPP/Windows/FileDir.cpp CPP/Windows/FileDir.h
	$(CXX) -c $(CXXFLAGS) $<

FileFind.o: CPP/Windows/FileFind.cpp CPP/Windows/FileFind.h
	$(CXX) -c $(CXXFLAGS) $<

FileIO.o: CPP/Windows/FileIO.cpp CPP/Windows/FileIO.h
	$(CXX) -c $(CXXFLAGS) $<
  
FileName.o: CPP/Windows/FileName.cpp CPP/Windows/FileName.h
	$(CXX) -c $(CXXFLAGS) $<

PropVariant.o: CPP/Windows/PropVariant.cpp CPP/Windows/PropVariant.h
	$(CXX) -c $(CXXFLAGS) $<

PropVariantConv.o: CPP/Windows/PropVariantConv.cpp CPP/Windows/PropVariantConv.h
	$(CXX) -c $(CXXFLAGS) $<

FileStreams.o: CPP/7zip/Common/FileStreams.cpp CPP/7zip/Common/FileStreams.h
	$(CXX) -c $(CXXFLAGS) $<
	
clean:
	del *.o