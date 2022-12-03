mybin:test.o heap.o
	gcc -std=c99 -o $@ $^

test.o:test.c
	gcc -c -std=c99 -o $@ $^
heap.o:Heap.c
	gcc -c -std=c99 -o $@ $^
.PHONY:clean
clean:
	rm -f mybin
