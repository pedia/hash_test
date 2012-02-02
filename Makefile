all: hash_test
.PHONY: all

CFLAGS = -I. -g -O2

objects = hash_test.o hash/MurmurHash3.o hash/city.o hash/md5.o hash/doobs_hash.o hash/MurmurHash2.o hash/MurmurHash1.o

hash_test: $(objects) allhash.h ptime.h
	$(CXX) $(CFLAGS) $^ -o $@

$(objects): %.o: %.cc
	$(CXX) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm *.o hash_test hash/*.o

