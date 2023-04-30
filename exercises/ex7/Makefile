# Yuhua Nie and Yanxiao Sun
# nieyuhua@uw.edu ysun01@uw.edu

CXX = g++
CXXFLAGS = -Wall -std=c++11

ex7: ex7.o Vector.o
	$(CXX) $(CXXFLAGS) -o ex7 ex7.o Vector.o

ex7.o: ex7.cc Vector.h
	$(CXX) $(CXXFLAGS) -c ex7.cc

Vector.o: Vector.cc Vector.h
	$(CXX) $(CXXFLAGS) -c Vector.cc

clean:
	rm -f ex7 *.o *~
