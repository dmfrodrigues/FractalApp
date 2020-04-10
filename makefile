GMPARITH=/media/dmfr/DATA/_ProgrammingLibraries/gmp-arith
IFLAGS =-I$(IDIR) -I$(GMPARITH)
LFLAGS =`wx-config --libs` -lgmp -lgmpxx

CC     =g++

SDIR   =./src
IDIR   =./include
ODIR   =./obj
LDIR   =./lib

CFLAGS =-std=c++11 -ffast-math -O3 $(IFLAGS) `wx-config --cxxflags` -c

all: makefolders $(LDIR)/libfractalapp.a

makefolders:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)

$(LDIR)/libfractalapp.a: $(ODIR)/FractalBitmap.o $(ODIR)/CURSOR_CROSS.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o
	rm -f $(LDIR)/libfractalapp.a
	ar rvs $(LDIR)/libfractalapp.a $(ODIR)/FractalBitmap.o $(ODIR)/CURSOR_CROSS.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf obj
	rm -rf lib
