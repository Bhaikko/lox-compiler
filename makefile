CXX = g++
RM = rm -f
CPPFLAGS = -std=c++11 -Wall -g

SRCS_CPP = \
		./src/main.cpp \

run:
	$(CXX) $(SRCS_CPP) -o application $(CPPFLAGS)