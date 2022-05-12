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

row* return_max_average_row(const head* table, int q, int floor_score, int* pass_people_array, int pass_people_array_cnt) {
    row* using_row = table->next;
    row* best_row = table->next;
    int best_row_data = using_row->data[q + 1];
    while (using_row != NULL) {
        if (!check_floor_score(using_row, q, floor_score)) {
            using_row = using_row->next;
            continue; //과락일 경우
        };
        for (int i = 0; i < pass_people_array_cnt; i++) {
            if (using_row->data[0] == pass_people_array[i]) {
                using_row = using_row->next;
                continue;
            }; //이미 담아진 합격자일 경우
        };
        if (using_row->data[q + 1] > best_row_data) {
            best_row_data = using_row->data[q + 1];
            best_row = using_row;
        };
        using_row = using_row->next;
    };
    return best_row;
};

int check_floor_score(row* using_row, int q, int floor_score) {
    for (int i = 1; i <= q; i++) {
        if (using_row->data[i] < floor_score) {
            return 0;
        };
    };
    return 1;
}; // boolean을 return


void score_people(head* table, int q, int floor_score, int pass_people_num) {
    get_average(table, q); //먼저 평균을 구한다.
    int people = how_many_people(table); //지원자들의 수.
    int* pass_people_array = malloc(sizeof(int) * pass_people_num);
    int pass_people_array_cnt = 0;
    for (int i = 0; i < pass_people_num; i++) { //합격자들의 학번 리스트를 만듬
        row* temp = return_max_average_row(table, q, floor_score, pass_people_array, pass_people_array_cnt);
        pass_people_array[pass_people_array_cnt] = temp->data[0];
        pass_people_array_cnt++;
    };
    for (int i = 0; i < people; i++) { //합격 불합격 나열
        row* using_row = table->next;
        if (is_in_array(pass_people_array, pass_people_array_cnt, using_row->data[0])) {
            using_row->data[q + 2] = 1; //합격
        }
        else {
            using_row->data[q + 2] = 0; //불합격
        };
    };
    free(pass_people_array);
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