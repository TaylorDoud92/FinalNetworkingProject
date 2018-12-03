/*
 * Frame.cpp
 *
 *  Created on: Nov. 29, 2018
 *      Author: taylor
 */

#include "Frame.h"

Frame::Frame(std::string characters, int checkSum, int parity) {
	Frame::characters = characters;
	Frame::parity = parity;
	Frame::checkSum = checkSum;
}

Frame::Frame(){
	Frame::characters = "";
	Frame::parity = '0';
	Frame::checkSum = '0';
}

Frame::~Frame() {
}

int Frame::asciiSum(){
	checkSum = 0;
	for(int i=0;i < characters.length();i++){
		checkSum = checkSum + static_cast<int>(characters[i]);
	}
	return checkSum;
}

int Frame::convertBinary(int i){
	int sum = 0;
	while(i){
		sum += i & 1;
		i >>=1;
	}
	return sum;
}

bool Frame::compareParity(){
	if((convertBinary(checkSum)+parity)%2 == 0){
		return true;
	}
	return false;
}

