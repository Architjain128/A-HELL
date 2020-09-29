# include "header.h"

void getboom(int a){
    ll j=0;
    const char delimiters[] = " \t\n\0";
    char *totken = strtok(extasks[a], delimiters);
    while (totken != NULL)
    {   
        exruntask[j]=totken;
        j++;
        totken = strtok(NULL, delimiters);
    }
    exruntask[j]=NULL;
}


void callingboom(char *str){
    ll i=0;
    const char boomdelimiters[] = "@$";

for (ll i = 0,j=0; i < strlen(str); i++)
{
    if(str[i]=='@')
    {
        sym[j]=0;
        j++;
    }
    if(str[i]=='$')
    {
        sym[j]=1;
        j++;
    }
}

    char *totken = strtok(str, boomdelimiters);
    while (totken != NULL)
    {
        extasks[i]=totken;
        i++;
        totken = strtok(NULL, boomdelimiters);
    }
    ll boom_cmd=i;

    for (ll i = 0; i < boom_cmd; i++)
    {
        sym_exit[i]=0;
        if(i==0 || (sym_exit[i-1]==1 && sym[i-1]==1) ||(sym_exit[i-1]==0 && sym[i-1]==0))
        {
            getboom(i);

            pid_t pid=fork();

            if(pid<0)
            {
                perror("fork");
                sym_exit[i]=1;
            }
            else if(pid==0)
            {
                if(execvp(exruntask[0],exruntask)<0)
                {
                    perror("cmd not found");
                    sym_exit[i]=1;
                }
            }
            else
            {
                wait(NULL);
                    sym_exit[i]=0;

            }
            // z=i;
        }
      
    }
//    exit_fail=sym_exit[z];
}