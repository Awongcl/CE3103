

# objects
objects = hello-main.o hello-funct1.o hello-funct2.o 
LIB = -lpthread
CFLAGs = -o -WALL
all: helloworld debug
# Linking rules, -o command
helloworld: $(objects)
	gcc -pg -o helloworld hello-main.o hello-funct1.o hello-funct2.o $(LIB)

#Below compile but not link
hello-main.o:  hello-main.c
	gcc $(CFLAGS) hello-main.c 

hello-funct1.o:	hello-funct1.c
	gcc $(CFLAGS) hello-funct1.c

hello-funct2.o: hello-funct2.c
	gcc $(CFLAGS) hello-funct2.c  

clean: 
	rm -f $(objects) helloworld
