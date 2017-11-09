# Makefile

CFLAGS = -c -O3
LFLAGS = -lm -lz -lpng -o
INCDIR = lib/%.c
OUTDIR = files/

THIS_FILE := $(lastword $(MAKEFILE_LIST))

LFILES = main.o pngio.o enct.o dect.o feistel.o

#=================================#

all: oclean convpng built run clean

enc: oclean convpng built run_e clean

dec: built run_d clean

#---------------------------------#

%.o: $(INCDIR)
	@gcc $(CFLAGS) $<

built: $(LFILES)
	@gcc $^ $(LFLAGS) main.out

#---------------------------------#

run:
	@time ./main.out || $(MAKE) -f $(THIS_FILE) clean

run_e:
	@time ./main.out -e || $(MAKE) -f $(THIS_FILE) clean

run_d:
	@time ./main.out -d || $(MAKE) -f $(THIS_FILE) clean

#---------------------------------#

clean:
	@rm -rf *.o *.out

oclean:
	@rm -rf $(OUTDIR)*.png

convpng:
ifeq ($(words $(wildcard *.png)), 1)
	@convert *.png -resize 512x512! -define png:color-type=2 -depth 8 $(OUTDIR)in.png
else
	@echo "More than one input file!";
	@exit 2;
endif
