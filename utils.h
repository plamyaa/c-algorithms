#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void * xmalloc(size_t n);
void *xcalloc(size_t n, size_t size);

int is_prime(const int x);
int next_prime(int x);