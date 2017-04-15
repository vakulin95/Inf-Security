# Makefile

CFLAGS = -c -w -O3
LFLAGS = -lm -o

all: clean built

built: rand_gen.o main.o
	@gcc $^ $(LFLAGS) main.out
	@make clean_b

run:
	@time ./main.out

run_l:
	@time ./main.out -l

#---------------------------------------------#
%.o: %.c
	@gcc $(CFLAGS) $< -o $@

#---------------------------------------------#

clean:
	@rm -rf *.out *.o *.gch

clean_b:
	@rm -rf *.o *.gch
