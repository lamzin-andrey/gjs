remove winapi.exe
g++ -c utilsstd.cpp -o utilsstd.o
g++ -c dphp.cpp -o dphp.o
g++ -c cuter.cpp -o main.o
g++ -c main.cpp -o main.o
g++ -Xlinker utilsstd.o dphp.o main.o -o winapi.exe
winapi SetSystemTime 2019-05-05 17:55:00
date
time

