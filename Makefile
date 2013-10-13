all: client.o connection.o server.o
	g++ -o start client.o ConnectionInfo.o server.o -lsocket
client.o: client.cpp fileshare.h
	g++ -c -g client.cpp
connection.o: ConnectionInfo.cpp fileshare.h
	g++ -c -g ConnectionInfo.cpp
server.o: server.cpp  fileshare.h
	g++ -c -g server.cpp
clean:
	rm *.o
