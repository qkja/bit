.PHONY:all
all:mybin mycmd

mycmd:main.cpp
	g++ -o $@ $^
mybin:test.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f mybin mycmd
