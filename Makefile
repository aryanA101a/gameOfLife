build:
	gcc gameOfLife.c -lraylib -o gameOfLife

run:	build
	./gameOfLife
