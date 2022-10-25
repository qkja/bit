test:test.cpp
	g++ -std=c++11 -o $@ $^

debug:test.cpp
	g++ -std=c++11 -o $@ $^ -g

.PHONY:clean
clean:
	rm -f test debug
