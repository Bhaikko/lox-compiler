CXX = g++
RM = rm -f
CPPFLAGS = -std=c++11 -Wall -g

SRCS_CPP = \
		./lib/Scanner/Token.cpp \
		./lib/Scanner/Scanner.cpp \
		./lib/Parser/ParseError.cpp \
		./lib/Parser/Parser.cpp \
		./lib/Parser/Expr.cpp \
		./lib/Parser/Binary.cpp \
		./lib/Parser/Grouping.cpp \
		./lib/Parser/Literal.cpp \
		./lib/Parser/Unary.cpp \
		./lib/Parser/Stmt/Stmt.cpp \
		./lib/Parser/AstPrinter.cpp \
		./lib/Interpreter/Interpreter.cpp \
		./lib/Interpreter/RuntimeError.cpp \
		./lib/Lox.cpp \
		./src/main.cpp \

run:
	$(CXX) $(SRCS_CPP) -o application $(CPPFLAGS) 

