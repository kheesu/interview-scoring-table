#pragma once

#define MAX_LENGTH 50
#define ROWALLOC(X) row *X = malloc(sizeof(row))

typedef struct row row;
struct row {
    row* next;
    int* data;
};

typedef struct head {
    row* next;
    row* tail;
    char(*data)[MAX_LENGTH];
    int config[2];                          //config[0] == number of columns, config[1] == minimum score
} head;

