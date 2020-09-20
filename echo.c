#include "header.h"

void callingecho(char *str,int zip, char *str1)
{
    char *temp;
    temp=(char *)malloc(100000*sizeof(char));
    ll po=0;
    for(ll o=zip;o<strlen(str);o++)
    {
        temp[po]=str[o];
        po++;
    }
    temp[po]='\0';

    fprintf(stdout,"%s\n",temp);
    free(temp);
}