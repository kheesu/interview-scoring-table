#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "header.h"


void get_average(head* table, int q) { //테이블의 모든 행에 평균값을 구한다.
    row* row = table->next;
    while (row != NULL) { //모든 행에 대해서
        int _sum = 0; //행들의 질문의 합계를 구함
        for (int i = 1; i <= q; i++) {
            _sum += row->data[i];
        }
        int _mean = _sum / q; //합계 나누기 질문 개수 == 평균값
        _sum = 0;
        row->data[q + 1] = _mean; //평균값 입력
        row = row->next; //다음 행으로 이동
    }
}

int check_floor_score(const row* using_row, int q, const int floor_score) {
    for (int i = 1; i <= q; i++) { //해당 열의 모든 질문 값들에 대해서
        if (using_row->data[i] < floor_score) { //질문 값이 과락점수보다 낮다면
            return 0; //False를 반환
        }
    }
    return 1; //통과하면 True를 반환
}

void sort_array(int* array, int num) { //버블 정렬으로 배열을 sorting함
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

int* make_average_array(head* table, int q, int people) { //테이블의 평균 값들로만 이루어진 배열을 반환
    row* using_row = table->next;
    int* average_array = malloc(sizeof(int) * people); //average array는 지원자수만큼의 크기를 가짐
    int cnt = 0;
    while (using_row != NULL) { //모든 행에 대해서
        average_array[cnt] = using_row->data[q + 1]; //행의 평균값을 가져옴
        using_row = using_row->next;
        cnt++;
    }
    sort_array(average_array, people); //배열을 정렬
    return average_array;
}

int paint_pass(head* table, int q, int average, int floor_score) { //합격자들을 입력함     
    row* p = table->next;
    int cnt = 0;
    while (p != NULL) { //모든 행에 대해서
        if (p->data[q + 1] == average && check_floor_score(p, q, floor_score)) { //지정된 평균값의 행을 갖으면서 과락점수를 맞춘 사람들에 대해
            p->data[q + 2] = 1; //합격 처리
            cnt++; //합격자수 +=1
        }
        p = p->next;
    }
    return cnt; //합격자수 반환
}

void paint_fail(head* table, int q) {
    row* p = table->next;
    while (p != NULL) { //모든 행에 대해서
        if (p->data[q + 2] != 1) {
            p->data[q + 2] = 0; //합격자가 아니라면 모두 불합격처리
        }
        p = p->next;
    }
}

void initilazie_table(head* table, int q) { //합격 여부를 초기화
    row* using_row = table->next;
    while (using_row != NULL) {
        using_row->data[q + 2] = 0; //모든 행의 합불여부를 0으로 초기화
        using_row = using_row->next;
    }
}

void score_people(head* table, int q, int floor_score, int pass_people_num) {
    get_average(table, q); //평균값을 우선 채워넣는다.
    initilazie_table(table, q); //테이블의 합불여부를 초기화한다.
    int people = how_many_people(table); //지원자수를 확인한다.
    int* average_array = make_average_array(table, q, people); //평균으로만 이루어진 배열을 만든다.
    int temp = average_array[0]; //이전에 사용한 평균 배열 값
    int cnt = 0; //현재 채워진 합격자수
    int i = 0; //평균 배열의 몇번째 원소를 순회하고 있는지 표시한다.
    while (cnt < pass_people_num && i < people) { //내림차순된 평균 배열의 앞부분부터 합격자를 채워넣는다.
        if (temp != average_array[i] || i == 0) { //이전에 사용한 평균 배열 값과 같지 않을 경우에만
            int pass_num = paint_pass(table, q, average_array[i], floor_score); //합격 처리한다.
            cnt += pass_num; //합격자수 증가
        }
        temp = average_array[i];
        i++;
    }

    paint_fail(table, q); //불합격자 처리를 한다.
}


int is_in_array(int* Array, int Array_length, int source) { //해당 배열에 source 값이 있는지 확인
    for (int i = 0; i < Array_length; i++) { //배열의 모든 요소를 순회하면서 source값과 일치하는지 확인
        if (Array[i] == source) {
            return 1;
        }
    }
    return 0;
}

int how_many_people(head* table) { //지원자수를 확인
    row* row = table->next;
    int result = 0; //지원자수를 count
    while (row != NULL) { //연결리스트(테이블)가 끝날 때까지 순회한다.
        result += 1;
        row = row->next;
    }
    return result;
}

void iterator(head* headrow, int q) { //테이블 전체를 출력한다.
    row* p = headrow->next;
    for (int i = 0; i < q + 3; i++) printf("%-20s", headrow->data[i]);
    puts("");
    while (p != NULL) { //모든 행에 대해서
        for (int i = 0; i < q + 3; i++) {
            printf("%-20d", p->data[i]); //행(배열)의 요소값들을 모두 출력한다.
        }
        printf("\n"); //Enter
        p = p->next;
    }
}


void exception_score_people(head* table, int q) { //합격자를 정하기 전에 예외처리를 하는 함수
    char c;

    if (table->next == NULL) { //테이블이 비었다면
        printf("EMPTY_TABLE_EXCEPTION: Empty Table.\n");
        return;
    }
    int floor_score;
    char buffer[BUFF_SIZE];

    //과락점수 예외처리
    while (1) {
        int failed = 0;
        printf("Enter the floor score\n");

        if (scanf("%4s", buffer) != 1) {
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
        floor_score = (int)strtol(buffer, NULL, 0);

        if (errno == ERANGE) fprintf(stderr, "Range error, try again\n");

        else if (floor_score > 100 || floor_score < 0) { // 유효한 숫자를 입력했는지 확인
            printf("WRONG_INPUT_EXCEPTION: Enter a valid number\n");
            floor_score = 0;
        }


        else if (floor_score < 0 || floor_score>90) { //과락점수는 0~90 사이어야함
            printf("INVALID_FLOOR_NUMBER_EXCEPTION: Minimum Score Must Be Between 0 and 90.\n");
        }

        else break;
    }
    
    int people = how_many_people(table);
    int pass_people_num;

    //합격자수 예외처리
    while (1) {
        int failed = 0;
        printf("Enter the pass people num\n");

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
        pass_people_num = (int)strtol(buffer, NULL, 0);

        if (errno == ERANGE) fprintf(stderr, "Range error, try again\n");

        if (pass_people_num > people || pass_people_num <= 0) { //합격자수는 1~ 지원자수 사이어야함
            printf("INVALID_PASS_PEOPLE_EXCEPTION: The number of openings must be a positive integer and cannot be larger than the number of applicants(%d)\n", people);
            failed = 1;
        }

        int isValid = is_valid_table(table, q); //테이블이 유효한지 확인함
        if (!isValid) {
            failed = 1;
        }

        if (failed == 0) break; //failed되지 않았을 때 무한반복문을 빠져나옴.
    }
    
    score_people(table, q, floor_score, pass_people_num); //score_people함수 실행.
}


void exception_get_average(head* table, int q) { //평균을 내기전 예외처리하는 함수
    if (table->next == NULL) {
        printf("EMPTY_TABLE_EXCEPTION: Table is empty\n"); //테이블이 비었다면
        return;
    };
    if (!is_valid_table(table, q)) { //테이블에 결측값이 있다면
        return;
    }
    get_average(table, q);
}

int is_valid_input(int num) { //각 셀에 들어가는 점수는 0과 100 사이어야함
    if (num < 0 || num > 100) {
        printf("WRONG_INPUT_EXCEPTION: Enter an integer between 0 and 100\n");
        return 0;
    }
    else {
        return 1;
    }
}

int is_valid_pk(head* headrow, int q, int pk) { //학번은 유일해야함, 학번이 유일한 값인지 확인
    row* using_row = headrow->next;
    while (using_row != NULL) { //모든 행을 순회하면서
        if (using_row->data[0] == pk) { //기존 행에서 현재 입력하려는 학번과 일치하는 값이 있다면
            return 0;
        }
    }
    return 1;
}

int is_valid_row(row* row, int q) { //한 행에 결측값이 없는지 확인
    for (int i = 0; i <= q; i++) { //배열을 순회하면서
        if (row->data[i] == 0) { //결측값이 있다면
            return 0;
        }
    }
    return 1;
}

int is_valid_table(head* headrow, int q) { //테이블이 유효한지 확인
    int people = how_many_people(headrow); //지원자수 확인
    int* used_pk = malloc(sizeof(int) * people); //이미 사용된 학번들
    row* using_row = headrow->next;
    int cnt = 0;
    while (using_row != NULL) {
        if (!is_valid_row(using_row, q)) { //결측값이 없는가
            print_row(using_row, q);
            printf("Row has missing value\n");
            free(used_pk);
            return 0;
        }
        if (is_in_array(used_pk, cnt, using_row->data[0])) { //학번이 중복되지는 않는가
            printf("Found duplicate Student ID (%d)\n", using_row->data[0]);
            free(used_pk);
            return 0;
        }
        used_pk[cnt] = using_row->data[0];
        cnt++;
        using_row = using_row->next;
    }
    free(used_pk);
    return 1;
}