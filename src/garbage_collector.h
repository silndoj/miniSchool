#ifndef GARBAGE_COLLECTOR_H_
#define GARBAGE_COLLECTOR_H_

#include <stdlib.h>
#define MALLOC(SIZE)    alloc_ptr_list(SIZE);

extern void *alloc_ptr_list(size_t alloc_size) \
__attribute__ ((returns_nonnull, alloc_size(1)));
void destroy_ptr_list()__attribute__((destructor));

#endif