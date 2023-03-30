#ifndef INOTIFYSTD_H
#define INOTIFYSTD_H
#include <string>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <limits.h>
#include <unistd.h>


//#include "string.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>

#include <zlib.h>


using namespace std;

class InotifyStd
{
public:
    InotifyStd() {
        // inotify variables
        this->currentTarget = "";
        this->id = -1;
        this->fd = -1;
        // end inotify variables
    }


    // inotify variables
    string currentTarget;
    int id; // = -1 on init and fail
    int fd;
    bool startWatch(string target);
    // return false if events more than sz
    bool getModifyList(string* list, unsigned int sz, unsigned int &filledSz);
    void stopWatch();
    // end inotify variables

    


// private:

};

#endif
