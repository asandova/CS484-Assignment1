all: Project1

Project1: main.o LargeNum.o Proability.o
	g++ main.o LargeNum.o Proability.o -o Project1

main.o:
	g++ -c main.cpp

LargeNum.o: LargeNum.h
	g++ -c LargeNum.cpp

proability.o: Proability.h
	g++ -c Proability.cpp

clean:
	rm -rf *.o
	rm Project1