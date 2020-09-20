#include "header.h"
#include "prompt.h"

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
    printf("\033[1;31m                     WELCOME IN A-HELL\n");
    printf("\033[0;31m                                - created by Archit Jain\n");
    printf("\033[1;34m<<==============================================================>>\033[0m\n");
}
void exitmsg()
{
    printf("\033[1;34m<<==============================================================>>\033[0m\n");
    printf("\033[1;31m                     OH HELL NO :(\n");
    printf("\033[0;31m                         BYE !!!\n");
    printf("\033[1;34m<<==============================================================>>\033[0m\n");
}

void handler(int sig)
{
	pid_t pid;
    // char opopop[100000];
	int status;
	char *exit=(char *)malloc(1024*(sizeof(char)));
	char *exit_status=(char *)malloc(1024*(sizeof(char)));
	pid=waitpid(0,&status,WNOHANG);
    
	sprintf(exit,"\n[ %s ] with pid %d exited ",helper,pid);
	if(WIFEXITED(status))
	{
		int ab=WEXITSTATUS(status);
		if(ab==0)
			sprintf(exit_status, "normally\n");
		else
			sprintf(exit_status, "abnormally\n");
	}
	if(pid>0)
	{
		printf("%s%s",exit,exit_status);
        // getcwd(curdir,sizeof(curdir));
        // prompt_pathy();
	    // sprintf(dis, "<\033[1;32m%s\033[0m@\033[1;32m%s\033[0m:\033[1;34m%s\033[0m> ",user,host,dir);
        // fprintf(stdout,"%s",dis);
	}
	free(exit);
	return;
}
#include "pwd.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "cmd.h"
#include "redi.h"
#include "pinfo.h"
#include "added.h"
#include "history.h"
#include "nightwatch.h"

typedef long long int ll;

int main()
{
    system("clear");
    msg();
    prompt_init();
    signal(SIGCHLD, handler);
    while(1)
    {
        getcwd(curdir,sizeof(curdir));
        prompt_pathy();
        sprintf(dis, "<\033[1;32m%s\033[0m@\033[1;32m%s\033[0m:\033[1;34m%s\033[0m> ",user,host,dir);
        fprintf(stdout,"%s",dis);
        fflush(stdout);

        // strcpy(a," \0");
        fgets(a,sizeof(a),stdin);
        a[strlen(a)-1]='\0';
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
        while( pop<=ink ) 
        {
            ll pin=0;
            strcpy(amd,arc[pop]);
            amd[strlen(a)]='\0';
            while(amd[pin]==' ' ||amd[pin]=='\t' )
            pin++;

             fu_pipe=0;
                fu_redi=0;
                for(ll xi=0;xi<strlen(amd);xi++)
                {
                    if(amd[xi]=='|')
                    fu_pipe++;
                    if(amd[xi]=='<' || amd[xi]=='>')
                    fu_redi++;
                }


                if(fu_pipe!=0)
                {
                    // pipipip
                }
                else if(fu_redi!=0)
                {
                    callingredi(amd);
                    // printf("red off");
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