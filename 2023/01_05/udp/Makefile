.PHONY:all
all:udpServer udpClient
udpServer:udpServer.cc
	g++ -std=c++11 -o $@ $^ 
udpClient:udpClient.cc
	g++ -std=c++11 -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f udpClient udpServer