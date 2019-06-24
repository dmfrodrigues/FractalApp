WXLIB  =D:\_ProgrammingLibraries\wxWidgets-3.0.4-new
MCAP   =D:\_ProgrammingLibraries\mcap
IFLAGS =-I$(IDIR) -I$(WXLIB)/include -I$(WXLIB) -I$(WXLIB)/lib/gcc_dll_UNICODE_MONOLITHIC_RELEASE/mswu -I$(MCAP)
LFLAGS =-L$(WXLIB)/lib/gcc_dll_UNICODE_MONOLITHIC_RELEASE

CC     =g++

SDIR   =./src
IDIR   =./include
ODIR   =./obj
LDIR   =./lib

CFLAGS =-MMD -std=c++11 -ffast-math -O3 $(IFLAGS) -c

all: makefolders $(LDIR)/libfractalapp.a

makefolders:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)

$(LDIR)/libfractalapp.a: $(ODIR)/FractalBitmap.o $(ODIR)/CURSOR_CROSS.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o
	rm $(LDIR)/libfractalapp.a
	ar rvs $(LDIR)/libfractalapp.a $(ODIR)/FractalBitmap.o $(ODIR)/CURSOR_CROSS.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o

$(ODIR)/FractalBitmap.o:       $(SDIR)/FractalBitmap.cpp
	$(CC) $(CFLAGS)            $(SDIR)/FractalBitmap.cpp       -o $(ODIR)/FractalBitmap.o
$(ODIR)/CURSOR_CROSS.o:        $(SDIR)/CURSOR_CROSS.cpp
	$(CC) $(CFLAGS)            $(SDIR)/CURSOR_CROSS.cpp        -o $(ODIR)/CURSOR_CROSS.o
$(ODIR)/FractalFrame.o:        $(SDIR)/FractalFrame.cpp
	$(CC) $(CFLAGS)            $(SDIR)/FractalFrame.cpp        -o $(ODIR)/FractalFrame.o
$(ODIR)/FractalPanel.o:        $(SDIR)/FractalPanel.cpp
	$(CC) $(CFLAGS)            $(SDIR)/FractalPanel.cpp        -o $(ODIR)/FractalPanel.o
$(ODIR)/InfoPanel.o:           $(SDIR)/InfoPanel.cpp
	$(CC) $(CFLAGS)            $(SDIR)/InfoPanel.cpp           -o $(ODIR)/InfoPanel.o
$(ODIR)/HDPrintscreenDialog.o: $(SDIR)/HDPrintscreenDialog.cpp
	$(CC) $(CFLAGS)            $(SDIR)/HDPrintscreenDialog.cpp -o $(ODIR)/HDPrintscreenDialog.o

-include $(ODIR)/*.d
