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

void callingjobs(){
    ll j=0;
	char * s = "stopped";
	char * r = "running";
    for (ll i=0;i<job_counter;i++)
    {
        if(order[i][1]==0)
        {
            printf("[%lld] running as shell %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);
            j++;
        }
        else if(order[i][1]==-1)
        {
            if(stat_pro[order[i][0]]==0)
            {
                printf("[%lld] stopped %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);
            }
            else 
            {
                char * var2=(malloc(sizeof(char)*1005));
                sprintf(var2,"/proc/%d/stat",order[i][0]);
                FILE *f =fopen(var2,"r");
                if(f==NULL) 
                {
                    // perror("unable to open file \n");
                    // return ;
                printf("[%lld] stopped %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);

                }
                else
                {
                    ll z=0;
                    int p;
                    char r[300];
                    char s;
                    char * atr;
                    for(z=0;z<3;z++)
                    {
                        if(z==0)   fscanf(f,"%d",&p);
                        if(z==1)   fscanf(f,"%s",r);
                        if(z==2)   fscanf(f," %c",&s);
                    }
                    if(s=='R') stat_pro[i]=2;
                    if(s=='S') stat_pro[i]=2;
                    if(s!='S'&&s!='R') stat_pro[i]=1;
                    if(stat_pro[i]==1)   atr="stopped";
                    else     atr="running";
                    printf("[%lld] %s %s [%d]\n",j,atr,back_pro[order[i][0]],order[i][0]);
                }

            }
            j++;
        }
    }
}




void callingkjob(char *str)
{
 char *kjobinp[100];
    const char setdelimiters[] = " \t\0";
    char *totken = strtok(str, setdelimiters);
    ll i=0;
    while (totken != NULL)
    {
        if(i>=2)break;
        if(strcmp(totken,"kjob")!=0)
        {
            kjobinp[i]=totken;
            i++;
        }

        totken = strtok(NULL, setdelimiters);
    }

    ll jnum=0;
    ll jsig=0;
     ll base=pow(10,strlen(kjobinp[0])-1);
        for(ll o=0;o<strlen(kjobinp[0]);o++)
        {   
            ll u=kjobinp[0][o]-'0';
            if(u>=0 && u<=9){
            jnum+=(u*base);
            base/=10;
            }
            else
            {
                fprintf(stdout,"\033[1;31m--> ERROR : [%s] is not an integer \033[0m\n",kjobinp[0]);
                break;
            }
            
        }
        // printf("%s %s\n",kjobinp[0],kjobinp[1]);

    base=pow(10,strlen(kjobinp[1])-1);
        for(ll o=0;o<strlen(kjobinp[1]);o++)
        {   
            ll u=kjobinp[1][o]-'0';
            if(u>=0 && u<=9){
            jsig+=(u*base);
            base/=10;
            }
            else
            {
                fprintf(stdout,"\033[1;31m--> ERROR : [%s] is not an integer \033[0m\n",kjobinp[1]);
                break;
            }
        }
        // printf("%lld %lld\n",jnum,jsig);
ll zcurpid=-1;
    for(int j=0;j<job_counter;j++)
    {
        ll pik=0;
       
        if(order[j][1]==-1 )
        {
            pik++;
            if(pik=jnum)
            {
                zcurpid=order[j][0];
                break;
            }
        }
    }
    printf("%lld\n",zcurpid);
}
//     ll f=0;
//     ll j=0,i=0,pid;
//     ll x1= atoi(args[1]);
//     while(i<1000005)
//     {
//         if(status[i]==0)
//         {
//             //chill
//         }
//         else
//         {
//             j++; //running jobs ++   
//             if(x1==j)
//             {
//                 pid = i,f=1;
//                 break;
//             }   
//         }
//         i++;
//     }   
//     ll x=atoi(args[2]);
//     // printf("%lld%lld\n",x,pid );
//     kill(pid,x);
//     if(x==9) {
//         status[pid];
//         bg_arr[pid]= NULL;
//     }
// }