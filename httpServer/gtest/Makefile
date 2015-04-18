###############
## Makefile
###############

BIN=../bin/TestBinary
GTEST_LIB = ../lib/libgtest.a

##ARCH = $(shell uname -m)	# ARCH becomes the output from the uname -m command.
CXX=/usr/bin/g++
CXXFLAGS=-g -O2 -std=c++11 -Wall -I$(GTEST_ROOT)/include -D_REENTRANT $(INCS)

SRCS = AddTest.cpp

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

INCS = -I../include \
       -I$(BOOST_INSTALL_ROOT)/include \

GTEST_SRC = $(GTEST_ROOT)/src/gtest-all.cc
GTEST_OBJ = $(patsubst %.cpp, %.o, $(GTEST_SRC))  

$(GTEST_LIB): $(GTEST_OBJ)
	ar -rv $(GTEST_LIB) $(GTEST_OBJ)

LIBS = \
    	$(BOOST_INSTALL_ROOT)/lib/libboost_thread.a \
	$(BOOST_INSTALL_ROOT)/lib/libboost_system.a \
	-L../lib -lAdd \
        $(GTEST_ROOT)/make/gtest_main.a \
	-lpthread

	
$(BIN): $(OBJS)
	$(CXX) -o $(BIN) $(OBJS) $(LIBS)

all: $(BIN) run

run:
	@echo "----------------------------"
	@echo "Running the TestCases. "
	@echo "----------------------------"
	$(BIN)
	@echo "----------------------------"

clean:
	rm -rf $(BIN) *.o
