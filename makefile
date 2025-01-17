SUBD = /tmp/$(ARGS)
ARGS ?= rpsfolder
export SUBD

compile: compile_client compile_server move_final

compile_client: client.o networking.o
	@gcc -o client_ client.o networking.o

compile_server: server.o networking.o server_util.o
	@gcc -o server_ server.o networking.o server_util.o

client.o: client.c networking.h
	@gcc -c client.c

server.o: server.c networking.h
	@gcc -c server.c

networking.o: networking.c networking.h
	@gcc -c networking.c

server_util.o: server_util.c server_util.h
	@gcc -c server_util.c

move_final:
	@cp ./makefile /tmp
	@mkdir -p $(SUBD)
	@mv server_ client_ $(SUBD)
	@chmod 777 $(SUBD)
	@export SUBD

server: $(SUBD)/server_
	@cd $(SUBD) && ./server_

client: $(SUBD)/client_
	@cd $(SUBD) && ./client_

clean:
	@rm -f *.o server_ client_
	@rm -rf $(SUBD)
	@rm -f /tmp/makefile
