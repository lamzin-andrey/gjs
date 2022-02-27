#include "DssLine.h"

DssLine::DssLine(std::vector<BYTE> bytes, bool debug) {
    this->debug = debug;
	unsigned int color;
	this->color = color = (bytes[2] * 256 * 256) + (bytes[1] * 256) + bytes[0];
	double startX, startY, endX, endY;
	this->startX = startX = this->_readPoint(bytes, 3);
	this->startY = startY = -1 * this->_readPoint(bytes, 7);
	this->endX = endX = this->_readPoint(bytes, 11);
	this->endY = endY = -1 * this->_readPoint(bytes, 15);
}

float DssLine::_readPoint(vector<BYTE>bytes, int start) {
    int order[] = {0, 1, 2, 3};
	
	//BYTE result[] = {0x00, 0x00, 0x00, 0x00};
	BYTE result[] = {0, 0, 0, 0};
	
	for (int i = 0, j = start; i < 4; i++) {
		result[ order[i] ] = bytes[j];
		if (this->debug) {
			cout << (short)bytes[j] << "\n";
		}
		j++;
    }
	float fNum;
    fNum = *(float*) result;
	return fNum;
}
