.PHONY:all
all:serverTcp clientTcp
serverTcp:serverTcp.cc
	g++ -std=c++11 -o $@ $^ -lpthread
clientTcp:clientTcp.cc
	g++ -std=c++11 -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f serverTcp clientTcp