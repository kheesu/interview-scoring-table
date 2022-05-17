#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
    char buffer[BUFF_SIZE];
    head* table;
    int q;
    char c;

    while (1) {
        printf("Enter\n 1 to create new table\n 2 to load table from CSV file\n 0 to exit program\n");
        if (scanf("%10s", buffer) != 1) {                                        
            fprintf(stderr, "INPUT ERROR\n");
            return -1;
        }

        while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

        if (buffer[1] != '\0' || buffer[0] < '0' || buffer[0] > '2')
            printf("Invalid input, try again\n");

        else if (buffer[0] == '1') {
            q = 1025;                                                          //Sets the number of questions for the table
            while (1) {
                printf("Enter Number of Questions (Max 1024) : ");
                if (scanf("%4095s", buffer) != 1) {
                    fprintf(stderr, "INPUT ERROR\n");
                    return -1;
                }

                while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin
                
                errno = 0;
                q = (int)strtol(buffer, NULL, 0);

                if (errno == ERANGE) fprintf(stderr, "Range error, try again\n");

                if (q > 1024 || q < 1) printf("Invalid input, try again\n");

                else {
                    table = table_init(q);
                    break;
                }
            }
            break;
        }
        else if (buffer[0] == '2') {
            while (1) {
                printf("File to load:\n");
                if (scanf("%4095s", buffer) != 1) {
                    fprintf(stderr, "INPUT ERROR\n");
                    return -1;
                }

                while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

                table = csv_in(buffer);

                if (table != NULL) {
                    q = table->config[0] - 3;
                    break;
                }
            }
            break;
        }
        else if (buffer[0] == '0') {
            printf("Exiting...\n");
            return 0;
        }
    }
    
    while (1) {
        printf("Enter\n 1 to print table\n 2 to add entry\n 3 to search\n 4 to update\n 5 to delete\n 6 to save current table as csv\n 0 to exit\n");
        if (scanf("%4095s", buffer) != 1) {
            fprintf(stderr, "INPUT ERROR\n");
            return -1;
        }

        while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

        if (buffer[0] < '0' || buffer[0] > '6' || buffer[1] != '\0')
            printf("Invalid input, try again\n");

        else if (buffer[0] == '1') {
            iterator(table, q);
        }

        else if (buffer[0] == '2') {
            row_append(q, table);
        }

        else if (buffer[0] == '3') {
            int column, query;
            printf("Enter column to search, then data to search for :\n");

            if (scanf("%4d%10d", &column, &query) != 2) {
                fprintf(stderr, "INPUT ERROR\n");
                return -1;
            }

            while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin
/*
            row* p = table_search(table, column, query);

            if (p == NULL) printf("ERROR\nSearch failed or empty table\n");

            else print_row(p, q);
*/
            if (m_table_search(table, column, query, q) == 0) {
                printf("ERROR\nSearch failed or empty table\n");
            }
        }

        else if (buffer[0] == '4') {
            int column, query;
            printf("Enter column to search, then data to search for :\n");

            if (scanf("%4d%10d", &column, &query) != 2) {
                fprintf(stderr, "INPUT ERROR\n");
                return -1;
            }

            while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

            row_update(table, q, column, query);
        }

        else if (buffer[0] == '5') {
            int column, query;
            printf("Enter column to search, then data to search for :\n");

            if (scanf("%4d%10d", &column, &query) != 2) {
                fprintf(stderr, "INPUT ERROR\n");
                return -1;
            }

            while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

            //row_del(table, column, query);
            m_row_del(table, column, query);
        }

        else if (buffer[0] == '6') {
            printf("Enter output file name\n");

            if (scanf("%4095s", buffer) != 1) {
                fprintf(stderr, "INPUT ERROR\n");
                return -1;
            }

            while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

            csv_out(table, q, buffer);
        }

        else if (buffer[0] == '0') {
            printf("Exiting...\n");
            return 0;
        }

        else printf("Invalid input, try again\n");
    }


}