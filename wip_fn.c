//
// wip_fn
// Copyright (c) 2021 Jovan Lanik
//

#include <stdlib.h>

#include "wip_fn.h"

void *wip_alloc(size_t size) {
	void *o = malloc(size);
	return o;
}

void *wip_realloc(void *pointer, size_t size, int *ret) {
	void *o = realloc(pointer, size);
	if(!o) {
		if(ret) *ret = 0;
		return pointer;
	}
	if(ret) *ret = 1;
	return o;
}

void wip_free(void *pointer) {
	free(pointer);
	return;
}

FILE *wip_openFile(const char *name) {
	FILE *file = fopen(name, "r+");
	return file;
}

