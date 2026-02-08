# Malloc Intercepting

This project interposes `malloc` using `LD_PRELOAD` to count the total number of bytes allocated by a program.

## Key behavior
- Overrides `malloc` to track total allocated bytes
- Logs output to `stderr` using `fprintf`
- Uses recursion guards to avoid infinite loops
- Handles glibc lazy initialization correctly

## Environment
- OS: Ubuntu 24.04.3 LTS  
- Compiler: Clang 18.1.3 (1ubuntu1)

## Build

Build the shared library:
```bash
clang -shared -fPIC -o libget_malloc.so get_malloc.c -ldl
```
Run a program with the malloc interceptor: 
```bash 
LD_PRELOAD=./libget_malloc.so ./program
```
### Example Test Program
Compile the test program:
1. ```clang -L. -Wl,-rpath=. -o main main.c```
Run it with the interceptor:
2. ```LD_PRELOAD=./libget_malloc.so ./main```

### Credits: 
- I used this great tutorial on getting started with interposing malloc: https://nvankempen.com/2025/06/04/guide-using-dynamic-loader-interpose-malloc.html