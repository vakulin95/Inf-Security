# Makefile

CFLAGS = -c -O3
LFLAGS = -lm -ljpeg -lpng -o
INCDIR = lib/%.c
OUTDIR = files/

LFILES = main.o pngio.o enct.o dect.o

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
	@time ./main.out

run_e:
	@time ./main.out -e

run_d:
	@time ./main.out -d

#---------------------------------#

clean:
	@rm -rf *.o *.out

oclean:
	@rm -rf $(OUTDIR)enc_out.png $(OUTDIR)dec_out.png $(OUTDIR)in.png

convpng:
	@convert $(OUTDIR)*.png -resize 512x512! -define png:color-type=2 -depth 8 $(OUTDIR)in.png
