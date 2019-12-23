CC=gcc
GCC=g++
CPPFLAGS=-std=c++11
CFLAGS= -Wall -Wextra -Os
OFILE=exec
GCCCOMPILE= $(GCC) $(CPPFLAGS) $(CFLAGS)
CCCOMPILE= $(CC) $(CFLAGS)

acp:
	 $(GCCCOMPILE) abstract_classes_polymorphism.cpp -o $(OFILE)

mad:
	$(CCCOMPILE) min_abs_diff.c -o $(OFILE)

t:
	 $(CCCOMPILE) tokenizer.c -o $(OFILE)
pos:
	 $(CCCOMPILE) permutations_of_strings.c -o $(OFILE)

clean:
	rm $(OFILE)
