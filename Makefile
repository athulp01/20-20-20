CC=gcc
LIBS=-lX11 -lXext

all: main.o
	$(CC) -o unstrain main.c $(LIBS)

install: unstrain
	install -D -m 755 ./unstrain /usr/local/bin
	install -D -m 644 ./unstrain.service /usr/lib/systemd/user
