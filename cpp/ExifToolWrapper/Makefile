CC = gcc
CCFLAGS =
CXX = g++
CXXFLAGS = -DWIN32 -D_WIN32 
# Many strings assume "char" type, making it *non-Unicode* by default.
# To keep ExifToolWrapper.cpp unchanged as much as possible, we keep it as
# non-Unicode.
# -DUNICODE -D_UNICODE
LIBS = 

PROG = ExifToolWrapper
MY_CONSOLE = 1

ifeq ($(MY_CONSOLE),1)
	SUBSYSTEM = -mconsole
else
	SUBSYSTEM = -mwindows
endif

MUNICODE = #-municode

$(PROG): main.o ExifToolWrapper.o CWinThread.o
	$(CXX) -o $@ $(SUBSYSTEM) $(MUNICODE) -Os -s $^ $(LIBS)
	
main.o: main.cpp ExifToolWrapper.h
	$(CXX) -c $(CXXFLAGS) $<

ExifToolWrapper.o: ExifToolWrapper.cpp ExifToolWrapper.h afxwin.h
	$(CXX) -c $(CXXFLAGS) $<
	
CWinThread.o: CWinThread.cpp CWinThread.h afxwin.h
	$(CXX) -c $(CXXFLAGS) $<
	
clean:
	del $(PROG).exe
	del *.o