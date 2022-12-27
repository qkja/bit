FLAGS=-std=c++11
LD=-lpthread
src=ThreadPool.cc 
bin=threadPool 
$(bin):$(src)
	g++ -o $@ $^ $(FLAGS) $(LD)
.PTHONY:clean
clean:
	rm -f $(bin)
