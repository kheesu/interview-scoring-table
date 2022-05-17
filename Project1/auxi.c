#include <stdlib.h>
#include <stdio.h>
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
    };
};

int check_floor_score(row* using_row, int q, int floor_score) {
    for (int i = 1; i <= q; i++) {
        if (using_row->data[i] < floor_score) {
            return 0;
        };
    };
    return 1;
}; // boolean을 return

void sort_array(int* array, int num) { //bubble sort 내림차순
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
};

int* make_average_array(head* table, int q, int people) {
    row* using_row = table->next;
    int* average_array = malloc(sizeof(int) * people);
    int cnt = 0;
    while (using_row != NULL) {
        average_array[cnt] = using_row->data[q + 1];
        using_row = using_row->next;
        cnt++;
    };
    sort_array(average_array, people);
    return average_array;
};

int paint_pass(head* table, int q, int average, int floor_score) {             //해당 점수로 구현된 합격자수를 반환
    row* p = table->next;
    int cnt = 0;
    while (p != NULL) {
        if (p->data[q + 1] == average && check_floor_score(p, q, floor_score) ){
            p->data[q + 2] = 1;
            cnt++;
        };
        p = p->next;
    };
    return cnt;
};

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
    get_average(table, q); //먼저 평균을 구한다.
    int people = how_many_people(table);
    int* average_array = make_average_array(table, q, people);
    int temp = average_array[0];
    int cnt = 0;
    int i = 0;
    while (cnt < pass_people_num && i<people) {
        if (temp != average_array[i] || i == 0) {
            int pass_num = paint_pass(table, q, average_array[i], floor_score);
            cnt += pass_num;
            i++;
        };
    };
    
    paint_fail(table, q);
};


int is_in_array(int* Array, int Array_length, int source) {
    for (int i = 0; i < Array_length; i++) {
        if (Array[i] == source) {
            return 1;
        };
    };
    return 0;
}; //return boolean

int how_many_people(head* table) {
    row* row = table->next;
    int result = 0;
    while (row != NULL) {
        result += 1;
        row = row->next;
    };
    return result;
};

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
