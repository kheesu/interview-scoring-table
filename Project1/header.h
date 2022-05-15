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

head* table_init(int len);

row* table_search(head* table, int column, int query);

void row_append(int q, head* pointer);

void print_row(row* r, int q);

void row_del(head* table, int q, int column, int query);


void csv_out(head* table, int q, char* name);

head* csv_in(const char* name);



void row_update(head* table, int q, int column, int query);

void get_average(head* table, int q);

void sort_array(int* array, int num);

int* make_average_array(head* talbe, int q, int people);

int paint_pass(head* table, int q, int average, int floor_Score);

void paint_fail(head* table, int q);

int check_floor_score(row* using_row, int q, int floor_score);

void score_people(head* table, int q, int floor_score, int pass_people_num);

int is_in_array(int* Array, int Array_length, int source);

int how_many_people(head* table);

void iterator(head* headrow, int q);