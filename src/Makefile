CXX = g++
CXXFLAGS = -O3 -g -Wall -Wextra -std=c++17
DEPS = $(wildcard *.h)

grop: main.o Index.o FSTree.o DirNode.o Hashtable.o
	$(CXX) $(CXXFLAGS) -o $@ $^

the_sl: the_sl.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) -o $@ $^

hashExample: hashExample.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf *.o grop *.dSYM
