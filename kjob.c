# include "header.h"

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

