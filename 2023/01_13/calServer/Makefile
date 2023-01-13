.PHONY:all
all:clientTcp serverTcpd

clientTcp: clientTcp.cc
	g++ -o $@ $^ -std=c++11
serverTcpd:serverTcp.cc
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean
clean:
	rm -f serverTcpd clientTcp