#ifndef __DSS_LINE__
#define __DSS_LINE__

#include  <iostream>
#include  <vector>
#include  "php.h"
using namespace std;

//typedef unsigned char BYTE;//TODO remove in win

/**
 * @author Andrey Lamzin lamzin80@mail.ru
 * @class DssParser Создает объект линии из массива байт
*/
class DssLine {
	/** @property float startX*/
	public:
		bool debug;
		double startX;
		/** @property float endX*/
		double endX;
		/** @property float startY*/
		double startY;
		/** @property float endY*/
		double endY;
		/** @property int color*/
		unsigned int color;
	/**
	 * @param array $bytes
	*/
    DssLine(std::vector<BYTE> bytes, bool debug = false);
	/**
	 * @desc считать точку из массива байт
	 * @param array $bytes массив байт
	 * @param int   $start с какого байта начинать
	 * @return double
	*/
	float _readPoint(vector<BYTE>bytes, int start);
	
};
#endif
