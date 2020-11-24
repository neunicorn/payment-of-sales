#include<stdio.h>
#include<stdlib.h>
#define MAXCHAR 3000

int history_payment ()
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "program.txt";

    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Could not open file\n");
        return 1;
    }
    while(fgets(str, MAXCHAR, fp) != NULL){
        printf("%s", str);
    }
    fclose(fp);



}
