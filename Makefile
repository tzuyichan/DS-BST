FILENAME = bst
DATA_STRUCTURE = binary_search_tree

GCC = gcc
CLANG = clang++
LLVMFLAGS = -std=c++11 -stdlib=libc++
CXXFLAGS += -lstdc++

$(CLANG): $(FILENAME).cpp $(DATA_STRUCTURE).o
	$(CLANG) $(LLVMFLAGS) $^ -o $(FILENAME)

$(GCC): $(FILENAME).cpp
	$(GCC) $^ -o $(FILENAME) $(CXXFLAGS)

$(DATA_STRUCTURE).o: $(DATA_STRUCTURE).cpp $(DATA_STRUCTURE).h
	$(CLANG) $(LLVMFLAGS) -c $<

clean:
	rm *.o $(FILENAME)