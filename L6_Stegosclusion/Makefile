# Makefile

CFLAGS = -c -O3
LFLAGS = -lm -ljpeg -lpng -o
INCDIR = lib/%.c
OUTDIR = files/

#=================================#

all: built run clean

enc: built run_e clean

dec: built run_d clean

#---------------------------------#

%.o: $(INCDIR) # %.c
	@gcc $(CFLAGS) $<

built: main.o jpgio.o pngio.o enct.o dect.o
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
	@rm -rf $(OUTDIR)enc_out.png $(OUTDIR)dec_out.png
