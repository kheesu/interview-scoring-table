#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

head* table_init(int len);

void row_append(int q, head* pointer);

void print_row(row* r, int q);

void row_del(head* table, int q, int column, int query);


void csv_out(head* table, int q, char* name);

head* csv_in(const char* name);


void get_average(head* table, int q);

row* return_max_average_row(const head* table, int q, int floor_score, int* pass_people_array, int pass_people_array_cnt);

int check_floor_score(row* using_row, int q, int floor_score);

void score_people(head* table, int q, int floor_score, int pass_people_num);

int is_in_array(int* Array, int Array_length, int source);

int how_many_people(head* table);

void iterator(head* headrow, int q);

int main() {
    int q;                                                          //Sets the number of questions for the table
    printf("Enter Number of Questions : ");
    scanf("%d", &q);
    head* headrow;                                  //Generates the table
    headrow = table_init(q);
    
    //for (int i = 0; i < q + 3; i++) {                                //Tests whether the head row was correctly generated
    //    printf("%s\n", headrow->data[i]);
    //}

    char buffer[1024];
    while (1) {
        printf("Enter 1 to add entry\n 2 to print table,\n 3 to search for a value\n 4 to update the row of searched value\n 5 to delete the row of searched value\n 6 to save current table as csv\n 7 to read csv into memory\n ! to exit :\n");
        scanf("%s", buffer);
        if (buffer[0] == '1') {
            row_append(q, headrow);
        }

        else if (buffer[0] == '2') {
            row* p = headrow->next;
            for (int i = 0; i < q + 3; i++) printf("%s\t", headrow->data[i]);
            puts("");
            while (p != NULL) {
                for (int i = 0; i < q + 3; i++) {
                    printf("%d\t\t", p->data[i]);
                }
                printf("\n");
                p = p->next;
            }
        }

        else if (buffer[0] == '3') {
            int column, query;
            printf("Enter column to search, then data to search for :\n");
            scanf("%d%d", &column, &query);
            row* p = table_search(headrow, column, query);
            if (p == NULL) printf("ERROR\nSearch failed or empty table\n");
            else print_row(p, q);
        }

        else if (buffer[0] == '4') {
            int column, query;
            printf("Enter column to search, then data to search for :\n");
            scanf("%d%d", &column, &query);
            row_update(headrow, q, column, query);
        }

        else if (buffer[0] == '5') {
            int column, query;
            printf("Enter column to search, then data to search for :\n");
            scanf("%d%d", &column, &query);
            row_del(headrow, q, column, query);
        }

        else if (buffer[0] == '6') {
            printf("Enter output file name\n");
            scanf("%s", buffer);
            csv_out(headrow, q, buffer);
        }

        else if (buffer[0] == '7') {
            printf("Enter input file name\n");
            scanf("%s", buffer);
            headrow = csv_in(buffer);
            if (headrow != NULL) q = headrow->config[0] - 3;
            else headrow = table_init(q);
        }

        else if (buffer[0] == '!') return 0;
        else printf("Enter valid character\n");
    }
    return 0;
}