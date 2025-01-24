CXX = g++ -std=c++11
DIR = /usr/local
LIBS = -lgecodedriver -lgecodesearch -lgecodeminimodel -lgecodeint -lgecodekernel -lgecodesupport

compile:
	$(CXX) -I$(DIR)/include -c main.cpp
	$(CXX) -L$(DIR)/lib -o main main.o $(LIBS)
