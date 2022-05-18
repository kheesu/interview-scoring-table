#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header.h"

//Output to csv
void csv_out(head* table, int q, char* name) {
    FILE* fp;
    fp = fopen(name, "w");
    for (int i = 0; i < q + 3; i++) {
        fprintf(fp, table->data[i]);
        if (i != q + 2) fputc(',', fp);
    }
    fputc('\n', fp);

    row* p = table->next;
    while (p != NULL) {
        for (int i = 0; i < q + 3; i++) {
            fprintf(fp, "%d", p->data[i]);
            if (i != q + 2) fputc(',', fp);
        }
        fputc('\n', fp);
        p = p->next;
    }
    fclose(fp);
}

//Read from csv
head* csv_in(const char* name) {
    FILE* fp = fopen(name, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error : File not found, retry\n");
        return NULL;
    }

    int col = 0;
    char ch, buffer[4096];
    head* table = calloc(1, sizeof(*table));

    fgets(buffer, 4096, fp);
    for (int i = 0; buffer[i] != '\n'; i++) {
        if (buffer[i] == ',') col++;
    }

    if (col == 0) {
        printf("Error : Invalid file, try again\n");
        return NULL;
    }

    int temp = 0;
    while (fgets(buffer, 4096, fp) != NULL) {
        for (int i = 0; buffer[i] != '\n'; i++) if (buffer[i] == ',') temp++;
        if (temp != col) {
            printf("Error : Invalid file, try again\n");
            return NULL;
        }
        temp = 0;
    }

    table->config[0] = ++col;
    fseek(fp, 0, SEEK_SET);

    char(*h)[MAX_LENGTH];
    h = calloc(sizeof(*h), col);
    table->data = h;
    char* tok;

    fgets(buffer, 4096, fp);
    buffer[strcspn(buffer, "\n")] = '\0';
    int i = 0;
    tok = strtok(buffer, ",");
    while (tok != NULL) {
        // printf("%s\n", tok);
        strcpy(h[i++], tok);
        tok = strtok(NULL, ",");
    }

    /*
    for(int i = 0; i < col; i++) {
        printf("%s %s\n", table->data[i], h[i]);
    }
    */

    while (fgets(buffer, 4096, fp) != NULL) {
        //printf("start\n");
        buffer[strcspn(buffer, "\n")] = '\0';

        row* new_row = calloc(1, sizeof *new_row);
        new_row->data = calloc(col, sizeof(int));
        new_row->next = NULL;

        tok = strtok(buffer, ",");
        for (int i = 0; i < col; i++, tok = strtok(NULL, ",")) {
            new_row->data[i] = (int)strtol(tok, NULL, 10);
            // printf("col %d [%s -> %d]\n", i, tok, new_row->data[i]);
        }

        if (!table->next) {
            table->next = new_row;
            table->tail = new_row;
        }
        else {
            table->tail->next = new_row;
            table->tail = new_row;
        }
        //printf("end\n");
    }

    return table;
}