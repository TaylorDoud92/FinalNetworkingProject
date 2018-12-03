#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Frame.h"

using namespace std;

int main(int argc, int argv[]) {

	Frame incomingFrame;
	Frame outgoingFrame;
	int counter = 0;
	std::string ack;
	srand(5);

	cout << "running....\n";

	try {
		// Create the socket and pass port number

		ServerSocket dataChannel(30000);

		ServerSocket ackChannel(30001);
		string fileName;

		cout << "Created Server Socket... \n";

		cout << "Reading File... \n";

		while (true) {
			ServerSocket data_sock;
			ServerSocket ack_sock;
			dataChannel.accept(data_sock);			//Start listening for data Socket and ack Socket
			ackChannel.accept(ack_sock);

			// For multiple threading, you need to create
			// a new thread here and pass new_sock to it.
			// The thread will use new_sock to communicate
			// with the client.

			try {
				data_sock >> fileName;								//Pass the fileName from the client socket to the Server
				string incomingStr;									//Variable to contain our incoming line
				string formattedStr;								//Variable to contain a section of our formatedline

				ifstream inFile(fileName);							//Create input file stream to grab lines from file

				while (getline(inFile, incomingStr)) {							//Start pulling lines from file

					while(incomingStr.length() > 64){							//Loop as long as incoming string is longer then 64 characters
						outgoingFrame.characters = incomingStr.substr(0,63);	//substring a portion of the string to be sent to the client
						outgoingFrame.asciiSum();									//Get sum of ascii characters and convert it to binary for parity bit

						if(rand() != 5 || counter != 5){
							if(outgoingFrame.convertBinary(outgoingFrame.checkSum)%2 == 0){
								outgoingFrame.parity = 0;
							} else {
								outgoingFrame.parity = 1;
							}
							data_sock << outgoingFrame.characters + std::to_string(outgoingFrame.parity);
							counter++;
						} else {
							if(outgoingFrame.convertBinary(outgoingFrame.checkSum)%2 == 0){
								outgoingFrame.parity = 1;
							} else {
								outgoingFrame.parity = 0;
							}
							counter = 0;
						}
						ack_sock >> ack;
						if(ack == "NAK"){
							if(outgoingFrame.convertBinary(outgoingFrame.checkSum)%2 == 0){
								outgoingFrame.parity = 0;
							} else {
								outgoingFrame.parity = 1;
							}
							data_sock << outgoingFrame.characters + std::to_string(outgoingFrame.parity);
						}
					}
					outgoingFrame.characters = incomingStr.substr(0,incomingStr.length()-1);
					outgoingFrame.asciiSum();
					if(outgoingFrame.convertBinary(outgoingFrame.checkSum)%2 == 0){
						outgoingFrame.parity = 0;
					} else {
						outgoingFrame.parity = 1;
					}
					data_sock << outgoingFrame.characters + std::to_string(outgoingFrame.parity);
				}
				inFile.close();
			} catch (SocketException& e) {
				std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
			}
		}
	} catch (SocketException& e) {
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	return 0;
}
