//Простой список  запущенных процессов на cpp (id\tname.exe)
//Компилировалось с помощью g++ for windows c++ 98
//Заголовочные файлы явно многие лишние
// -mwindows зесь при компиляции не нужен, так как пропадает stdout

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <io.h>
using namespace std;

void procList(string processFileName) {
	PROCESSENTRY32 Entry;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    Entry.dwSize = sizeof(Entry);
    Process32First(hSnapshot, &Entry);
    do {
		string a = Entry.szExeFile;		
		if (processFileName.length() > 0 && a == processFileName) {
			cout << Entry.th32ProcessID << "\t" << Entry.szExeFile << "\n";
		} else if(processFileName.length() == 0){
			cout << Entry.th32ProcessID << "\t" << Entry.szExeFile << "\n";
		}
		
    } while (Process32Next(hSnapshot, &Entry ) );	
	
}


int main(int argc, char** argv) {
	string arg = "";
	if (argc > 1) {
		arg = string(argv[1]);
	}
	
	if (arg == "--help" || arg == "/?") {
		cout << "Usage: sps [filter]\n"
			 << "filter may be one process name, for example cmd.exe:\n"
			 << ">sps cmd.exe\n\n"
			 << "if filter not set, will display all processes\n";
		return 0;
	}
	
	procList(arg);
	return 0;
}
