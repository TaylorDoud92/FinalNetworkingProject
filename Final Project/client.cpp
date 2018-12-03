#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <bitset>
#include "Frame.h"

int main(int argc, int argv[]) {
	
	std::string ipaddress;
	std::cout << "Please Enter IP address of server" << "\n";
//	std::getline(std::cin,ipaddress);
	std::cout << "We're past getLine";

	try {

		// Replace "localhost" with the hostname
		// that you're running your server.
		ClientSocket dataChannel("localhost", 30000);
		ClientSocket ackChannel("localhost", 30001);

		Frame incomingFrame;
		Frame sendingFrame;
		
		std::string fileName;
		std::string incomingLine;
		std::string outgoingLine;

		std::getline(std::cin, fileName);

		try{
			dataChannel << fileName;
		} catch (SocketException& e){
			std::cout << "Exception was caught:" << e.description() << "\n";
		}
		// Usually in real applications, the following
		// will be put into a loop.

		while(true){

				try {
					dataChannel >> incomingLine;

					incomingFrame.characters = incomingLine.substr(0,incomingLine.size()-1);
					incomingFrame.parity = incomingLine.back();
					incomingFrame.asciiSum();

					if(incomingFrame.compareParity()){
						ackChannel << "ACK";
						std::cout << incomingFrame.characters;
					} else {
						ackChannel << "NAK";
					}

				} catch (SocketException&) {

				}

		}

	} catch (SocketException& e) {
		std::cout << "Exception was caught:" << e.description() << "\n";
	}

	return 0;
}
