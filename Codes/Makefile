run: main.o prompt.o operations.o 
	g++ main.o prompt.o operations.o -o run

main.o: main.cpp
	g++ -c main.cpp

prompt.o: prompt.cpp shell.h
	g++ -c prompt.cpp 

operations.o: operations.cpp shell.h
	g++ -c operations.cpp