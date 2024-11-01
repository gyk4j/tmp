CC = gcc
CCFLAGS =
CXX = g++
CXXFLAGS = -DWIN32 -D_WIN32 #-DUNICODE -D_UNICODE
LIBS = 

PROG = MediaInfoDLL.exe
MY_CONSOLE = 1

ifeq ($(MY_CONSOLE),1)
	SUBSYSTEM = -mconsole
else
	SUBSYSTEM = -mwindows
endif

MUNICODE = #-municode

$(PROG): MediaInfoDLL.o
	$(CXX) -o $@ $(SUBSYSTEM) $(MUNICODE) -Os -s $^ $(LIBS)

MediaInfoDLL.o: MediaInfoDLL.cpp MediaInfoDLL.h
	$(CXX) -c $(CXXFLAGS) $<
	
clean:
	del MediaInfoDLL.exe
	del MediaInfoDLL.o