all: Project1

Project1: main.o LargeNum.o Proability.o
	g++ main.o LargeNum.o Proability.o -o Project1

Optimize1: main.o LargeNum.o Proability.o
	g++ -o1 main.o LargeNum.o Proability.o -o Project1

Optimize2: main.o LargeNum.o Proability.o
	g++ -o2 main.o LargeNum.o Proability.o -o Project1

Optimize3: main.o LargeNum.o Proability.o
	g++ -o3 main.o LargeNum.o Proability.o -o Project1

main.o: LargeNum.h Proability.h
	g++ -c main.cpp

LargeNum.o: LargeNum.h
	g++ -c LargeNum.cpp

Proability.o: Proability.h
	g++ -c Proability.cpp

clean:
	rm -rf *.o
	rm Project1