# Makefile

CFLAGS = -c -O3
LFLAGS = -lm -lz -lpng -o
INCDIR = lib/%.c
OUTDIR = files/

LFILES = main.o pngio.o

THIS_FILE := $(lastword $(MAKEFILE_LIST))

#=================================#

all: built run clean

#---------------------------------#

%.o: $(INCDIR)
	@gcc $(CFLAGS) $<

built: $(LFILES)
	@gcc $^ $(LFLAGS) main.out

#---------------------------------#

run:
	@time ./main.out || $(MAKE) -f $(THIS_FILE) clean

#---------------------------------#

clean:
	@rm -rf *.o *.out
