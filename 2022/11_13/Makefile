.PHONY:all
all:myexec mycmd

myexec:myexec.c
	g++ -std=c++11 -o $@ $^
mycmd:mycmd.cpp
	g++ -std=c++11 -o $@ $^

.PHONY:clean
clean:
	rm -f myexec mycmd
