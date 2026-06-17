CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -I. -Itests

APP_SOURCES = main.cpp
APP_OBJECTS = $(APP_SOURCES:.cpp=.o)
APP_TARGET = app

TEST_SOURCES = tests/test_main.cpp \
               tests/test_lcs_full_dp.cpp \
               tests/test_lcs_two_rows.cpp \
               tests/test_lcs_one_row.cpp \
               tests/test_lcs_validator.cpp \
               tests/test_cross_validation.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_TARGET = test_runner

.PHONY: all test clean

all: $(APP_TARGET)

$(APP_TARGET): $(APP_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ifeq ($(OS),Windows_NT)
    RM = del /Q
    NULLDEV = nul
else
    RM = rm -f
    NULLDEV = /dev/null
endif

clean:
	-$(RM) $(APP_OBJECTS) $(APP_TARGET) $(TEST_OBJECTS) $(TEST_TARGET) 2>$(NULLDEV)
