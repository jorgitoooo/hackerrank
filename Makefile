GCC=g++
FLAGS=-std=c++11
OFILE=exec
acp:
	$(GCC) $(FLAGS) abstract_classes_polymorphism.cpp -o $(OFILE)
clean:
	rm $(OFILE)
