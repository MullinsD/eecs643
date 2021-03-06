pipeline : main.o Pipeline.o Instruction.o
	g++ -std=c++11 main.o Pipeline.o Instruction.o -o pipeline

main.o : main.cpp Pipeline.h Instruction.h
	g++ -std=c++11 -c main.cpp

Instruction.o : Instruction.cpp Instruction.h
	g++ -std=c++11 -c Instruction.cpp

Pipeline.o : Pipeline.cpp Pipeline.h Instruction.h
	g++ -std=c++11 -c Pipeline.cpp
