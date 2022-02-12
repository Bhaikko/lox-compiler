CXX = g++
RM = rm -f
CPPFLAGS = -std=c++11 -Wall -g

SRCS_CPP = \
		./lib/Token.cpp \
		./lib/Scanner.cpp \
		./lib/Parser/Expr.cpp \
		./lib/Parser/Binary.cpp \
		./lib/Lox.cpp \
		./src/main.cpp \

run:
	$(CXX) $(SRCS_CPP) -o application $(CPPFLAGS) 

