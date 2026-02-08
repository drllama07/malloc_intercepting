#include <stdlib.h>
#include <stdio.h>



int main() {
 
	for(size_t i = 1; i < 101; i++) {
		void *p = malloc(i);
		printf("Allocating  %zu bytes\n", i);
	        free(p);

        }
}
