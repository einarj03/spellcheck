spell: main.o spell.o
	g++ -Wall -g main.o spell.o -o spell

main.o: main.cpp spell.h
	g++ -Wall -c main.cpp

spell.o: spell.cpp spell.h
	g++ -Wall -c spell.cpp