CC=gcc
CPPC=g++
CPPFLAGS=-std=c++11
CFLAGS= -Wall -Wextra -Os
OFILE=exec
CPPCCOMPILE= $(CPPC) $(CPPFLAGS) $(CFLAGS)
CCCOMPILE= $(CC) $(CFLAGS)

acp:
	 $(CPPCCOMPILE) abstract_classes_polymorphism.cpp -o $(OFILE)
mad:
	$(CCCOMPILE) min_abs_diff.c -o $(OFILE)
t:
	 $(CCCOMPILE) tokenizer.c -o $(OFILE)
pos:
	 $(CCCOMPILE) permutations_of_strings.c -o $(OFILE)
vf:
	 $(CCCOMPILE) variadic_functions.c -o $(OFILE)
std:
	 $(CCCOMPILE) structuring_the_document.c -o $(OFILE)
run:
	./$(OFILE)
clean:
	rm $(OFILE)
