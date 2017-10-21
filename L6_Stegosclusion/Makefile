# Makefile

CFLAGS = -c -O3
LFLAGS = -lm -ljpeg -o

all: built run clean

%.o: %.c
	@gcc $(CFLAGS) $<

built: main.o
	@gcc $^ $(LFLAGS) main.out

run:
	@time ./main.out

clean:
	@rm -rf *.o *.out

oclean:
	@cd files
	@rm -rf *.jpg
