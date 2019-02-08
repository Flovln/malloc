# malloc

The goal of this project was to write a dynamic memory allocation handler library. Writting our own *malloc()*, *realloc()* and *free()* functions.

## Functions prototypes
```c
#include <stdlib.h>
void  free(void *ptr);
void  *malloc(size_t size);
void  *realloc(void *ptr, size_t size);
```

## Details

- *malloc()* : allocates "size" bytes of memory and returns a pointer on the allocated memory.
- *realoc()* : tries to update the allocation pointed by "ptr" at "size" bytes and returns "ptr". If there is not enough space within the memory pointed by "ptr", *realloc()* creates a new allocation and copies as much data from the previous allocation until reaching the "size" limit, and free the old one.
- *free()* : free the memory allocation pointed by "ptr". If "ptr" equals null, *free()* does nothing.

Find more details about each function behavior by consulting their man pages.

```bash
$> man 3 malloc
...
$> man 3 realloc
...
$> man 3 free
...
```

To implement those functions I used the **mmap()** (man 2 mmap) and **munmap()** (man 2 munmap) syscalls in order to reclaim and give memory back to the system.

## How to use the library

Compile the project.

```bash
$> cd malloc
$> make
...
```

Run the tests
```bash
$> make runtests
```

## Output

```bash
# Page reclaims output
-----------------------------------------------
/usr/bin/time -l ./tests/test0
        0.00 real         0.00 user         0.00 sys
    823296  maximum resident set size
         0  average shared memory size
         0  average unshared data size
         0  average unshared stack size
       213  page reclaims
         0  page faults
         0  swaps
         0  block input operations
         0  block output operations
         0  messages sent
         0  messages received
         0  signals received
         0  voluntary context switches
         1  involuntary context switches
...
# Range for each allocation type: TINY, SMALL, LARGE
-----------------------------------------------
./tests/test5
TINY : 0x104def000
0x104def988 - 0x104defd88 : 1024 octets
LARGE : 0x104e09000
0x104e09040 - 0x104e11040 : 32768 octets
LARGE : 0x104e12000
0x104e12040 - 0x104f12040 : 1048576 octets
LARGE : 0x105dee000
0x105dee040 - 0x106dee040 : 16777216 octets
LARGE : 0x106def000
0x106def040 - 0x10edef040 : 134217728 octets
Total : 152077312 octets
```