objects = main.c compressor.c

all: $(objects)
	gcc $(objects) -lm -o bin

run:
	./bin
