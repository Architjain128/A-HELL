# include "header.h"

void callingjobs(){
    ll j=0;
    for (ll i=0;i<job_counter;i++)
    {
        if(order[i][1]==0)
        {
            printf("[%lld] running as shell %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);
            j++;
        }
        else if(order[i][1]==-1 || stat_pro[order[i][0]]==2)
        {
            if(stat_pro[order[i][0]]==0)
            {
                printf("[%lld] stopped %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);
            }
            else if(stat_pro[order[i][0]]==2)
            {
                char * var2=(malloc(sizeof(char)*1005));
                sprintf(var2,"/proc/%d/stat",order[i][0]);
                FILE *f =fopen(var2,"r");
                if(f==NULL) 
                {
                    printf("[%lld] stopped (unknown) %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);
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
    return;
}



void callingkjob(char *str)
{
 char *kjobinp[10];
    const char setdelimiters[] = " \t\0";
    char *totken = strtok(str, setdelimiters);
    ll i=0;
    while (totken != NULL)
    {
        if(i>=5)break;
        if(strcmp(totken,"kjob")!=0)
        {
            kjobinp[i]=totken;
            i++;
        }

        totken = strtok(NULL, setdelimiters);
    }
    if(i<2)
    {
        fprintf(stdout,"\033[1;31m--> ERROR : to few arguments \033[0m\n");
        exit_fail=1;

    }
    if(i>2)
    {
        fprintf(stdout,"\033[1;31m--> ERROR : too many arguments \033[0m\n");
        exit_fail=1;
    }
    if(i==2)
    {
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
        exit_fail=1;

                break;
            }
            
        }
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
        exit_fail=1;

                break;
            }
        }

        ll zcurpid=-1;
        ll pik=0;
        for(int j=0;j<job_counter;j++)
        {
            if(order[j][1]==-1 || stat_pro[order[j][0]]==2)
            {
                pik++;
                if(pik==jnum)
                {
                    zcurpid=order[j][0];
                    break;
                }
            }
        }
        if(pik<jnum)
        {
            fprintf(stdout,"\033[1;31m--> ERROR : job number does not exists\033[0m\n");
        exit_fail=1;

            // exit(EXIT_FAILURE);
        }
        else{
            if(zcurpid==-1)
            {
                fprintf(stdout,"\033[1;31m--> ERROR : you can not kill running shell\033[0m\n");
        exit_fail=1;

                // exit(EXIT_FAILURE);
            }
            else{
                if(kill(zcurpid,jsig)<0)
                {
                    perror("kjob");
        exit_fail=1;

                    // exit(EXIT_FAILURE);
                }
                if(jsig==9)
                {
                    stat_pro[zcurpid]=0;
                }
            }
        }
    }
    return;
}



void callingoverkill()
{
    for(int j=0;j<job_counter;j++)
    {
        if(order[j][1]==-1 )
        {
            if(kill(order[j][0],9)<0)
            {
                // perror("kjob");
            }
            stat_pro[order[j][0]]=0;
        }
    }
    return;
}



void callingfg(char *str)
{
    char *fginp[10];
    const char setdelimiters[] = " \t\0";
    char *totken = strtok(str, setdelimiters);
    ll i=0;
    while (totken != NULL)
    {
        if(i>=2)break;
        if(strcmp(totken,"fg")!=0)
        {
            fginp[i]=totken;
            i++;
        }
        totken = strtok(NULL, setdelimiters);
    }
    if(i<1)
    {
        fprintf(stdout,"\033[1;31m--> ERROR : to few arguments \033[0m\n");
        exit_fail=1;

        // exit(EXIT_FAILURE);
    }
    if(i>12)
    {
        fprintf(stdout,"\033[1;31m--> ERROR : too many arguments \033[0m\n");
        exit_fail=1;

        // exit(EXIT_FAILURE);
    }
    if(i==1)
    {
        ll num=0;
        ll base=pow(10,strlen(fginp[0])-1);
        for(ll o=0;o<strlen(fginp[0]);o++)
        {   
            ll u=fginp[0][o]-'0';
            if(u>=0 && u<=9){
            num+=(u*base);
            base/=10;
            }
            else
            {
                fprintf(stdout,"\033[1;31m--> ERROR : [%s] is not an integer \033[0m\n",fginp[0]);
        exit_fail=1;

                break;
            }
        }
        ll zcurpid=-1;
        ll pik=0;
        for(int j=0;j<job_counter;j++)
        {
            if(order[j][1]==-1 || stat_pro[order[j][0]]==2 )
            {
                pik++;
                if(pik==num)
                {
                    zcurpid=order[j][0];
                    break;
                }
            }
        }
        if(pik<num)
        {
            fprintf(stdout,"\033[1;31m--> ERROR : job number does not exists\033[0m\n");
        exit_fail=1;

        }
        else
        {
            char * var2=(malloc(sizeof(char)*1005));
            sprintf(var2,"/proc/%lld/stat",zcurpid);
            FILE *fd = fopen(var2,"r");
			if((fd=fopen(var2,"r"))==NULL)
			{
				printf("No such process in background\n");
			}
			else
			{
                cur_pid=zcurpid;
				kill(zcurpid,SIGCONT);
                stat_pro[zcurpid]=0;
				waitpid(-1,NULL,WUNTRACED);
			}
        }
    }
    return;
}

void callingbg(char *str){
    char *bginp[10];
    const char bdelimiters[] = " \t\0";
    char *totken = strtok(str, bdelimiters);
    ll i=0;
    while (totken != NULL)
    {
        if(i>=2)break;
        if(strcmp(totken,"bg")!=0)
        {
            bginp[i]=totken;
            i++;
        }

        totken = strtok(NULL, bdelimiters);
    }
    if(i<1)
    {
        fprintf(stdout,"\033[1;31m--> ERROR : to few arguments \033[0m\n");
        exit_fail=1;

        // exit(EXIT_FAILURE);
    }
    else if(i>1)
    {
        fprintf(stdout,"\033[1;31m--> ERROR : too many arguments \033[0m\n");
        exit_fail=1;

        // exit(EXIT_FAILURE);
    }
    else if(i==1)
    {
        ll num=0;
        ll base=pow(10,strlen(bginp[0])-1);
        for(ll o=0;o<strlen(bginp[0]);o++)
        {   
            ll u=bginp[0][o]-'0';
            if(u>=0 && u<=9){
            num+=(u*base);
            base/=10;
            }
            else
            {
                fprintf(stdout,"\033[1;31m--> ERROR : [%s] is not an integer \033[0m\n",bginp[0]);
                exit_fail=1;

                break;
            }
            
        }


        ll zcurpid=-1;
        ll pik=0;
        for(int j=0;j<job_counter;j++)
        {
            if(order[j][1]==-1 || stat_pro[order[j][0]]==2 )
            {
                pik++;
                if(pik==num)
                {
                    zcurpid=order[j][0];
                    break;
                }
            }
        }
        if(pik<num)
        {
            fprintf(stdout,"\033[1;31m--> ERROR : job number does not exists\033[0m\n");
            exit_fail=1;
        }
        else
        {
            if(kill(zcurpid, SIGCONT)<0)
            {
                perror("bg");
                exit_fail=1;
            }
        }
    }
    return;
}

