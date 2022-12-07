all: .init ficplay

.init:
	chmod +x test.sh
	@touch .init

ficplay: ficplay.cpp
	g++ -o ficplay ficplay.cpp

clean:
	@rm .init
	rm ficplay