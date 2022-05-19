#ifndef HEADER_DEFINED
#define HEADER_DEFINED

#define MAX_LENGTH 50
#define BUFF_SIZE 4096
#define ROWALLOC(X) row *X = calloc(1,sizeof(row))

typedef struct row row;
struct row {
    row* next;
    int* data;
};

typedef struct head {
    row* next;
    row* tail;
    char(*data)[MAX_LENGTH];
    int config[2];                          //config[0] == number of columns, config[1] == table size
} head;

head* table_init(int len);

row* table_search(head* table, int column, int query);

int m_table_search(head* table, int column, int query, int q);

void row_append(int q, head* pointer);

void print_row(row* r, int q);

int m_row_update(head* table, int q, int column, int query);

void row_del(head* table, int q, int column, int query);

int m_row_del(head* table, int column, int query);


void csv_out(head* table, int q, char* name);

head* csv_in(const char* name);



void row_update(head* table, int q, int column, int query);

void get_average(head* table, int q);

void sort_array(int* array, int num);

int* make_average_array(head* talbe, int q, int people);

int paint_pass(head* table, int q, int average, int floor_Score);

void paint_fail(head* table, int q);

int check_floor_score(const row* using_row, int q, const int floor_score);

void score_people(head* table, int q, int floor_score, int pass_people_num);

int is_in_array(int* Array, int Array_length, int source);

int how_many_people(head* table);

void iterator(head* headrow, int q);

void exception_score_people(head* table, int q);

void exception_get_average(head* table, int q);

int is_valid_table(head* headrow, int q);

#endif