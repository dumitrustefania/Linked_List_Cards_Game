// Copyright 2022 Dumitru Bianca Stefania 312CA
#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct t_data
{
    int num;
    char symb[8];
} t_data;

typedef struct t_ll
{   void *data;
    struct t_ll *head, *tail;
    struct t_ll *prev, *next;
    int size;
} t_ll;
#endif  // STRUCTS_H_
