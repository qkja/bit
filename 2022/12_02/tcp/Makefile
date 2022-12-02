.PHONY:all
all:tcpClient tcpServer

tcpClient:tcpClient.cc
	g++ -o $@ $^ -std=c++11

tcpServer:tcpServer.cc
	g++ -o $@ $^ -std=c++11
	
.PHONY:clean
clean:
	rm -f tcpServer tcpClient