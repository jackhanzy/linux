server: socket.o socket_server.o
	g++ -g -o server socket.cpp socket_server.cpp server.cpp

socket_server.o: socket_server.cpp socket_server.h socket.cpp socket.h
	g++ -c socket.cpp socket_server.cpp

socket.o: socket.cpp socket.h
	g++ -c socket.cpp
.PHONY: clean

clean:
	rm -f *.o
