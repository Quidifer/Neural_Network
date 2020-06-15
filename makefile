#makefile
#type 'make' to compile
#type 'make clean' to remove object files

#variables
COMPILE = g++
# FLAGS = -g -W -Wall -Werror -ansi -pedantic
OBJS = Layer.o Network.o

#Targets
all: main.cpp $(OBJS)
	$(COMPILE) $(FLAGS) -o a.out main.cpp $(OBJS)

Layer.o: Layer.cpp Neuron.h
	$(COMPILE) $(FLAGS) -c Layer.cpp

Network.o: Network.cpp Layer.h Neuron.h
	$(COMPILE) $(FLAGS) -c Network.cpp

clean:
	rm -rf *.o a.out
