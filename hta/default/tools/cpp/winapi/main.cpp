#include <windows.h>
#include <string.h>
#include "dphp.h"

using namespace dphp;

void _WApiSetSystemTime(int argc, char** argv);

void _WApiSetSystemTime(int argc, char** argv){
	string stdErr("SetSystemTime required 2 argument: YYYY-MM-DD and HH:MM:SS\n");
	if (argc != 4) {
		file_put_contents("lastError.txt", stdErr, 8);
		return;
	}
	string date = string(argv[2]);
	string time = string(argv[3]);
	vector<string> aDate = explode("-", date);
	vector<string> aTime = explode(":", time);
	
	if (aDate.size() != 3 || aTime.size() != 3) {
		file_put_contents("lastError.txt", stdErr, 8);
		return;
	}
	UtilsStd Lib;
	int h = Lib.strToInt(aTime[0]) - 3;
	if (h < 0) {
		h = 24 + h; 
	}
	
	SYSTEMTIME vsys;
	vsys.wYear = Lib.strToInt(aDate[0]);
	vsys.wMonth = Lib.strToInt(aDate[1]);
	vsys.wDay = Lib.strToInt(aDate[2]);
	vsys.wHour = h;// 20 is 23, 23 is 2, 0 is 3
	vsys.wMinute = Lib.strToInt(aTime[1]);
	vsys.wSecond = Lib.strToInt(aTime[2]);
	vsys.wMilliseconds = 1;
	SetSystemTime(&vsys);
}

int main (int argc, char** argv) {
	string stdErr("Usage: winapi.exe functionName arg1 arg2 arg3 ...\nSee released winapi functions in functions.txt\n");
	if (argc < 2) {
		file_put_contents("lastError.txt", stdErr, 8);
		return 0;
	}
	string functionName = string(argv[1]);
	if (functionName == "SetSystemTime") {
		_WApiSetSystemTime(argc, argv);
		return 0;
	}
	
	string err = string("Unknown function ");
	err += functionName + "\n";
	file_put_contents("lastError.txt", err, 8);
	
	return 0;
}
