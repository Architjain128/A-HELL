#include "header.h"
void callingunsetenv(char* str);

void callingsetenv(char* str)
{
    char *setinp[10];
    char set2inp[10000];
    char zalima[10000];
    const char setdelimiters[] = " \t\0";
    char *totken = strtok(str, setdelimiters);
    ll i=0;
    while (totken != NULL)
    {
        if(strcmp(totken,"setenv")!=0)
        {
            if(i==0)
            setinp[0]=totken;

            else
            {
                if(i==1)
                strcpy(set2inp,totken);
                else
                {
                    strcat(set2inp," ");
                    strcat(set2inp,totken);
                }
            }
            i++;
        }
        totken = strtok(NULL, setdelimiters);
    }
   
    if(i<2)
    {
        printf("\033[0;33m--> WARNING : value is NULL \033[0m\n");
        stpcpy(zalima,"unsetenv ");
        strcat(zalima,setinp[0]);
        callingunsetenv(zalima);
        strcpy(set2inp," ");
    }
    if(setenv(setinp[0],set2inp,1)==-1)
    {
        printf("\033[0;33m--> ERROR : setenv failed \033[0m\n");
        perror(";(");
        exit_fail=1;
        // exit(EXIT_FAILURE);
    }
    return;
}
