.PHONY:all
all:libmyDynamicslib.so libmystaticlib.a

libmyDynamicslib.so:mymathdy.o myprintdy.o
	gcc -shared -o libmyDynamicslib.so mymathdy.o myprintdy.o
mymathdy.o:mymath.c
	gcc -std=c99 -fPIC -c mymath.c -o mymathdy.o 
myprintdy.o:myprint.c
	gcc -std=c99 -fPIC -c myprint.c -o myprintdy.o 

libmystaticlib.a:mymaths.o myprints.o
	ar -rc libmystaticlib.a myprints.o mymaths.o
mymaths.o:mymath.c
	gcc -std=c99 -c mymath.c -o mymaths.o
myprints.o:myprint.c
	gcc -std=c99 -c myprint.c -o myprints.o



.PHONY:lib 
lib:
	mkdir -p lib-dy/lib; 
	mkdir -p lib-dy/include; 
	cp *.so lib-dy/lib;
	cp *.h lib-dy/include
	mkdir -p lib-static/lib; 
	mkdir -p lib-static/include; 
	cp *.a lib-static/lib;
	cp *.h lib-static/include

.PHONY:clean
clean:
	rm -f *.o *.so *.a -r lib-static -r lib-dy
