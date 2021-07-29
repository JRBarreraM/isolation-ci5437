main:	clean utils.hpp
		g++ -O3 -Wall -o main main.cpp

clean:
		rm -f main