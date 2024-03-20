#ifndef DPHP_H
#define DPHP_H

#define FILE_APPEND 9

#include "utilsstd.h"
#include <unistd.h>
#include <vector>
#include <ctime>



namespace dphp {
	string date(string fmt, long ts = 0);
	//9 for append
	string file_get_contents(string file);
	int file_put_contents(string file, string data, int mode = 0);
	string str_replace(string search, string replace, string subject, int &count);
	string str_replace(string search, string replace, string subject);
	string __str_replace(string search, string replace, string subject, int &count);
	//TODO can use php.ini в котором может быть строка fgets_buf_size=N
	string fgets(FILE* f, unsigned int  = 2048);
	//return -1 if not found
	int strpos(string haystack, string needle, unsigned int offset = 0);
	bool file_exists(string filename);
	vector<string> explode(string delimeter, string source, unsigned int maxLength = 1000000);
	string implode(string glue, vector<string> pieces);
	vector<string> unset(vector<string> &a, unsigned int index);
}

#endif
