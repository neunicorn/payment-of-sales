#include<stdio.h>
#include<stdlib.h>
#define MAXCHAR 3000


void income(){

    FILE *income;

    char str[MAXCHAR];
    char* filename = "income.txt";

    income = fopen(filename, "r");
    if(income == NULL){
        printf("Could not open file\n");
        return 1;
    }
    while(fgets(str, MAXCHAR, income) != NULL){
        printf("%s", str);
    }
    fclose(income);

}

