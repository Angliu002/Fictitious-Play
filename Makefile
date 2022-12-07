all: ficplay

ficplay: ficplay.cpp
	g++ -o ficplay ficplay.cpp

clean: 
	rm ficplay