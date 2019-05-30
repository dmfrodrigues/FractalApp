CC     =g++

SDIR   =./src
IDIR   =./include
ODIR   =./obj
LDIR   =./lib

IFLAGS =-I$(IDIR) -I"D:\_ProgrammingLibraries\wxWidgets-3.0.4-new\include" -I"D:\_ProgrammingLibraries\wxWidgets-3.0.4-new" -I"D:\_ProgrammingLibraries\wxWidgets-3.0.4-new\lib\gcc_dll_UNICODE_MONOLITHIC_RELEASE\mswu" -I"D:\_ProgrammingLibraries\mcap"
CFLAGS =-MMD -std=c++11 -ffast-math -pipe -mthreads -D__GNUWIN32__ -D__WXMSW__ -DWXUSINGDLL -DwxUSE_UNICODE -O3 $(IFLAGS) -c

LFLAGS =-L"D:\_ProgrammingLibraries\wxWidgets-3.0.4-new\lib\gcc_dll_UNICODE_MONOLITHIC_RELEASE"

all: makefolders $(LDIR)/libfractalapp.a

makefolders:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)

$(LDIR)/libfractalapp.a: $(ODIR)/FractalBitmap.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o
	ar rvs $(LDIR)/libfractalapp.a $(ODIR)/FractalBitmap.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o

$(ODIR)/FractalBitmap.o:       $(SDIR)/FractalBitmap.cpp
	$(CC) $(CFLAGS)            $(SDIR)/FractalBitmap.cpp       -o $(ODIR)/FractalBitmap.o
$(ODIR)/FractalFrame.o:        $(SDIR)/FractalFrame.cpp
	$(CC) $(CFLAGS)            $(SDIR)/FractalFrame.cpp        -o $(ODIR)/FractalFrame.o
$(ODIR)/FractalPanel.o:        $(SDIR)/FractalPanel.cpp
	$(CC) $(CFLAGS)            $(SDIR)/FractalPanel.cpp        -o $(ODIR)/FractalPanel.o
$(ODIR)/InfoPanel.o:           $(SDIR)/InfoPanel.cpp
	$(CC) $(CFLAGS)            $(SDIR)/InfoPanel.cpp           -o $(ODIR)/InfoPanel.o
$(ODIR)/HDPrintscreenDialog.o: $(SDIR)/HDPrintscreenDialog.cpp
	$(CC) $(CFLAGS)            $(SDIR)/HDPrintscreenDialog.cpp -o $(ODIR)/HDPrintscreenDialog.o

-include $(ODIR)/*.d
