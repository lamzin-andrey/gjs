#include <string>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
using namespace std;

void writeStr(string s, string filename);
string sys(string sys, string sock);
string read(string filename, char stop = '\0');
unsigned long filesize(string file);
void Char(string s, char* &dest);

int main(int argc, char* argv[]) {
	writeStr("#! /bin/bash\nzenity --info\n", "/tmp/test.sh");
	sys("chmod 766 /tmp/test.sh", "/tmp/amarket.sock");
	sys("/tmp/test.sh", "/tmp/amarket.sock");
	return 0;
}

void writeStr(string s, string filename)
{
//Вывод в файл
  ofstream t;
  t.open(filename.c_str(), ios:: out);
  t << s;
  t.close();
}

string sys(string sys, string sock) {
        sys += " > " + sock;
        //char* s = new char[sys.length() + 1];
        //Char(sys, s);
        system(sys.c_str());

        unsigned long sz = filesize(sock);
        while (true) {
                system("sleep 1");
                unsigned long csz = filesize(sock);
                if (csz == sz) {
                        string s = read(sock);
                        return s;
                }
                sz = csz;                
        }
        return "";
}

string read(string filename, char stop)
{
	unsigned int i;
   string s = "";
   char* path = new char [filename.length()+1];
   for ( i = 0; i < filename.length(); i++)
	   path[i]= filename[i]; 
	   path[i] = '\0';
  ifstream t;
  t.open(path, ios:: in);
  
  string q = "";
  while ( std::getline(t, q ) ) {
	  s += q + "\n";
	  //for (int i = q.length(); i < 32000; i++) res[i] = '\0';
	  q = "";
  }
  t.close();
  
  if (s.length() > 0)
	s = s.substr(0, s.length() - 1);
  //cout <<"\nReport = '" << s<< "'\n";
  return s;
}


unsigned long  filesize(string file) {
        char* c_file = new char[file.length() + 1];
        Char(file, c_file);
        struct stat state;
        stat(c_file, &state);
        return (unsigned long)state.st_size;
}

void Char(string s, char* &dest)
{
 dest = new char[s.length()];
 int i = 0;
 for (i = 0;  i < s.length(); i++) 	dest[i] = s[i]; 
 dest[i] = '\0';
}
