//
// wip_fn
// Copyright (c) 2021 Jovan Lanik
//

#include <stdio.h>

void *wip_alloc(size_t);
void *wip_realloc(void *, size_t, int*);
void wip_free(void *);
FILE *wip_openFile(const char *n);

