OPTFLAGS = \
  -Og

DBGFLAGS = \
  -g \
  -fsanitize=address

INCLUDES = \
  -isystem include \
  -I ../include

CXXFLAGS = \
  -std=c++11 \
  -pedantic \
  -Wall \
  -Wextra \
  -Wconversion \
  -Wsign-conversion \
  -Wshadow \
  $(OPTFLAGS) \
  $(DBGFLAGS) \
  $(INCLUDES)

OBJECTS = \
  main.o \
  test_spline.o

ARTIFACTS = \
  $(OBJECTS) \
  main

.PHONY: test clean

test: main
	@./main

clean:
	rm -f $(ARTIFACTS)

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

test_spline.o: ../include/spline.hpp
