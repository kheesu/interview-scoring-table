#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "header.h"

head* table_init(int len) {

    char(*h)[MAX_LENGTH];
    h = malloc(sizeof(*h) * (len + 3));

    strcpy(h[0], "Student ID");

    for (int i = 1; i < len + 1; i++) {
        char buffer[1000];
        char buffer2[1000] = "Question ";
        snprintf(buffer, sizeof(char) * MAX_LENGTH, "%d", i);
        strcat(buffer2, buffer);
        strcpy(h[i], buffer2);
    }
    strcpy(h[len + 1], "Average");
    strcpy(h[len + 2], "P/F");

    head* out = calloc(1,sizeof(head));
    out->data = h;
    out->next = NULL;
    out->tail = out->next;
    return out;
}


void row_append(int q, head* pointer) {                             //Creates new row and appends to the end of the table
    char c;
    char buffer[BUFF_SIZE];
    int* data = calloc(q + 3, sizeof(int));                      //Allocate an int array to be inserted into the allocated row

    for (int i = 0; i < q + 1; i++) {

        while (1) {
            int failed = 0;
            printf("Enter data for %s : \n", pointer->data[i]);

            if (scanf("%11s", buffer) != 1) {
                fprintf(stderr, "INPUT ERROR\n");
                exit(-1);
            }

            while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

            for (int j = 0; buffer[j] != '\0'; j++) {
                if (buffer[j] < '0' || buffer[j] > '9') {
                    printf("WRONG_INPUT_EXCEPTION: Enter a valid number\n");
                    failed = 1;
                    break;
                }
            }
            if (failed == 1) continue;

            errno = 0;
            data[i] = (int)strtol(buffer, NULL, 0);

            if (errno == ERANGE) fprintf(stderr, "Range error, try again\n");

            else if (i > 0 && (data[i] > 100 || data[i] < 0)) {
                printf("WRONG_INPUT_EXCEPTION: Enter a valid number\n");
                data[i] = 0;
            }

            else if (i == 0) {
                row* p = pointer->next;
                failed = 0;

                while (p != NULL) {
                    if (p->data[0] == data[0]) {
                        printf("Found duplicate Student ID (%d), try again\n", p->data[0]);
                        failed = 1;
                        break;
                    }
                    p = p->next;
                }

                if (failed == 0) break;
            }

            else break;
        }
    }

    ROWALLOC(new);                                                  //Allocates new row and appends it to the table

    if (pointer->next == NULL) {
        pointer->next = new;
        pointer->tail = new;
    }
    else {
        pointer->tail->next = new;
        pointer->tail = new;
    }

    
    pointer->tail->data = data;
    pointer->tail->next = NULL;
    return;
}


void print_row(row* r, int q) {                                     //Prints the pointed row
    if (r == NULL) return;
    for (int i = 0; i < q + 3; i++) printf("%-20d", r->data[i]);
    puts("");
    return;
}

row* table_search(head* table, int column, int query) {             //Returns pointer to the row with first matching value
    if (table->next == NULL) return NULL;                            //Returns NULL if table is empty i.e. only has head row
    row* p = table->next;
    while (p != NULL) {
        if (p->data[column] == query) return p;
        p = p->next;
    }
    return NULL;                                                    //Also returns NULL if search failed
}

int m_table_search(head* table, int column, int query, int q) {
    if (table->next == NULL) return 0;                            //Returns 0 if table is empty i.e. only has head row
    row* p = table->next;

    while (p != NULL) {
        if (p->data[column] == query) {
            print_row(p, q);
            p = p->next;
        }
    }
    return 1;
}

void row_update(head* table, int q, int column, int query) {
    row* p = table_search(table, column, query);
    char c;

    if (p == NULL) {
        fprintf(stderr, "Search failed, abort update\n");
        return;
    }

    free(p->data);                                                  //Free previous row's data
    int* data = malloc(sizeof(int) * (q + 3));                      //Allocate an int array to be inserted into the old row
    for (int i = 0; i < q + 3; i++) {
        printf("Enter data for %s : \n", table->data[i]);

        if (scanf("%11d", data + i) != 1) {
            fprintf(stderr, "INPUT ERROR\n");
            exit(-1);
        }

        while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin
    }
    p->data = data;
    return;
}

