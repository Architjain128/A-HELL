# include "header.h"


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

                signal(SIGTTIN, SIG_IGN);
                signal(SIGTTOU, SIG_IGN);

                tcsetpgrp(STDIN_FILENO, zcurpid);

                kill(zcurpid, SIGCONT);

                int st;
                waitpid(zcurpid, &st, WUNTRACED);
                tcsetpgrp(STDIN_FILENO, getpgrp());

                signal(SIGTTIN, SIG_DFL);
                signal(SIGTTOU, SIG_DFL);
    
                if (WIFSTOPPED(st)) {
                stat_pro[zcurpid]=0;
                }
                
				
			}
        }
    }
    return;
}