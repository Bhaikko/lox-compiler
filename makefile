CXX = g++
RM = rm -f
CPPFLAGS = -std=c++11 -Wall -g

SRCS_CPP = \
		./lib/Scanner/Token.cpp \
		./lib/Scanner/Scanner.cpp \
		./lib/Parser/Expr.cpp \
		./lib/Parser/Binary.cpp \
		./lib/Parser/Grouping.cpp \
		./lib/Parser/Unary.cpp \
		./lib/Parser/Literal.cpp \
		./lib/Parser/AstPrinter.cpp \
		./lib/Lox.cpp \
		./src/main.cpp \

run:
	$(CXX) $(SRCS_CPP) -o application $(CPPFLAGS) 

