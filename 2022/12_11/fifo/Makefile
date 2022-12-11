.PHONY:all
all:clientFifo serverFifo

clientFifo:clientFifo.cc
	g++ -std=c++11 -o $@ $^

serverFifo:serverFifo.cc
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -f serverFifo clientFifo fifo
