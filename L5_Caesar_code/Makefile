# Makefile

CFLAGS = -c -w -I/usr/local/include
GSLFLAGS = -L/usr/local/lib
LFLAGS = -lm -lgmp

all: clean built

built: caes.o main.o
	@gcc $^ -o main.out -lm -lgmp
	@make clean_b

run:
	@time ./main.out

#---------------------------------------------#
%.o: %.c
	@gcc $(GSLFLAGS) $(CFLAGS) $(LFLAGS) $< -o $@

#---------------------------------------------#

clean:
	@rm -rf *.out *.o *.gch

clean_b:
	@rm -rf *.o *.gch
