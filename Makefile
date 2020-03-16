all: hw1-3

hw1-3:
	g++ -o hw1-3 hw1-3.cpp
	g++ -o hw1-2 hw1-2.cpp
	g++ -o hw1-1 hw1-1.cpp

clean:
	rm hw1-1 hw1-2 hw1-3
