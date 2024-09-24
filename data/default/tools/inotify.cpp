#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <limits.h>
#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

#define MAX_EVENTS 1024 /*Максимальное кличество событий для обработки за один раз*/
#define LEN_NAME 4096 /*Будем считать, что длина имени файла не превышает 4096 символов*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*размер структуры события*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*буфер для хранения данных о событиях*/


string buildDirFromArgs(int argc, char **argv);

int main( int argc, char **argv ) 
{
	int length, i = 0, wd;
	int fd;
	char buffer[BUF_LEN];

	 /* Инициализация Inotify*/
	fd = inotify_init();
	if ( fd < 0 ) {
		// perror( "Couldn't initialize inotify");
		return 0;
	}
	
	string targetDir = buildDirFromArgs(argc, argv);
	// printf("%s\n", targetDir.c_str());

	 /* добавим наблюдение для директории, заданной первым параметром командной строки */
	wd = inotify_add_watch(fd, targetDir.c_str(), IN_CREATE | IN_MODIFY | IN_DELETE); 

	if (wd == -1)
	{
		// printf("Couldn't add watch to %s\n",argv[1]);
		return 0;
	}
	else
	{
		// printf("Watching:: %s\n",argv[1]);
	}

	/* бесконечный цикл*/
	while(1)
	{
		i = 0;
		length = read(fd, buffer, BUF_LEN );  

		if ( length < 0 ) {
			// perror("read");
		}  

		while ( i < length ) {
		struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
		if ( event->len ) {
			if ( event->mask & IN_CREATE) {
				if (event->mask & IN_ISDIR) {
					// printf( "cd%s\n", event->name );       
					// cout << "cd" << event->name << "\n";
					string msg(event->name);
					msg = "echo cd" + msg + " >> /opt/qt-desktop-js/default/tools/inotifyd.output";
					system(msg.c_str());
				} else {
					// printf( "cf%s\n", event->name);
					// cout << "cf" << event->name << "\n";
					string msg(event->name);
					msg = "echo cf" + msg + " >> /opt/qt-desktop-js/default/tools/inotifyd.output";
					system(msg.c_str());
				}
			}

			if ( event->mask & IN_MODIFY) {
				if (event->mask & IN_ISDIR) {
					// printf( "md%s\n", event->name);
					// cout << "md" << event->name << "\n";
					string msg(event->name);
					msg = "echo md" + msg + " >> /opt/qt-desktop-js/default/tools/inotifyd.output";
					system(msg.c_str());
				}
				else {
					// printf( "mf%s\n", event->name);
					// cout << "mf" << event->name << "\n";
					string msg(event->name);
					msg = "echo mf" + msg + " >> /opt/qt-desktop-js/default/tools/inotifyd.output";
					system(msg.c_str());
				}
			}
          
			if ( event->mask & IN_DELETE) {
				if (event->mask & IN_ISDIR) {
					// printf( "dd%s\n", event->name );       
					cout << "dd" << event->name << "\n";
					string msg(event->name);
					msg = "echo dd" + msg + " >> /opt/qt-desktop-js/default/tools/inotifyd.output";
					system(msg.c_str());
				} else {
					// printf( "df%s\n", event->name);
					// cout << "df" << event->name << "\n";
					string msg(event->name);
					msg = "echo df" + msg + " >> /opt/qt-desktop-js/default/tools/inotifyd.output";
					system(msg.c_str());
				}
			}
				i += EVENT_SIZE + event->len;
			}
		}
		
		sleep(00);
	}

 /* Освобождение ресурсов*/
inotify_rm_watch( fd, wd );
close(fd);

return 0;
}


string buildDirFromArgs(int argc, char **argv)
{
	string r("");
	for (int i = 1; i < argc; i++) {
		string part(argv[i]);
		if (i > 1) {
			r += " " + part;
		} else {
			r += part;
		}
	}
	
	return r;
}
