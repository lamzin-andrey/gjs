#include "php.h"

int filesize(std::string filename) // path to file
{
    FILE *p_file = NULL;
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

string substr(string s, int start, int length) {
	string r = "";
	int L = s.length();
	if (start < L) {
		// start + length < L
		for (int i = start; i < start + length; i++) {
			if (i > L - 1) {
				return r;
			}
			r += s[i];
		}
	}
	return r;
}
