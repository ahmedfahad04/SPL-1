run: main.o prompt.o implementation.o cmd_processing.o suggestingCMDs.o
	g++ main.o prompt.o implementation.o cmd_processing.o suggestingCMDs.o -o run

main.o: main.cpp
	g++ -c main.cpp

prompt.o: prompt.cpp shell.h
	g++ -c prompt.cpp 

implementation.o: implementation.cpp shell.h
	g++ -c implementation.cpp

cmd_processing.o: cmd_processing.cpp shell.h
	g++ -c cmd_processing.cpp

suggestingCMDs.o: suggestingCMDs.cpp shell.h
	g++ -c suggestingCMDs.cpp

clean:
	rm *.o run 

line:
	wc -l *.*