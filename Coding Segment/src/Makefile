run: main.o prompt.o implementation.o execution.o suggestingCMDs.o slsh.o
	g++ main.o prompt.o implementation.o execution.o suggestingCMDs.o slsh.o -o run
	mv *.o obj

main.o: main.cpp
	g++ -c main.cpp

slsh.o: slsh.cpp
	g++ -c slsh.cpp

prompt.o: prompt.cpp shell.h
	g++ -c prompt.cpp 

implementation.o: implementation.cpp shell.h
	g++ -c implementation.cpp

execution.o: execution.cpp shell.h
	g++ -c execution.cpp

suggestingCMDs.o: suggestingCMDs.cpp shell.h
	g++ -c suggestingCMDs.cpp



clean: 
	rm run
	rm -r obj
	mkdir obj
	

line:
	wc -l *.*
