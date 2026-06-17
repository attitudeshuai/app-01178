CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

BACKEND_DIR = ../backend
GTEST_INC = C:/msys64/ucrt64/include
GTEST_LIB = C:/msys64/ucrt64/lib

TEST_TARGET = lcs_test.exe
TEST_SRC = lcs_test.cpp

.PHONY: all test clean

all: test

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(BACKEND_DIR)/lcs.h
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_SRC) -I$(BACKEND_DIR) -I$(GTEST_INC) -L$(GTEST_LIB) -lgtest -lgtest_main -lmingw32

clean:
	rm -f $(TEST_TARGET)
