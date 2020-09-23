#include "header.h"


void handler(int sig)
{
	pid_t pid;
	int st;
	char *exit=(char *)malloc(1024*(sizeof(char)));
	char *exit_status=(char *)malloc(1024*(sizeof(char)));
	pid=waitpid(-1,&st,WNOHANG);
	sprintf(exit,"\n[%s] with pid [%d] exited ",back_pro[pid],pid);
	if(WIFEXITED(st))
	{
		int ab=WEXITSTATUS(st);
		if(ab==0)
			sprintf(exit_status, "normally\n");
		else
			sprintf(exit_status, "abnormally\n");
	}
	if(pid>0)
	{
		printf("%s%s",exit,exit_status);
	}
	free(exit);
	return;
}

void callingcmd(char* str,int zip,char* str9)
{
    signal(SIGCHLD, handler);
    char cum[10000];
	ll bg=0;
    ll i=0;
    int st;
    char *inp[10000];
    char *temp2;
    temp2 = strtok(str, " \t");            
    strcpy(cum,"");

    while( temp2 != NULL ) 
    {
        if(strcmp(temp2,"&")==0)bg=1;
        
        if(strcmp(temp2,"&")!=0){
            inp[i]=temp2;
            strcat(cum,temp2);
            strcat(cum," ");
            i++;
        }
        temp2 = strtok(NULL, "  \t");
    }
    inp[i]=NULL;

if(bg==1)
{
    pid_t pid=fork();
    
    if (pid < 0) 
    {
        perror("ERROR:");
        return ;
    }
    if(pid==0)
    {
        if ( execvp(inp[0], inp) <0)
        {
            fprintf(stderr,"command: %s, not found\n",inp[0] );
            exit(0);
        }
    	
    }
    else
    {
        order[job_counter][0]=pid;
        strcpy(back_pro[order[job_counter][0]],cum);
        stat_pro[order[job_counter][0]] = 2;
        order[job_counter][1] = -1;
        job_counter++;
    }
    
}
else
{
    pid_t pid=fork();
    
    if (pid < 0) 
    {
        perror("ERROR:");
        return ;
    }
    if(pid==0)
    {
        if ( execvp(inp[0], inp) < 0)
        {
            fprintf(stderr,"command: %s, not found\n",inp[0] );
            exit(0);
        }
    	return ;
    }
    else
    {
        order[job_counter][0]=pid;
        strcpy(back_pro[order[job_counter][0]],cum);
        stat_pro[order[job_counter][0]] = 1;
        order[job_counter][1] = 1;
        job_counter++;
       waitpid(pid,&st,0);

    }
}

    // if(bg==0) 
    // {
    // 	cur_pid=pid;
    //  	bg_processes[pid]=helper;
    // 	// signal(SIGTSTP,zhandler);
    //     waitpid (pid, &st, WUNTRACED);
    // }
    // else
    // {
    // 	if(strcmp(inp[0],"vi")==0)	
    //     proc_status[pid]=2;
    // 	else 	
    //     proc_status[pid]=1;
    // 	bg_processes[pid]=inp[0];
    //     printf("%s %d\n",bg_processes[pid],pid);
    // }
    // int Rfork=fork();
    // if(bg==1)
    // {
    //    if(Rfork==0)
	// 	{
	// 		if(execvp(inp[0],inp)<0)
	// 		{
	// 			fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",helper);
	// 			exit(0);
	// 		}
	// 	}
    // }
    // else
    // {
    //     if(Rfork==0)
	// 	{
	// 		if(execvp(inp[0],inp)<0)
	// 		{
	// 			fprintf(stdout,"\033[1;31m--> ERROR : command not found [ %s ]\033[0m\n",helper);
	// 			exit(0);	
	// 		}
	// 	}
	// 	else
	// 	{
	// 		waitpid(Rfork,&status,0);
	// 	}
    // }
}