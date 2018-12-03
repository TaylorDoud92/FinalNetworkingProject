#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <bitset>
#include <thread>
#include <chrono>
#include "Frame.h"

int main(int argc, int argv[]) {
	
	Frame incomingFrame;
	Frame sendingFrame;

	std::string fileName;
	std::string incomingLine;
	std::string outgoingLine;
	std::string ipaddress;

	std::cout << "Please Enter IP address of server" << "\n";
	std::getline(std::cin,ipaddress);
	std::cout << "Enter File to transfer \n";
	std::getline(std::cin, fileName);

	try {

		// Replace "localhost" with the hostname
		// that you're running your server.
		ClientSocket dataChannel("localhost", 29999);
		ClientSocket ackChannel("localhost", 30000);

		dataChannel << fileName;

		while(true){
			dataChannel >> incomingLine;
			std::cout << incomingLine;
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}

		try{
			dataChannel << fileName;
		} catch (SocketException& e){
			std::cout << "Exception was caught:" << e.description() << "\n";
		}


//		while(true){
//				try {
//					dataChannel >> incomingLine;
//
//					incomingFrame.characters = incomingLine.substr(0,incomingLine.size()-1);
//					incomingFrame.parity = incomingLine.back();
//					incomingFrame.asciiSum();
//
//					if(incomingFrame.compareParity()){
//						ackChannel << "ACK";
//						std::cout << incomingFrame.characters;
//					} else {
//						ackChannel << "NAK";
//					}
//
//					std::cout << "alive";
//				} catch (SocketException&) {
//
//				}
//
//		}

	} catch (SocketException& e) {
		std::cout << "Exception was caught:" << e.description() << "\n";
	}

	return 0;
}
