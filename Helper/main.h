#pragma once


#include <stdlib.h>
#include <stdio.h>

//Generic macros and inlines


#define M_ListOf_abstr(X) \
{                                \
          X curr, *pNext;        \
}

#define M_GET_MACRO(_1,_2,NAME,...) NAME

#define M_t_ListOf(...) M_GET_MACRO(__VA_ARGS__, M_t_ListOf_2, M_t_ListOf_1, _)(__VA_ARGS__)

#define M_t_ListOf_1(X) struct M_ListOf_abstr(X)

#define M_t_ListOf_2(X, Name) struct Name M_ListOf_abstr(X)


static inline void* safe_malloc(size_t n, unsigned long line)
{
    void* p = malloc(n);
    if (!p)
    {
        fprintf(stderr, "[%s:%ul]Out of memory(%ul bytes)\n",
                __FILE__, line, (unsigned long)n);
        exit(EXIT_FAILURE);
    }
    return p;
}

#define M_SAFEMALLOC(n) safe_malloc(n, __LINE__)

#define M_abstr(type) (*((type *)0))
