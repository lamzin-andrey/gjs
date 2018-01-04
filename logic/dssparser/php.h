#ifndef __PHP_COMPATIBLE__
#define __PHP_COMPATIBLE__

typedef unsigned char BYTE;


#include  <iostream>
#include  <string>

#include  <stdlib.h>
#include  <stdio.h>
using namespace std;

int filesize(std::string filename);
string substr(string s, int start, int length);

#endif
