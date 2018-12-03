# Makefile for the socket programming tutorial 
#

server = ServerSocket.o Socket.o server.o Frame.o ServerSocket.h Socket.h SocketException.h Frame.h
client = ClientSocket.o Socket.o client.o Frame.o ServerSocket.h Socket.h SocketException.h Frame.h

all : server client

server: $(server)
	g++ -o server $(server)


client: $(client)
	g++ -o client $(client)


Socket: Socket.cpp 
ServerSocket: ServerSocket.cpp 
ClientSocket: ClientSocket.cpp
server: server.cpp
client: client.cpp
frame: Frame.cpp

clean:
	rm -f *.o simple_server simple_client