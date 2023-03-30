#include "inotifystd.h"

/*string currentTarget;
int id; // = -1 on init and fail
int fd;*/

bool InotifyStd::startWatch(string target) {
    if (this->id != -1) {
        this->stopWatch();
    }

    /* Инициализация Inotify*/
    this->fd = inotify_init();
    if ( this->fd < 0 ) {
        return false;
    }

     /* добавим наблюдение для директории, заданной первым параметром командной строки */
    this->id = inotify_add_watch(this->fd, target.c_str(), IN_CREATE | IN_MODIFY | IN_DELETE);

    if (this->id  == -1)
    {
        close(this->fd);
        return false;
    }
    this->currentTarget = target;

    return true;
}

// return false if events more than sz
bool InotifyStd::getModifyList(string* list, unsigned int sz, unsigned int &filledSz)
{
    // clear array
    unsigned int k;
    for (k = 0; k < sz; k++) {
        list[k] = "";
    }
    filledSz = 0;

    int i = 0;
    int MAX_EVENTS  = 1024; /*Максимальное кличество событий для обработки за один раз*/
    int LEN_NAME  = 4096; /*Будем считать, что длина имени файла не превышает 4096 символов (в оригинале 16)*/
    int EVENT_SIZE = ( sizeof (struct inotify_event) ); /*размер структуры события*/
    int BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )); /*буфер для хранения данных о событиях*/
    char buffer[BUF_LEN];

    int length = read(this->fd, buffer, BUF_LEN);

    if ( length < 0 ) {
        return false;
    }
    k = 0;
    while ( i < length ) {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
        if ( event->len ) {
            if ( event->mask & IN_CREATE) {
                if (event->mask & IN_ISDIR)
                        // printf( "The directory %s was Created.\n", event->name );
                    list[k] = "cd" + string(event->name);
                    else
                        // printf( "The file %s was Created with WD %d\n", event->name, event->wd );
                    list[k] = "cf" + string(event->name);
                    k++;
                }

                if ( event->mask & IN_MODIFY) {
                    if (event->mask & IN_ISDIR)
                        // printf( "The directory %s was modified.\n", event->name );
                        list[k] = "md" + string(event->name);
                    else
                        // printf( "The file %s was modified with WD %d\n", event->name, event->wd );
                        list[k] = "mf" + string(event->name);
                    k++;
                }

                if ( event->mask & IN_DELETE) {
                    if (event->mask & IN_ISDIR)
                        // printf( "The directory %s was deleted.\n", event->name );
                        list[k] = "dd" + string(event->name);
                    else
                        // printf( "The file %s was deleted with WD %d\n", event->name, event->wd );
                        list[k] = "df" + string(event->name);
                    k++;
                }

                i += EVENT_SIZE + event->len;

                if (k >= sz) {
                    filledSz = k;
                    return false;
                }
       }
   }// end while
   filledSz = k;

   return true;
}

void InotifyStd::stopWatch() {
    /* Освобождение ресурсов*/
    this->currentTarget = "";
   if (this->fd > 0 && this->id > -1) {
       inotify_rm_watch(this->fd, this->id);
   }
   if (this->fd > 0) {
       close(this->fd);
   }

   this->fd = -1;
   this->id = -1;
}

// end inotify
