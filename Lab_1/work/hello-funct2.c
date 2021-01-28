#include <stdio.h>

int count = 1;
//1 because of the enter key

int count_press(){
	printf("Hello World from funct2!\n");
	int i = 0x7fffffff;
	while(i>0)
	  i--;	

	count += 1;
	return count;
}
