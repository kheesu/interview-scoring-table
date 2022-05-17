#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    ROWALLOC(new);                                                  //Allocates new row and appends it to the table
                                                                //TODO: malloc execption handling
    if (pointer->next == NULL) {
        pointer->next = new;
        pointer->tail = new;
    }
    else {
        pointer->tail->next = new;
        pointer->tail = new;
    }

    int* data = calloc(q + 3, sizeof(int));                      //Allocate an int array to be inserted into the allocated row

    for (int i = 0; i < q + 1; i++) {
        printf("Enter data for %s : \n", pointer->data[i]);
        ;
        if (scanf("%d", data + i) != 1) {
            fprintf(stderr, "INPUT ERROR\n");
            return -1;
        }
    }
    pointer->tail->data = data;
    pointer->tail->next = NULL;
    return;
}


//TODO: Make the test printing thing into a function
//void print_table()

void print_row(row* r, int q) {                                     //Prints the pointed row
    if (r == NULL) return;
    for (int i = 0; i < q + 3; i++) printf("%d\t", r->data[i]);
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

void row_update(head* table, int q, int column, int query) {
    row* p = table_search(table, column, query);
    if (p == NULL) {
        fprintf(stderr, "Search failed, abort update\n");
        return;
    }

    free(p->data);                                                  //Free previous row
    int* data = malloc(sizeof(int) * (q + 3));                      //Allocate an int array to be inserted into the old row
    for (int i = 0; i < q + 3; i++) {
        printf("Enter data for %s : \n", table->data[i]);
        scanf("%d", data + i);
    }
    p->data = data;
    return;
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
