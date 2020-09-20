#include "header.h"

void callingsetenv(char* str)
{
    int set_flag_arg=0;
    char *setinp[100];
    const char setdelimiters[] = " \t\0";
    char *totken = strtok(str, setdelimiters);
    ll i=0;
    while (totken != NULL)
    {
        if(strcmp(totken,"setenv")!=0)
        {
            setinp[i]=totken;
            i++;
        }
        totken = strtok(NULL, setdelimiters);
    }
    if(set_flag_arg==1)
    printf("\033[0;33m--> WARNING : too many arguments \033[0m\n");
    if(i<2)
    {
        printf("\033[0;33m--> WARNING : value is NULL \033[0m\n");
        strcpy(setinp[1],"");
    }
    if(setenv(setinp[0],setinp[1],1)==-1)
    {
        printf("\033[0;33m--> ERROR : setenv failed \033[0m");
        perror(";(");
    }
}

void callingunsetenv(char* str)
{
    int unset_flag_arg=0;
    char *unsetinp[100];
    const char unsetdelimiters[] = " \t\0";
    char *totken = strtok(str, unsetdelimiters);
    ll i=0;
    while (totken != NULL)
    {
        if(strcmp(totken,"unsetenv")!=0)
        {
            unsetinp[i]=totken;
            i++;
        }
        totken = strtok(NULL, unsetdelimiters);
    }
    if(unset_flag_arg==1)
    printf("\033[0;33m--> WARNING : too many arguments \033[0m\n");
   
    if(unsetenv(unsetinp[0])==-1)
    {
        printf("\033[0;33m--> ERROR : unsetenv failed \033[0m");
        perror(";(");
    }
}