#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int asciiSum(string s){
	int sum = 0;
	for(int i=0;i < s.length();i++){
		sum = sum + static_cast<int>(s[i]);
	}
	return sum;
}

int convertBinary(int i){
	int sum = 0;
	while(i){
		sum += i & 1;
		i >>=1;
	}
	return sum;
}

int main(int argc, int argv[]) {

	cout << "running....\n";

	try {
		// Create the socket and pass port number

		ServerSocket dataChannel(30000);

		ServerSocket ackChannel(30000);

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
				string fileName;									//Create a string to hold the incoming fileName
				data_sock >> fileName;								//Pass the fileName from the client socket to the Server
				string incomingStr;									//Variable to contain our incoming line
				string formattedStr;								//Variable to contain a section of our formatedline

				ifstream inFile(fileName);							//Create input file stream to grab lines from file

				while (getline(inFile, incomingStr)) {				//Start pulling lines from file

					while(incomingStr.length() > 64){				//Loop as long as incoming string is longer then 64 characters
						formattedStr = incomingStr.substr(0,63);	//substring a portion of the string to be sent to the client
						convertBinary(asciiSum(formattedStr));		//Get sum of ascii characters and convert it to binary for parity bit

						data_sock <<
					}



					if(incomingStr.length() > 64){					//Check to see if line is greater then 64 characters long.
						formattedStr = incomingStr.substr(0,63);
					} else {
						formattedStr = incomingStr.substr(0,incomingStr.length()-1);
					}




					data_sock << fileName;
				}
				inFile.close();
			} catch (SocketException&) {
			}
		}
	} catch (SocketException& e) {
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	return 0;
}
