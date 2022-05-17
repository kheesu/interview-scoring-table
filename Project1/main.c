#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


/*
int main() {
    int q;                                                          //Sets the number of questions for the table
    printf("Enter Number of Questions : ");
    scanf("%d", &q);
    head* headrow;                                  //Generates the table
    headrow = table_init(q);
    
    //for (int i = 0; i < q + 3; i++) {                                //Tests whether the head row was correctly generated
    //    printf("%s\n", headrow->data[i]);
    //}

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
            head *temp = csv_in(buffer);
            if (temp != NULL) {
                headrow = temp;
                q = headrow->config[0] - 3;
            }
        }

        else if (buffer[0] == '8'){
            get_average(headrow, q);
        }

        else if (buffer[0] == '9'){
            int floor_score;
            scanf("%d", &floor_score);
            int pass_people_num;
            scanf("%d", &pass_people_num);
            score_people(headrow, q, floor_score, pass_people_num);
        }

        else if (buffer[0] == '!') return 0;
        else printf("Enter valid character\n");
    }
    return 0;
}
*/

int main() {
    char buffer[BUFF_SIZE];
    head* table;
    int q;
    char c;

    while (1) {
        printf("Enter\n1 to create new table\n2 to load table from CSV file\n0 to exit program\n");
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

                if (q > 1024 || q < 1) printf("Enter Valid Number\n");

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
        printf("Enter\n1 to print table\n 2 to add entry,\n 3 to search for a value\n 4 to update the row of searched value\n 5 to delete the row of searched value\n 6 to save current table as csv\n");
        if (scanf("%4095s", buffer) != 1) {
            fprintf(stderr, "INPUT ERROR\n");
            return -1;
        }

        while ((c = getchar()) != '\n' && c != EOF);                                 //Flush stdin

        if (buffer[0] < '1' || buffer[0] > '6' || buffer[1] != '\0')
            printf("Invalid input, try again\n");

        else if (buffer[0] == '1') {

        }
    }


}