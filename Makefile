GCC=g++
FLAGS=-std=c++11
acp:
	$(GCC) $(FLAGS) abstract_classes_polymorphism.cpp -o exec
clean:
	rm exec
