.PHONY:all
all:clientTcp serverTcpd
Method=-DMY_SELF

clientTcp: clientTcp.cc
	g++ -o $@ $^ $(Method) -std=c++11 -ljsoncpp
serverTcpd:serverTcp.cc
	g++ -o $@ $^ $(Method) -std=c++11 -lpthread -ljsoncpp

.PHONY:clean
clean:
	rm -f serverTcpd clientTcp