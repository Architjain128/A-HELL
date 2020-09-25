#include "header.h"

void callingpinfo(char *str,int zip,char *str1)  
{
    char procky[10000];
    char memory[10000];
    char exec[10000];
    char states[10000];
    char inp[10][1000];
    char *temp2;
    ll i=0;
    temp2 = strtok(str, " \t");
    while( temp2 != NULL && i<10 ) 
    {
        if(strcmp(temp2,"pinfo")!=0){
            strcpy(inp[i],temp2);
            i++;
        }
        temp2 = strtok(NULL, "  \t");
    }
    ll pidnum=0;

    if(i==0)
    {
        pidnum = getpid();
        // printf("pid -- %lld\n",pidnum);
        sprintf(procky,"/proc/%lld",pidnum);
    }
    else
    {
        pidnum=0;
        ll base=pow(10,strlen(inp[0])-1);
        for(ll o=0;o<strlen(inp[0]);o++)
        {   
            ll u=inp[0][o]-'0';
            if(u>=0 && u<=9){
            pidnum+=(u*base);
            base/=10;
            }
            else
            {
                fprintf(stdout,"\033[1;31m--> ERROR : [%s] is not an integer \033[0m\n",inp[0]);
                exit_fail=1;
                return;
            }
            
        }
        // printf("pid -- %s\n",pidnum);
        sprintf(procky,"/proc/%lld",pidnum);
    }


    if(access( procky, F_OK ) <0)
    {
        fprintf(stdout,"\033[1;31m--> ERROR :file %s not found\033[0m\n",procky);
        exit_fail=1;
    }
    else
    {
        printf("pid -- %lld\n",pidnum);

        ll count=0,fl=0,fl2=0;
        strcpy(states,procky) ;
        int l=strlen(states);
        states[l]='/';
        states[l+1]='s';
        states[l+2]='t';
        states[l+3]='a';
        states[l+4]='t';
        states[l+5]='u';
        states[l+6]='s';
        states[l+7]='\0';
        FILE *fp = fopen(states,"r");
        while( fscanf(fp, "%s", memory) != EOF )
        {
            count++;
            if(!strcmp("State:",memory))
            {
                fl++;
                fl2=1;
                continue;
            }
            else if(!strcmp("VmSize:",memory))
            {
                fl++;
                fl2=2;
                continue;
            }
            if(fl2!=0)
            {
                if(fl2==1)
                {
                    printf("Process Status -- %s\n",memory);	
                    fl2=0;
                }
                else if(fl2==2)
                {
                    printf("memory -- %s  {virtual memory}\n",memory);
                    fl2=0;
                }
            }
        }
        if(fl!=2)
        {
            printf("memory -- ?\n");
        }
        l=strlen(procky);
            procky[l]='/';
            procky[l+1]='e';
            procky[l+2]='x';
            procky[l+3]='e';
            procky[l+4]='\0';
            memset(states, 0, sizeof(states));
            int x= readlink(procky,states,1023);
            fl2=1;
            ll n1,n2;
            n1=strlen(states);
            n2=strlen(execut);
            for (i = 0; i < n2 && i < n1; ++i)
            {
                if(states[i]!=execut[i])
                    {
                        fl2=0;
                        break;
                    }
            }
            if(i==n2 && fl2==1)
            {
                exec[0]='~';
                for (int j = n2; j < n1+1; ++j)
                {
                    exec[j-n2+1]=states[j];
                }
            }
            else
            {
                for (int j = 0; j < n1+1; ++j)
                {
                    exec[j]=states[j];
                }
            }
            if(x<0){
                fprintf(stdout,"\033[1;31m--> ERROR : undefined path\033[0m\n");
            exit_fail=1;
            }
            else
            printf("Executable Path -- %s\n",exec );
    }
    free(temp2);
}