all: drserver server client
	
client: client.cpp fileshare.h connection.o
	g++ -o client -g client.cpp ConnectionInfo.o
	
server: server.cpp  fileshare.h connection.o
	g++ -o server -g server.cpp ConnectionInfo.o
	
drserver: directory_server.cpp fileshare.h connection.o
	g++ -g -o drserver directory_server.cpp ConnectionInfo.o
	
connection.o: ConnectionInfo.cpp fileshare.h
	g++ -c -g ConnectionInfo.cpp
	
clean:
	rm *.o drserver server client
