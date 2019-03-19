# Flags for compiling with C++.  
CXXFLAGS = -Wall -std=c++11 -O2 -DNO_FREETYPE -I $(HOME)/libs/include
LIBS =  -L $(HOME)/libs/lib -l PNGwriter -l png

all:
	@echo "\033[256;94m\
	Choose a command from the following:\n\
	- compile\n\
	- test / test_time / test_point / test_conv \n\
	- open / open_point / open_conv \n\
	- use \n\
	- clean\
	\033[0m"

# To know if everything compiles fine
compile: Point.o ConvexPolygon.o Polygon_Calculator.o 

# Start the calculator
use: Polygon_Calculator.exe
	@./Polygon_Calculator.exe

# Check if it is well-implemented
test: Polygon_Calculator.exe
	@cd tests; ../Polygon_Calculator.exe < test.inp > test.out; \
	diff test.out test.txt 

# Check if it is efficient
test_time: Polygon_Calculator.exe
	@cd tests; ../Polygon_Calculator.exe < test_time.inp > test_time.out; \
	more test_time.out

# Check if Point/ConvexPolygon is well-implemented
test_point: test_point.exe
	@cd tests; ./test_point.exe < test_point.inp > test_point.out; \
	diff test_point.out test_point.txt
test_conv: test_conv.exe
	@cd tests; ./test_conv.exe < test_conv.inp > test_conv.out; \
	diff test_conv.out test_conv.txt

# Opens the tests files
open_point:
	@cd tests; code test_point.out test_point.txt test_point.inp test_point.cc
open_conv:
	@cd tests; code test_conv.out test_conv.txt test_conv.inp test_conv.cc
open:
	@cd tests; code test.out test.txt test.inp ../Polygon_Calculator.cc

# Compiles the calculator
Polygon_Calculator.exe: Point.o ConvexPolygon.o Polygon_Calculator.o
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@ 

# Compiles diferent testers
test_point.exe: Point.o test_point.o
	@cd tests; $(CXX) $(CXXFLAGS) -o $@ ../Point.o test_point.o
test_conv.exe: Point.o ConvexPolygon.o test_conv.o
	@cd tests; $(CXX) $(CXXFLAGS) -o $@ ../Point.o ../ConvexPolygon.o test_conv.o


# All the needed linkers
Point.o: Point.cc
test_point.o: 
	@cd tests; $(CXX) $(CXXFLAGS) -c test_point.cc 
ConvexPolygon.o: ConvexPolygon.cc 
test_conv.o: 
	@cd tests; $(CXX) $(CXXFLAGS) -c test_conv.cc 
Polygon_Calculator.o: Polygon_Calculator.cc 

# Removes .exe, .o and .out files
clean: 
	@rm -rf *.o *.exe *.out
	@cd tests; rm -rf *.o *.exe *.out
