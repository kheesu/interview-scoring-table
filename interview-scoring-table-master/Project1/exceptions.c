#include <stdlib.h>
#include <stdio.h>
#include "header.h"


void exception_score_people(head* table, int q) { //어떻게 str을 안 받지...
    if (table->next == NULL) {
        printf("EMPTY_TABLE_EXCEPTION: 테이블이 비어 있습니다.\n");
        return;
    };
    int floor_score;
    printf("Enter the floor score\n");
    scanf("%d", &floor_score);
    if (floor_score < 0 || floor_score>90) {
        printf("INVALID_FLOOR_NUMBER_EXCEPTION: 과락점수는 0~90 사이의 값이어야 합니다.\n");
        return;
    };
    int people = how_many_people(table);
    int pass_people_num;
    printf("Enter the pass people num\n");
    scanf("%d", &pass_people_num);
    if (pass_people_num > people || pass_people_num <=0) {
        printf("INVALID_PASS_PEOPLE_EXCEPTION: 합격자수는 자연수여야 하며, 현재 인원수( %d )보다 많아서는 안됩니다. \n", people);
        return;
    };
    int isValid = is_valid_table(table, q);
    if (!isValid) {
        return;
    };
    score_people(table, q, floor_score, pass_people_num);
};

void exception_get_average(head* table, int q) {
    if (table->next == NULL) {
        printf("EMPTY_TABLE_EXCEPTION: 테이블이 비어 있습니다.\n");
        return;
    };
    if (!is_valid_table(table, q)) {
        return;
    };
    get_average(table, q);
};

int return_valid_input() {
    char buffer[BUFF_SIZE];
    scanf("%1000s", buffer);
    int num = atoi(buffer);
    if (num <= 0 || num > 100) {
        printf("WRONG_INPUT_EXCEPTION: 1에서 100사이의 값을 입력하세요.\n");
        return 0;
    }
    else {
        return num;
    };
};

int is_valid_pk(head* headrow, int q, int pk) {
    row* using_row= headrow->next;
    while (using_row != NULL) {
        if (using_row->data[0] == pk) {
            return 0;
        };
        using_row = using_row->next;
    };
    return 1;
}; //return boolean

int is_valid_row(row* row, int q) {
    for (int i = 0; i <= q; i++) {
        if (row->data[i] == NULL) {
            return 0;
        };
    };
    return 1;
}; //return boolean

int is_valid_table(head* headrow, int q) {
    int people = how_many_people(headrow);
    int* used_pk = malloc(sizeof(int) * people);
    row* using_row = headrow->next;
    int cnt = 0;
    while (using_row != NULL) {
        if (!is_valid_row(using_row, q)) {
            print_row(using_row, q);
            printf("해당 행에 결측값이 있습니다.\n");
            return 0;
        }; //행에 결측값이 있는지 확인
        if (is_in_array(used_pk, cnt, using_row->data[0])) {
            printf("학번(%d)가 중복되었습니다.", using_row->data[0]);
            return 0;
        }; //각 행의 학번이 유일한 값인지 확인
        used_pk[cnt] = using_row->data[0];
        cnt++;
        using_row = using_row->next;
    };
    return 1;
};