#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include "Frame.h"

using namespace std;

int main(int argc, int argv[]) {

	Frame incomingFrame;
	Frame outgoingFrame;
	int counter = 0;
	string ack;
	string fileName;
	srand(5);

	cout << "running....\n";

	try {
		// Create the socket and pass port number
		while (true) {

		ServerSocket dataChannel(29999);
		ServerSocket ackChannel(30000);


		cout << "Created Server Socket... \n" << std::endl;
		cout << "Reading File... \n" << std::endl;

		ServerSocket data_sock;
		ServerSocket ack_sock;
		dataChannel.accept(data_sock);			//Start listening for data Socket and ack Socket
		ackChannel.accept(ack_sock);


			cout << "Connected Socks \n";

			try {
				data_sock >> fileName;


				data_sock << fileName;
				cout << "resent FileName";
//				std::this_thread::sleep_for(std::chrono::seconds(2));
				data_sock << fileName;
				cout << "resent FileName";
//				data_sock >> fileName;								//Pass the fileName from the client socket to the Server
//				cout << fileName;
				string incomingStr;									//Variable to contain our incoming line
				string formattedStr;								//Variable to contain a section of our formatedline

//				ifstream inFile(fileName);							//Create input file stream to grab lines from file
//
//				while (getline(inFile, incomingStr)) {							//Start pulling lines from file
//
//					while(incomingStr.length() > 64){							//Loop as long as incoming string is longer then 64 characters
//						outgoingFrame.characters = incomingStr.substr(0,63);	//substring a portion of the string to be sent to the client
//						outgoingFrame.asciiSum();									//Get sum of ascii characters and convert it to binary for parity bit
//
//						if(rand() != 5 || counter != 5){
//							if(outgoingFrame.convertBinary(outgoingFrame.checkSum)%2 == 0){
//								outgoingFrame.parity = 0;
//							} else {
//								outgoingFrame.parity = 1;
//							}
//							data_sock << outgoingFrame.characters + std::to_string(outgoingFrame.parity);
//							counter++;
//						} else {
//							if(outgoingFrame.convertBinary(outgoingFrame.checkSum)%2 == 0){
//								outgoingFrame.parity = 1;
//							} else {
//								outgoingFrame.parity = 0;
//							}
//							counter = 0;
//						}
//						ack_sock >> ack;
//						if(ack == "NAK"){
//							if(outgoingFrame.convertBinary(outgoingFrame.checkSum)%2 == 0){
//								outgoingFrame.parity = 0;
//							} else {
//								outgoingFrame.parity = 1;
//							}
//							data_sock << outgoingFrame.characters + std::to_string(outgoingFrame.parity);
//						}
//					}
//					outgoingFrame.characters = incomingStr.substr(0,incomingStr.length()-1);
//					outgoingFrame.asciiSum();
//					if(outgoingFrame.convertBinary(outgoingFrame.checkSum)%2 == 0){
//						outgoingFrame.parity = 0;
//					} else {
//						outgoingFrame.parity = 1;
//					}
//					data_sock << outgoingFrame.characters + std::to_string(outgoingFrame.parity);
//				}
//				inFile.close();
			} catch (SocketException& e) {
				std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
			}
		}
	} catch (SocketException& e) {
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	return 0;
}
