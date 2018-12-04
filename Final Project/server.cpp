#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Frame.h"

using namespace std;

int main(int argc, int argv[]) {

	vector<Frame> frameList;
	Frame incomingFrame;
	Frame outgoingFrame;
	int counter = 0;
	string ack;
	string fileName;
	srand(5);

	cout << "running...\n";

	try {

		ServerSocket dataChannel(29999);
		ServerSocket ackChannel(30000);

		cout << "Created Server Socket... \n" << std::endl;
		cout << "Reading File... \n" << std::endl;

		ServerSocket data_sock;
		ServerSocket ack_sock;

		dataChannel.accept(data_sock);
		ackChannel.accept(ack_sock);

		cout << "Connected Sockets \n";

		try {
			data_sock >> fileName;
			cout << "FileName received \n";

			ifstream inFile(fileName);
			cout << "FileName updated \n";

			string incomingStr;

			while (getline(inFile, incomingStr)) {

				while(incomingStr.length() > 64){

					outgoingFrame.characters = incomingStr.substr(0,64);
					outgoingFrame.asciiSum();
					incomingStr = incomingStr.substr(64,incomingStr.size());
					frameList.push_back(outgoingFrame);
					cout << outgoingFrame.characters << "\n";
				}
				outgoingFrame.characters = incomingStr.substr(0,incomingStr.length()-1);
				outgoingFrame.asciiSum();
				frameList.push_back(outgoingFrame);
				cout << outgoingFrame.characters << "\n";
				std::cout << "New Line" << "\n";
			}
			inFile.close();

			cout << "File Closed";

//			for(int i=0;i<frameList.size();i++){
//				data_sock << frameList[i].characters;
//				ack_sock >> ack;
//				cout << ack << "\n";
//			}

			for(int i=0;i<frameList.size();i++){
				std::cout << frameList[i].characters;
				if(rand() != 5 || counter != 5){

					if(frameList[i].convertBinary(frameList[i].checkSum)%2 == 0){
						frameList[i].parity = 0;
					} else {
						frameList[i].parity = 1;
					}
					data_sock << frameList[i].characters + std::to_string(frameList[i].parity);
					counter++;

					} else {

					if(frameList[i].convertBinary(frameList[i].checkSum)%2 == 0){
						frameList[i].parity = 1;
					} else {
						frameList[i].parity = 0;
					}
					data_sock << frameList[i].characters + std::to_string(frameList[i].parity);
					counter = 0;
				}
				ack_sock >> ack;
				cout << ack << "\n";

				if(ack == "NAK"){
					if(frameList[i].convertBinary(frameList[i].checkSum)%2 == 0){
						frameList[i].parity = 0;
					} else {
						frameList[i].parity = 1;
					}
					data_sock << frameList[i].characters + std::to_string(frameList[i].parity);
				}
			}
		} catch (SocketException& e) {
				std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
		}
	} catch (SocketException& e) {
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	return 0;
}
