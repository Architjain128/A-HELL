#include "header.h"

void callingecho(char *str,int zip, char *str1)
{
    char *temp2=(char *)malloc(1024*(sizeof(char)));
    temp2 = strtok(str, " \t");
    while( temp2 != NULL ) 
    {
        if(strcmp(temp2,"echo")!=0)
        printf("%s ",temp2);
        temp2 = strtok(NULL, " \t");
    }
    printf("\n");
    free(temp2);
}