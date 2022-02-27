#ifndef __DSS_PARSER__
#define __DSS_PARSER__

#include  <iostream>
#include  <vector>
#include  <math.h>
#include  "php.h"

#include  "DssLine.h"

#include  <stdlib.h>
#include  <stdio.h>

#include <QString>


#include  "../../lib/utils.h"

using namespace std;

//typedef unsigned char BYTE;//TODO remove in win

/**
 * @author Andrey Lamzin lamzin80@mail.ru
 * @class DssParser Парсит бинарный dss файл в массив данных
*/
class DssParser {
    public:
        DssParser();
        vector<DssLine*> lines;
        /** числа, разделенные запятой. Первое число количество линий, далее цвет,startX,startY,endX,endY */
        QString sResult;

	
	/** @param string $file путь к dss файлу*/
    void parseData(string file);
	/**
	 * Считывает целое число из массива байт в big endian порядке
	 * @param array $data ассив с целыми числами - значениями байт составляющих целое
	 * @return int
	*/
	private:
    Utils lib;
	unsigned int _readUnsignedInt(vector<BYTE> data);
};

#endif
