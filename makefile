ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Windows)
	MKDIR=mkdir -p --
	RM   =rm -f
	RMDIR=rm -rf
endif
ifeq ($(detected_OS),Linux)
	MKDIR=mkdir -p
	RM   =rm -f
	RMDIR=rm -rf
endif

#GMPARITH=../gmp-arith
IFLAGS =-I$(IDIR) #-I$(GMPARITH)
LFLAGS =`wx-config --libs` #-lgmp -lgmpxx

CC     =g++

LIB    =fractalapp
SDIR   =./src
IDIR   =./include
ODIR   =./obj
LDIR   =./lib
FLIB   =$(LDIR)/lib$(LIB).a

CFLAGS_OPTIMIZE=-ffast-math -O3
CFLAGS_PARANOID=-pthread -g -O -Wall -pedantic -Wunused-result -pedantic-errors -Wextra -Wcast-align -Wcast-qual -Wchar-subscripts -Wcomment -Wconversion -Wdisabled-optimization \
    -Wfloat-equal  -Wformat  -Wformat=2 -Wformat-nonliteral -Wformat-security -Wformat-y2k -Wimport -Winit-self -Winvalid-pch -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wpacked -Wparentheses  -Wpointer-arith -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings# -Wunsafe-loop-optimizations -Winline -Weffc++ -Wpadded
CFLAGS =$(IFLAGS) $(CFLAGS_PARANOID) $(CFLAGS_OPTIMIZE) `wx-config --cxxflags`

all: $(FLIB)

O_FILES=$(ODIR)/FractalBitmap.o $(ODIR)/CURSOR_CROSS.o $(ODIR)/FractalFrame.o $(ODIR)/FractalPanel.o $(ODIR)/InfoPanel.o $(ODIR)/HDPrintscreenDialog.o

 $(FLIB): $(O_FILES) | $(LDIR)
	$(RM) $(FLIB)
	ar rvs $(FLIB) $(O_FILES)

$(ODIR)/%.o: $(SDIR)/%.cpp | $(ODIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(ODIR):
	$(MKDIR) $@

$(LDIR):
	$(MKDIR) $@

clean:
	$(RMDIR) $(ODIR)
	$(RMDIR) $(LDIR)
