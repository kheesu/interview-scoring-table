#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


int main() {
    int q;                                                          //Sets the number of questions for the table
    printf("Enter Number of Questions : ");
    scanf("%d", &q);
    head* headrow = table_init(q);                                  //Generates the table

    for (int i = 0; i < q + 3; i++) {                                //Tests whether the head row was correctly generated
        printf("%s\n", headrow->data[i]);
    }

    char buffer[1024];
    while (1) {
        printf("Enter 1 to add entry\n 2 to print table,\n 3 to search for a value\n 4 to update the row of searched value\n 5 to delete the row of searched value\n 6 to save current table as csv\n 7 to read csv into memory\n ! to exit :\n");
        scanf("%s", buffer);
        if (buffer[0] == '1') {
            row_append(q, headrow);
        }

        else if (buffer[0] == '2') {
            iterator(headrow, q);
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
        }

        else if (buffer[0] == '8') {
            exception_get_average(headrow, q);
        }

        else if (buffer[0] == '9') {
            exception_score_people(headrow, q);
        }

        else if (buffer[0] == '!') return 0;
        else printf("Enter valid character\n");
    }
    return 0;
}