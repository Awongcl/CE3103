#include <stdio.h>
#include "hello.h"

int main(){
	printf("Hello World From Main!\n");
	int i = 0x5ffffff;
	while(i > 0)
	   i--;

	helloprint();
	
	char c, n;
	while(c != 'q'){
		fread(&c,1,1,stdin);
		n = count_press();
		printf("Number of presses: %d\n", n-1);		
	}
	printf("Bye!");
	return 0;
}
