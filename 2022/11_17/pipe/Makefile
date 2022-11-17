.PHONY:all
all:clientFifo serverFifo 

clientFifo:clientFifo.cpp
	g++ -std=c++11 -o $@ $^
serverFifo:serverFifo.cpp
	g++ -std=c++11 -o $@ $^
.PHONY:clean
clean:
	rm clientFifo serverFifo
