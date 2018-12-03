/*
 * Frame.h
 *
 *  Created on: Nov. 29, 2018
 *      Author: taylor
 */
#include <string>

#ifndef FRAME_H_
#define FRAME_H_

class Frame {
public:
	Frame(std::string characters, int checkSum, int parity);
	Frame();
	virtual ~Frame();

	int asciiSum();
	int convertBinary(int i);
	bool compareParity();

	std::string characters;
	char checkSum;
	char parity;
};

#endif /* FRAME_H_ */
