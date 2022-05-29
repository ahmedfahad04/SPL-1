run: main.o prompt.o implementation.o execution.o commandAliasing.o suggestingCMDs.o slsh.o colorManagement.o prompt.o historyManagement.o commandAutoCompletion.o
	g++ -o run main.o prompt.o commandAliasing.o implementation.o execution.o suggestingCMDs.o slsh.o colorManagement.o historyManagement.o commandAutoCompletion.o -pthread 2> temp
	mv *.o obj

main.o: main.cpp
	g++ -c main.cpp 2> temp

slsh.o: slsh.cpp
	g++ -c slsh.cpp 2> temp

prompt.o: prompt.cpp shell.h
	g++ -c prompt.cpp 2> temp

implementation.o: implementation.cpp shell.h
	g++ -c implementation.cpp 2> temp

execution.o: execution.cpp shell.h
	g++ -c execution.cpp 2> temp

suggestingCMDs.o: suggestingCMDs.cpp shell.h
	g++ -c suggestingCMDs.cpp 2> temp

colorManagement.o: colorManagement.cpp
	g++ -c colorManagement.cpp 2> temp

commandAliasing.o: commandAliasing.cpp
	g++ -c commandAliasing.cpp 2> temp

historyManagement.o: historyManagement.cpp
	g++ -c historyManagement.cpp 2> temp

commandAutoCompletion.o: commandAutoCompletion.cpp
	g++ -c commandAutoCompletion.cpp 2> temp

clean: 
	rm run
	rm -r obj
	mkdir obj
	
line:
	wc -l *.*



# disable all warnings
CXXFLAGS += -w
