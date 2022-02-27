#include "DssParser.h"

DssParser::DssParser() {
    sResult = "";
}

void DssParser::parseData(string file) {
    sResult = "";
	unsigned int hStart  = 0;
	unsigned int shStart = 12;
	unsigned int lnStart = 12 + 24;
	unsigned int lStart  = 12 + 24 + 4;
	unsigned int lineLength = 3 + 4*4;
	unsigned int i = 0;
	//$sub = array();
	vector<BYTE> sub;
	sub.push_back(0);
	sub.push_back(0);
	sub.push_back(0);
	sub.push_back(0);
	vector<BYTE> linesData;
	vector<BYTE> line;
	
	for (int d = 0; d < 19; d++) {
		line.push_back(0);
	}
	
	bool lineStart = false;
	bool lineEnd = false;
	int lineNum = floor((filesize(file) - lStart) / lineLength);
	unsigned int krat = 0;
	unsigned int dk = 0;
	unsigned int di = 0;
	string hstr = "";
	//FILE *fileHandler = fopen($file, 'r');
    FILE *fileHandler = fopen(file.c_str(),"rb");
    if (!fileHandler ) {
        lib.qMessageBox("", "none");
    }
	vector<BYTE> header;
	vector<BYTE> subheader;
	
	
	int countInsert = 0;
	BYTE buf[1] = {0};
	
	while (!feof(fileHandler)) {
		fread (buf, 1, 1, fileHandler);
		BYTE byte = buf[0];
		
		if ((i >= 0) && (i < shStart))  {
			header.push_back(byte);
		} else if ((i >= shStart) && (i < lnStart)) {
			if (i == shStart) {
				string hstr;
				for (int m = 0; m < header.size(); m++) {
					char ch = (char)header[m];
					hstr += ch;
				}
				if (substr(hstr, 3, 8) != "DSHP0JMX") {
					//cout << "Fail: header = " << substr(hstr, 3, 5) << "\n";
					return;
				} else {
					//cout << "Header = " << substr(hstr, 3, 8) << "\n";
				}
			}
			subheader.push_back(byte);
		} else if ((i >= lnStart) && (i < lStart)) {
			sub[3 - (i - lnStart)] = byte;
		} else if ((i >= lStart) && (i < (lStart + (lineNum) * lineLength + 1))) {
			if (i == lStart) {
				lineNum = this->_readUnsignedInt(sub);
                sResult += QString::number(lineNum) + ",";
			}
			line[dk] = byte;
			if (dk == lineLength - 1) {
                    DssLine *dssLine = new DssLine(line, false);

                    sResult += QString::number(dssLine->startX, 'g', 14) + ",";
                    sResult += QString::number(dssLine->startY, 'g', 14) + ",";
                    sResult += QString::number(dssLine->endX, 'g', 14) + ",";
                    sResult += QString::number(dssLine->endY, 'g', 14) + ",";
                    sResult += QString::number(dssLine->color) + ",";
                    this->lines.push_back( new DssLine(line) );

				countInsert++;
				dk = -1;
				lineEnd = true;
			} else {
				lineEnd = false;
			}
			
			dk++;
		}
		i++;
	}
	fclose(fileHandler);
}
	/**
	 * Считывает целое число из массива байт в big endian порядке
	 * @param array $data ассив с целыми числами - значениями байт составляющих целое
	 * @return int
	*/
	
unsigned int DssParser::_readUnsignedInt(vector<BYTE> data) {
	unsigned int ok = 0;
	
	for (int i = 0; i < data.size(); i++) {
		ok += (short)data[i];
		if (i < 3) {
			ok = ok << 8;
		}
	}
	return ok;
}
