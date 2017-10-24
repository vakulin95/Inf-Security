# Makefile

CFLAGS = -c -O3
LFLAGS = -lm -ljpeg -o
INCDIR = lib/%.c

all: built run clean

%.o: $(INCDIR) # %.c
	@gcc $(CFLAGS) $<

built: main.o jpgio.o enct.o
	@gcc $^ $(LFLAGS) main.out

run:
	@time ./main.out

clean:
	@rm -rf *.o *.out

oclean:
	@cd files
	@rm -rf *.jpg
