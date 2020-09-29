#include "header.h"
#include "prompt.h"
int sh;
char *ex_st[]={"✔️  :')","❌ :'("};

ll popwer(ll a,ll b)
{
    ll res=1;
    for(ll i=0;i<b;i++)
    res*=a;
    return res;
}
void msg()
{
    printf("\033[1;34m\n<<==============================================================>>\033[0m\n");
    printf("\033[1;31m                    😈 WELCOME IN A-HELL 😈\n");
    printf("\033[0;31m                                 - created by Archit Jain\n");
    printf("\033[1;34m<<==============================================================>>\033[0m\n");
}
void exitmsg()
{
    printf("\n\033[1;34m<<==============================================================>>\033[0m\n");
    printf("\033[1;31m                       OH HELL NO 👿\n");
    printf("\033[0;31m                         BYE !!!\n");
    printf("\033[1;34m<<==============================================================>>\033[0m\n");
    // exit(0);
}
void cinhand(int signum)
{

    if(cur_pid>0 && getpid()!=sh)
    {
        signal(SIGINT,SIG_IGN);
    }
    else
    {
        return;
    }
    
}
void zhand(int signum)
{
    if(cur_pid>0 && getpid()!=sh)
    {
        fprintf(stderr,"864z");
        if(kill(cur_pid,SIGTSTP)<0)
        {
            perror("Cannot kill by ^C ");
        }
        else
        {
            stat_pro[cur_pid]=2;
            char temp[100];
            sprintf(temp," Foreground process with pid %d has been stopped and sent in background\n",cur_pid);
            write(STDOUT_FILENO,temp,sizeof(temp));
        }
    }
    else
    {
     fprintf(stderr,"nothing");
        return;
    }
}

#include "pwd.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "cmd.h"
#include "pipe.h"
#include "boom.h"
#include "pinfo.h"
#include "env.h"
#include "jobs.h"
#include "history.h"
#include "nightwatch.h"
#include "redi.h"
#include "ppp.h"
// void chand(int signum)
// {
//     if(cur_pid>0)
//     {
//         if(kill(cur_pid,9)<0)
//         {
//             perror("Cannot kill by ^C ");
//         }
//         else
//         {
//             stat_pro[cur_pid]=2;
//             char temp[100];
//             sprintf(temp," Foregroung process with pid %d has been stopped and sent in background\n",cur_pid);
//             write(STDOUT_FILENO,temp,sizeof(temp));
//         }    
//     }
//     else
//     {
//         return;
//     } 
// }


