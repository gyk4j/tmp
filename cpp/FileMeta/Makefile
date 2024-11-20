CC = gcc
CCFLAGS =
CXX = g++
CXXFLAGS = -DWIN32 -D_WIN32 
#-DUNICODE -D_UNICODE
LIBS = 

PROG = ExifToolWrapper
MY_CONSOLE = 1

ifeq ($(MY_CONSOLE),1)
	SUBSYSTEM = -mconsole
else
	SUBSYSTEM = -mwindows
endif

MUNICODE = #-municode

$(PROG).exe : $(PROG).o
	$(CXX) -o $@ $(SUBSYSTEM) $(MUNICODE) -Os -s $^ $(LIBS)

$(PROG).o : $(PROG).cpp $(PROG).h
	$(CXX) -c $(CXXFLAGS) $<
	
clean:
	del $(PROG).exe
	del $(PROG).o