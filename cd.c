#include "header.h"

void callingcd(char *str,int zip, char *str1)
{
    char inp[10000];
    char *temp2=(char *)malloc(1024*(sizeof(char)));
    temp2 = strtok(str, " \t");
    ll i=0;
    while( temp2 != NULL && i<2 ) 
    {
        if(strcmp(temp2,"cd")!=0){
            if(i==0)
            strcpy(inp,temp2);
            i++;
        }
        temp2 = strtok(NULL, " \t");
    }

    if(strlen(inp)==0)
    {
        chdir(str1);
    }
    else
    { 
        if(i>1)
	    {
            fprintf(stdout,"\033[0;33m--> WARNING : syntax invalid, multiple arguments output for : [cd %s]\033[0m\n",inp);
          
	    }
        char *temp=(char *)malloc(100000*sizeof(char));
        strcpy(temp,inp);

        if(temp[0]=='~')
        {
            if(chdir(str1)<0){
            fprintf(stdout,"\033[1;31m--> ERROR : directory not found [ %s ]\033[0m\n",temp);
            exit_fail=1;
            }
            if(strlen(temp)!=1){
            temp[0]='.';
            if(chdir(inp)<0){
            fprintf(stdout,"\033[1;31m--> ERROR : directory not found [ %s ]\033[0m\n",temp);
            exit_fail=1;

            }
            }
        }
        else if(temp[0]=='-')
        {
            printf("%s\n",predir);
            if(chdir(predir)<0){
            fprintf(stdout,"\033[1;31m--> ERROR : directory not found [ %s ]\033[0m\n",temp);
            exit_fail=1;

            }
        }
        else{
            
            if(chdir(temp)<0){
            fprintf(stdout,"\033[1;31m--> ERROR : directory not found [ %s ]\033[0m\n",temp);
            exit_fail=1;
            }
        }

        free(temp);
    }
        free(temp2);

}