typedef long long int ll;
int zpipp=0;
int main()
{
    system("clear");
    sh=getpid();
    // signal(SIGTERM,handler_exit);
    stdin_fd = dup(STDIN_FILENO);
    stderr_fd = dup(STDERR_FILENO);
    stdout_fd = dup(STDOUT_FILENO); 
    job_counter=0;
    exit_fail=0;
    cur_pid=-1;
    order[job_counter][0]=getpid();
    stat_pro[order[job_counter][0]]=1;
    order[job_counter][1]=0;
    strcpy(back_pro[order[job_counter][0]],"./A-Hell");
    job_counter++;

    msg();
    prompt_init();
    while(1)
    {

    signal(SIGTSTP,zhand);
    signal(SIGINT, cinhand);


        strcpy(predir,curdir);
        getcwd(curdir,sizeof(curdir));
        if(zpipp==0)
        {
            strcpy(predir,curdir);
            zpipp++;
        }
        prompt_pathy();
        sprintf(dis, "%s <\033[1;32m%s\033[0m@\033[1;32m%s\033[0m:\033[1;34m%s\033[0m> ",ex_st[exit_fail],user,host,dir);
        fprintf(stdout,"%s",dis);
        fflush(stdout);

        
        // strcpy(a," \0");
        exit_fail=0;
        cur_pid=-1;
        strcpy(a,"");
        fgets(a,sizeof(a),stdin);
        a[strlen(a)-1]='\0';
        
       
    
        if (a == NULL) {
            printf("Shell is exited due to ctrl+D\n");  /* Exit on Ctrl-D */
            exitmsg();
            exit(0);
            break;
        }
        ll ctd=1;
        for (ll i = 0; i < strlen(a); i++)
        {
            if(a[i]!=' '|| a[i]!='\0')
            {
                ctd=0;
                break;
            }
        }
        
        if(ctd==1)
        {
            exitmsg();
            exit(0);
            break;
        }

        // scanf("%[^\n]s",a);
        addhistory(a,execut);

        ll ink=0; 
        char* cmdd =(char *)malloc(1024*(sizeof(char)));
        cmdd= strtok(a, ";");
        while( cmdd != NULL ) 
        {
            strcpy(arc[ink],cmdd);
            ink++;
            cmdd = strtok(NULL, ";");
        }
        ll pop=0;
        ll fu_pipe=0;
        ll fu_redi=0;
        ll fu_boom=0;
        while( pop<=ink ) 
        {
            ll pin=0;
            strcpy(amd,arc[pop]);
            amd[strlen(a)]='\0';
            while(amd[pin]==' ' ||amd[pin]=='\t' )
            pin++;

            if(amd[pin]=='\0' && pop==0)
            {
                exitmsg();
                exit(0);
            }
                fu_pipe=0;
                fu_redi=0;
                fu_boom=0;
                for(ll xi=0;xi<strlen(amd);xi++)
                {
                    if(amd[xi]=='|')
                    fu_pipe++;
                    if(amd[xi]=='<' || amd[xi]=='>')
                    fu_redi++;
                    if(amd[xi]=='@' || amd[xi]=='$')
                    fu_boom++;

                }


                if(fu_boom!=0)
                {
                    callingboom(amd);
                }

                else if(fu_pipe!=0)
                {
                    callingpiponly(amd);
                }
                else if(fu_redi!=0)
                {
                    callingredi(amd);
                }

            // pwd 
            else if(amd[pin]=='p' && amd[pin+1]=='w' && amd[pin+2]=='d')
            {
                pin+=3;
                if(amd[pin]==' ' || amd[pin]=='\0')
                callingpwd(amd);
                else
                fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
            }
            // cd 
            else if(amd[pin]=='c' && amd[pin+1]=='d')
            {
                pin+=2;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingcd(amd,pin,execut);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }
            // echo 
            else if(amd[pin]=='e' && amd[pin+1]=='c' && amd[pin+2]=='h' && amd[pin+3]=='o')
            {
                pin+=4;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingecho(amd,pin,execut);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);

                }
            }

            // ls 
            else if(amd[pin]=='l' && amd[pin+1]=='s')
            {
                pin+=2;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingls(amd,pin,execut);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }
            else if(amd[pin]=='l' && amd[pin+1]=='a')
            {
                pin+=2;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingla(amd,pin,execut);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // pinfo 
            else if(amd[pin]=='p' && amd[pin+1]=='i' && amd[pin+2]=='n' && amd[pin+3]=='f' && amd[pin+4]=='o')
            {
                pin+=5;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingpinfo(amd,pin,execut);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // history 
            else if(amd[pin]=='h' && amd[pin+1]=='i' && amd[pin+2]=='s' && amd[pin+3]=='t' && amd[pin+4]=='o'&& amd[pin+5]=='r'&& amd[pin+6]=='y')
            {
                pin+=7;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callinghistory(amd,pin,execut);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // nightswatch
            else if(amd[pin]=='n' && amd[pin+1]=='i' && amd[pin+2]=='g' && amd[pin+3]=='h' && amd[pin+4]=='t'&& amd[pin+5]=='s'&& amd[pin+6]=='w' && amd[pin+7]=='a' && amd[pin+8]=='t' && amd[pin+9]=='c' && amd[pin+10]=='h')
            {
                pin+=11;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    nightwatch(amd,execut);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // setenv 
            else if(amd[pin]=='s' && amd[pin+1]=='e' && amd[pin+2]=='t' && amd[pin+3]=='e' && amd[pin+4]=='n'&& amd[pin+5]=='v')
            {
                pin+=6;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingsetenv(amd);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // unsetenv
            else if(amd[pin]=='u' && amd[pin+1]=='n' && amd[pin+2]=='s' && amd[pin+3]=='e' && amd[pin+4]=='t'&& amd[pin+5]=='e' && amd[pin+6]=='n'&& amd[pin+7]=='v')
            {
                pin+=8;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingunsetenv(amd);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }
            // jobs
            else if(amd[pin]=='j' && amd[pin+1]=='o' && amd[pin+2]=='b' && amd[pin+3]=='s')
            {
                pin+=4;
                if(amd[pin]==' ' || amd[pin]=='\0')
                callingjobs();
                else
                fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
            }
              
              // kjobs
            else if(amd[pin]=='k' && amd[pin+1]=='j' && amd[pin+2]=='o' && amd[pin+3]=='b')
            {
                pin+=4;
                if(amd[pin]==' ' || amd[pin]=='\0')
                callingkjob(amd);
                else
                fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
            }
            else if(amd[pin]=='o' && amd[pin+1]=='v' && amd[pin+2]=='e' && amd[pin+3]=='r' && amd[pin+4]=='k'&& amd[pin+5]=='i' && amd[pin+6]=='l'&& amd[pin+7]=='l')
            {
                pin+=8;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingoverkill();
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // fg
            else if(amd[pin]=='f' && amd[pin+1]=='g')
            {
                pin+=2;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingfg(amd);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // bg
            else if(amd[pin]=='b' && amd[pin+1]=='g')
            {
                pin+=2;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    while(amd[pin]==' ')
                    {
                        pin++;
                    }
                    callingbg(amd);
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // exit 
            else if(amd[pin]=='e' && amd[pin+1]=='x' && amd[pin+2]=='i' && amd[pin+3]=='t')
            {
                pin+=4;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    exitmsg();
                    exit(0); 
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }
            // quit
            else if(amd[pin]=='q' && amd[pin+1]=='u' && amd[pin+2]=='i' && amd[pin+3]=='t')
            {
                pin+=4;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                    exitmsg();
                    exit(0); 
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // clear
            else if(amd[pin]=='c' && amd[pin+1]=='l' && amd[pin+2]=='e' && amd[pin+3]=='a' && amd[pin+4]=='r')
            {
                pin+=5;
                if(amd[pin]==' ' || amd[pin]=='\0')
                {
                system("clear");
                }
                else
                {
                    fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",amd);
                }
            }

            // other command
            else
            {	
                callingcmd(amd,pin,execut); 
            }
            pop++;

            if(ink!=pop && ink!=1)
            printf("\n");

        }
    }
}