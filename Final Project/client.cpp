#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <bitset>
#include "Frame.h"

int asciiSum(std::string s){
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
	
	std::string ipaddress;

	try {

		std::cout << "Please Enter IP address of server" << "/n";
		std::cin >> ipaddress;

		// Replace "localhost" with the hostname
		// that you're running your server.
		ClientSocket dataChannel("localhost", 30000);
		ClientSocket ackChannel("localhost", 30000);
		
		
		std::string reply;

		// Usually in real applications, the following
		// will be put into a loop.
		try {

			dataChannel << "Test message.";
			dataChannel >> reply;

		} catch (SocketException&) {
		}

		std::cout << "We received this response from the server:\n\"" << reply
				<< "\"\n";

	} catch (SocketException& e) {

		std::cout << "Exception was caught:" << e.description() << "\n";

	}

	return 0;
}
