CC=gcc
LIBS=-lX11 -lXext

all: main.o
	$(CC) -o unstrain main.c $(LIBS)

install: unstrain
	install -D -m 755 ./unstrain /usr/local/bin
