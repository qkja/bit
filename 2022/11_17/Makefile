.PHONY:all
all:IpcShmCli IpcShmSer

IpcShmCli:IpcShmCli.cc
	g++ -std=c++11 -o $@ $^
IpcShmSer:IpcShmSer.cc
	g++ -std=c++11 -o $@ $^
.PHONY:clean
clean:
	rm -f IpcShmCli IpcShmSer
