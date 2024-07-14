build:
	gcc gameOfLife.c -lraylib -fopenmp -o gameOfLife

run:	build
	./gameOfLife
