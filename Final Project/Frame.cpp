/*
 * Frame.cpp
 *
 *  Created on: Nov. 29, 2018
 *      Author: taylor
 */

#include "Frame.h"

Frame::Frame(std::string characters, char checkSum, char parity) {
	Frame::characters = characters;
	Frame::parity = parity;
	Frame::checkSum = checkSum;
}

Frame::~Frame(std::string characters, char checksum, char parity) {
}

