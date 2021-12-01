FILENAME = bst

GCC = gcc
CLANG = clang++
LLVMFLAGS = -std=c++11 -stdlib=libc++
CXXFLAGS += -lstdc++

$(CLANG): $(FILENAME).cpp
	$(CLANG) $(LLVMFLAGS) $^ -o $(FILENAME)

$(GCC): $(FILENAME).cpp
	$(GCC) $^ -o $(FILENAME) $(CXXFLAGS)

clean:
	rm *.o $(FILENAME)