void replace_row(head *table, row *p, int q) {
    char c, buffer[BUFF_SIZE];

    free(p->data);                                                  //Free previous row's data
    int* data = calloc(q + 3, sizeof(int));                      //Allocate an int array to be inserted into the old row
    for (int i = 0; i < q + 1; i++) {
        while (1) {
            int failed = 0;
            printf("Enter data for %s : \n", table->data[i]);

            if (scanf("%11s", buffer) != 1) {
                fprintf(stderr, "INPUT ERROR\n");
                exit(-1);
            }

            while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

            for (int j = 0; buffer[j] != '\0'; j++) {
                if (buffer[j] < '0' || buffer[j] > '9') {
                    printf("WRONG_INPUT_EXCEPTION: Enter a valid number\n");
                    failed = 1;
                    break;
                }
            }
            if (failed == 1) continue;

            errno = 0;
            data[i] = (int)strtol(buffer, NULL, 0);

            if (errno == ERANGE) fprintf(stderr, "Range error, try again\n");

            else if (i > 0 && (data[i] > 100 || data[i] < 0)) {
                printf("WRONG_INPUT_EXCEPTION: Enter a valid number\n");
                data[i] = 0;
            }

            else if (i == 0) {
                row* p = table->next;
                failed = 0;

                while (p != NULL) {
                    if (p->data[0] == data[0]) {
                        printf("Found duplicate Student ID (%d), try again\n", p->data[0]);
                        failed = 1;
                        break;
                    }
                    p = p->next;
                }

                if (failed == 0) break;
            }

            else break;
        }
    }
    p->data = data;
    return;
}

int m_row_update(head* table, int q, int column, int query) {
    if (table->next == NULL) return 0;                            //Returns 0 if table is empty i.e. only has head row
    row* p = table->next;

    while (p != NULL) {
        if (p->data[column] == query) {
            replace_row(table, p, q);
        }
        p = p->next;
    }
    return 1;
}

//TODO: Make update function for updating single values
//void update_value(head *table, int q, int column, int query)

void row_del(head* table, int q, int column, int query) {               //Deletes first matching entry
    if (table->next == NULL) {                                            //Returns if table is empty i.e. only has head row
        printf("Empty table, abort delete\n");
        return;
    }
    if (table->next->data[column] == query && table->next->next == NULL) {
        free(table->next->data);
        free(table->next);
        table->next = NULL;
        return;
    }
    if (table->next->data[column] == query) {
        row* temp = table->next;
        table->next = table->next->next;
        free(temp->data);
        free(temp);
        return;
    }
    row* p = table->next;
    while (p->next != NULL) {
        if (p->next->data[column] == query) {
            row* temp = p->next;
            if (p->next->next == NULL) table->tail = p;
            p->next = p->next->next;       //If the matching row is the final row, need to update the tail pointer of head
            free(temp->data);
            free(temp);
            return;
        }
        p = p->next;
    }
    printf("Search failed, abort delete\n");
}

//TODO: Make delete function for deleting multiple matching rows
int m_row_del(head* table, int column, int query) {
    int result = 0;
    if (table->next == NULL) {                                            //Returns if table is empty i.e. only has head row
        printf("Empty table, abort delete\n");
        return 0;
    }
    if (table->next->data[column] == query && table->next->next == NULL) {
        free(table->next->data);
        free(table->next);
        table->next = NULL;
        return 1;
    }
    while (table->next->data[column] == query) {
        row* temp = table->next;
        table->next = table->next->next;
        free(temp->data);
        free(temp);
        result = 1;
        
        if (table->next == NULL) return result;
    }

    row* p = table->next;

    while (p->next != NULL) {
        if (p->next->data[column] == query) {
            row* temp = p->next;
            if (p->next->next == NULL) table->tail = p;
            p->next = p->next->next;       //If the matching row is the final row, need to update the tail pointer of head
            free(temp->data);
            free(temp);
            result = 1;
        }

        else p = p->next;

        if (p == NULL) return result;
    }
    return result;
}