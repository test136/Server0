build: Server0.o
	g++ -luv -g -o server main.cpp Server0.o

Server0.o: Server0.cpp Server0.h
	g++ -luv -g -o Server0.o Server0.cpp -c

.PHONY: clean
clean:
	rm server
