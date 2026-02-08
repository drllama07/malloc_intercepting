#define _GNU_SOURCE
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>

// A global counter to store the total number of bytes allocated so far.
static size_t byte_counter =0;
// flag for preventing potential recursions.
static size_t skip_output = 0;

// Because stderr is not initialized like stdout after calling fprintf on stderr we get an unexpected 1024-byte // memory allocation. This code helps avoid it by forcing the initialization before everything. 
__attribute__((constructor))
void init_libc() {
        fprintf(stderr, "Outputing Malloc Calls: \n");
	byte_counter = 0;
}

void *malloc(size_t size) {
      // initializing a function pointer that will be assigned to the actual malloc.
      static void *(*real_malloc)(size_t) = NULL;

      if (!real_malloc) {
	      real_malloc = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
      }
      // if this is a malloc call due to the outputing mechanism used inside our malloc definition,
      // we skip printing the total number of bytes allocated and prevent infinite recursion.
      if(skip_output) {
	      return real_malloc(size);
      }



      // we increment skip_output to skip outputing for any malloc call within our malloc function.
      skip_output += 1;
      
      byte_counter += size;
      
      printf("The total number of bytes allocated: %zu \n", byte_counter);
      
      // reseting our counter so that our outputing mechanism works for malloc calls outside our own malloc. 
      skip_output -= 1;

      return real_malloc(size);
}
