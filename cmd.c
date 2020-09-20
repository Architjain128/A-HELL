#include "header.h"
void callingcmd(char* str,int zip,char* str9)
{
    strcpy(helper,str);
	ll bg=0;
    ll i=0;
    int status;
    char *inp[10000];
    char *temp2;
    temp2 = strtok(str, " \t");            
    strcpy(helper,"");

    while( temp2 != NULL ) 
    {
        if(strcmp(temp2,"&")==0)bg=1;
        
        if(strcmp(temp2,"&")!=0){
            inp[i]=temp2;
            strcat(helper,temp2);
            strcat(helper," ");
            i++;
        }
        temp2 = strtok(NULL, "  \t");
    }
    inp[i]=NULL;
    int Rfork=fork();
    if(bg==1)
    {

       if(Rfork==0)
		{
            
			if(execvp(inp[0],inp)<0)
			{
				fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",helper);
				exit(0);
			}
		}
      
    }
    else
    {
        if(Rfork==0)
		{
			if(execvp(inp[0],inp)<0)
			{
				fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",helper);
				exit(0);	
			}
       
		}
		else
		{
			waitpid(Rfork,&status,0);
		}
    }
}