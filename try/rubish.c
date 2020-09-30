# include"header.h"

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


void boom(char *str){
    ll i=0;
    const char boomdelimiters[] = "@$";
ll j=0;
for (ll i = 0; i < strlen(str); i++)
{
    if(str[i]=='@')
    {
        sym[j]=1;
        j++;
    }
    if(str[i]=='$')
    {
        sym[j]=0;
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
    ll boom_num=i-1;
    ll boom_cmd=i;
    ll temp_exit_fail = 0;
    for (ll i = 0; i < boom_cmd; i++)
    {
        sym_exit[i]=0;
        if(i==0 || (sym_exit[i-1]==1 && sym[i-1]==0) ||(sym_exit[i-1]==0 && sym[i-1]==1))
        {
            getboom(i);
            printf("collected %lld\n",i);
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
            }
        }
    }
    for(ll i=0;i<boom_num;i++)
    {
        printf("%d %d\n",sym[i],sym_exit[i]);
    }
}

int main(){
        exit_fail=0;
        strcpy(a,"");
        fgets(a,sizeof(a),stdin);
        a[strlen(a)-1]='\0';

        boom(a);
}