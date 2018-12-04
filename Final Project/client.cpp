#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <vector>
#include "Frame.h"

using namespace std;

void sendConfirmation() {

}

int main(int argc, int argv[]) {
	

	vector<Frame> frameList;
	Frame incomingFrame;

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
			std::cout << "waiting for incoming\n";
			dataChannel >> incomingLine;
			incomingFrame.characters = incomingLine.substr(0,64);
//			incomingFrame.parity = incomingLine.back();
//			frameList.push_back(incomingFrame);
			if((incomingFrame.convertBinary(incomingFrame.checkSum)+incomingFrame.parity)%2 == 0){
				ackChannel << "ACK";
			} else {
				ackChannel << "NAK";
			}
//			std::cout << "received Line" << "\n";
			std::cout << incomingLine << "\n";
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
