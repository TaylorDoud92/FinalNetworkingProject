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
	Frame( std::string characters, char checkSum, char parity);
	virtual ~Frame( std::string characters, char checkSum, char parity);

private:
	std::string characters;
	char checkSum;
	char parity;
};

#endif /* FRAME_H_ */
