#include<stdio.h>
#include<stdlib.h>
#define MAXCHAR 3000

int daftar ()
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "Menu.txt";

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
