# include "header.h"


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
                perror("could not run bg process");
                exit_fail=1;
            }
        }
    }
    return;
}

