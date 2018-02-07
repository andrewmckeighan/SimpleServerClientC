all: client server

client: client.o StringEncoder.o
	gcc -o client client.o -lssl -lcrypto -lm

server: server.o StringEncoder.o
	gcc -o server server.o -lssl -lcrypto -lm

client.o: client.c
	gcc -g -c client.c

server.o: server.c
	gcc -g -c server.c

StringEncoder.o: StringEncoder.c
	gcc -g -c StringEncoder.c
#	./client
