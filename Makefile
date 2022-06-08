CC = gcc
CFLAGS = -Wall -Wextra -g
IN = main.c sim.c
OUT = out.exe
SDL = `pkg-config sdl2 --cflags --libs`

default:
	$(CC) $(IN) -o $(OUT) $(CFLAGS) $(SDL)
	./out.exe