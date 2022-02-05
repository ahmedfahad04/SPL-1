run: main.o prompt.o operations.o cmd_processing.o
	g++ main.o prompt.o operations.o cmd_processing.o -o run

main.o: main.cpp
	g++ -c main.cpp

prompt.o: prompt.cpp shell.h
	g++ -c prompt.cpp 

operations.o: operations.cpp shell.h
	g++ -c operations.cpp

cmd_processing.o: cmd_processing.cpp shell.h
	g++ -c cmd_processing.cpp

clean:
	rm *.o run 