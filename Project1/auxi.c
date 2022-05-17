#include <stdio.h>
#include <stdlib.h>
#include "header.h"


void get_average(head* table, int q) {
    row* row = table->next;
    while (row != NULL) {
        int _sum = 0;
        for (int i = 1; i <= q; i++) {
            _sum += row->data[i];
        };
        int _mean = _sum / q;
        _sum = 0;
        row->data[q + 1] = _mean;
        row = row->next;
    }
}

int check_floor_score(const row* using_row, int q, const int floor_score) {
    for (int i = 1; i <= q; i++) {
        if (using_row->data[i] < floor_score) {
            return 0;
        }
    }
    return 1;
}

void sort_array(int* array, int num) { //bubble sort 
    int temp;
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num - 1; j++)
        {
            if (array[j] < array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int* make_average_array(head* table, int q, int people) {
    row* using_row = table->next;
    int* average_array = malloc(sizeof(int) * people);
    int cnt = 0;
    while (using_row != NULL) {
        average_array[cnt] = using_row->data[q + 1];
        using_row = using_row->next;
        cnt++;
    }
    sort_array(average_array, people);
    return average_array;
}

int paint_pass(head* table, int q, int average, int floor_score) {             
    row* p = table->next;
    int cnt = 0;
    while (p != NULL) {
        if (p->data[q + 1] == average && check_floor_score(p, q, floor_score)) {
            p->data[q + 2] = 1;
            cnt++;
        }
        p = p->next;
    };
    return cnt;
}

void paint_fail(head* table, int q) {
    row* p = table->next;
    while (p != NULL) {
        if (p->data[q + 2] != 1) {
            p->data[q + 2] = 0;
        }
        p = p->next;
    };
}

void score_people(head* table, int q, int floor_score, int pass_people_num) {
    get_average(table, q);
    int people = how_many_people(table);
    int* average_array = make_average_array(table, q, people);
    int temp = average_array[0];
    int cnt = 0;
    int i = 0;
    while (cnt < pass_people_num && i < people) {
        if (temp != average_array[i] || i == 0) {
            int pass_num = paint_pass(table, q, average_array[i], floor_score);
            cnt += pass_num;
        }
        temp = average_array[i];
        i++;
    }

    paint_fail(table, q);
}


int is_in_array(int* Array, int Array_length, int source) {
    for (int i = 0; i < Array_length; i++) {
        if (Array[i] == source) {
            return 1;
        }
    }
    return 0;
}

int how_many_people(head* table) {
    row* row = table->next;
    int result = 0;
    while (row != NULL) {
        result += 1;
        row = row->next;
    }
    return result;
}

void iterator(head* headrow, int q) {
    row* p = headrow->next;
    for (int i = 0; i < q + 3; i++) printf("%-20s", headrow->data[i]);
    puts("");
    while (p != NULL) {
        for (int i = 0; i < q + 3; i++) {
            printf("%-20d", p->data[i]);
        }
        printf("\n");
        p = p->next;
    }
}


void exception_score_people(head* table, int q) { 
    char c;

    if (table->next == NULL) {
        printf("EMPTY_TABLE_EXCEPTION: Empty Table.\n");
        return;
    };
    int floor_score;
    printf("Enter the floor score\n");

    if (scanf("%3d", &floor_score) != 1) {
        fprintf(stderr, "INPUT ERROR\n");
        exit(-1);
    }

    while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

    if (floor_score < 0 || floor_score>90) {
        printf("INVALID_FLOOR_NUMBER_EXCEPTION: Minimum Score Must Be Between 0 and 90.\n");
        return;
    };
    int people = how_many_people(table);
    int pass_people_num;
    printf("Enter the pass people num\n");
    ;
    if (scanf("%5d", &pass_people_num) != 1) {
        fprintf(stderr, "INPUT ERROR\n");
        exit(-1);
    }

    while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

    if (pass_people_num > people || pass_people_num <= 0) {
        printf("INVALID_PASS_PEOPLE_EXCEPTION: The number of openings must be a positive integer and cannot be larger than the number of applicants(%d)\n", people);
        return;
    };
    int isValid = is_valid_table(table, q);
    if (!isValid) {
        return;
    }
    score_people(table, q, floor_score, pass_people_num);
}

void exception_get_average(head* table, int q) {
    if (table->next == NULL) {
        printf("EMPTY_TABLE_EXCEPTION: Table is empty\n");
        return;
    };
    if (!is_valid_table(table, q)) {
        return;
    };
    get_average(table, q);
}

int is_valid_input(int num) {
    if (num < 0 || num > 100) {
        printf("WRONG_INPUT_EXCEPTION: Enter an integer between 0 and 100\n");
        return 0;
    }
    else {
        return 1;
    };
}

int is_valid_pk(head* headrow, int q, int pk) {
    row* using_row = headrow->next;
    while (using_row != NULL) {
        if (using_row->data[0] == pk) {
            return 0;
        };
    };
    return 1;
}

int is_valid_row(row* row, int q) {
    for (int i = 0; i <= q; i++) {
        if (row->data[i] == NULL) {
            return 0;
        };
    };
    return 1;
}

int is_valid_table(head* headrow, int q) {
    int people = how_many_people(headrow);
    int* used_pk = malloc(sizeof(int) * people);                //Memory leak? Where does used_pk go?
    row* using_row = headrow->next;
    int cnt = 0;
    while (using_row != NULL) {
        if (!is_valid_row(using_row, q)) {
            print_row(using_row, q);
            printf("Row has missing value\n");
            return 0;
        }; 
        if (is_in_array(used_pk, cnt, using_row->data[0])) {
            printf("Found duplicate Student ID (%d)\n", using_row->data[0]);
            return 0;
        }; 
        used_pk[cnt] = using_row->data[0];
        cnt++;
        using_row = using_row->next;
    };
    return 1;
}