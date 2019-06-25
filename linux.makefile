MCAP=/media/dmfr/DATA/_ProgrammingLibraries/mcap
IFLAGS =-I$(IDIR) -I$(MCAP)
LFLAGS =`wx-config --libs`

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
