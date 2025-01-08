compile: compile_client compile_server

compile_client: client.o networking.o
	@gcc -o client_ client.o networking.o

compile_server: server.o networking.o
	@gcc -o server_ server.o networking.o

client.o: client.c networking.h
	@gcc -c client.c

server.o: server.c networking.h
	@gcc -c server.c

networking.o: networking.c networking.h
	@gcc -c networking.c

server: server_
	@./server_

client: client_
	@./client_

clean:
	@rm -f *.o server_ client_