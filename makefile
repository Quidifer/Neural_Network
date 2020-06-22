#makefile
#type 'make' to compile
#type 'make clean' to remove object files

#variables
COMPILE = g++
# FLAGS = -g -W -Wall -Werror -ansi -pedantic
OBJS = Layer.o Network.o

ENV_VAR = test_network_sigmoid.cpp

ifeq ($(TYPE),RELU)
     ENV_VAR = test_network_ReLU.cpp
    else
     ENV_VAR = test_network_sigmoid.cpp
    endif

#Targets
all: $(ENV_VAR) $(OBJS)
	$(COMPILE) $(FLAGS) -o a.out $(ENV_VAR) $(OBJS)

Layer.o: Layer.cpp Neuron.h
	$(COMPILE) $(FLAGS) -c Layer.cpp

Network.o: Network.cpp Network.h Layer.h Neuron.h
	$(COMPILE) $(FLAGS) -c Network.cpp

Network_ReLU.o: Network_Relu.cpp Network.h Network_ReLU.h Layer.h Neuron.h
	$(COMPILE) $(FLAGS) -c Network_ReLU.cpp

clean:
	rm -rf *.o a.out
