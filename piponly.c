#include "header.h"

char *tasks[10000];
char *runtask[100];
char inp_file[10000];
char out_file[10000];
int out_type;

void getcm(ll a)
{
    ll j=0;
    ll temp_flag_inp=0;
    ll temp_flag_out=0;
    ll temp_flag_outappen=0;
    strcpy(inp_file,"");
    strcpy(out_file,"");
    out_type=0;
    const char delimiters[] = " \t\n\0";
    char *totken = strtok(tasks[a], delimiters);
    while (totken != NULL)
    {
        if(temp_flag_outappen==1)
        {
            out_type=2;
            temp_flag_outappen=0;
            strcpy(out_file,totken);
        }
        if(temp_flag_out==1)
        {
            out_type=1;
            temp_flag_out=0;
            strcpy(out_file,totken);
        }
        if(temp_flag_inp==1)
        {
            temp_flag_inp=0;
            strcpy(inp_file,totken);
        }

        if(strcmp(totken,"<")==0)
        {
            temp_flag_inp=1;
        }
        else if(strcmp(totken,">")==0)
        {
            temp_flag_out=1;
        }
        else if(strcmp(totken,">>")==0)
        {
            temp_flag_outappen=1;
        }
        else{
            runtask[j]=totken;
            j++;
        }

        totken = strtok(NULL, delimiters);
    }
    runtask[j]=NULL;
}

void callingpiponly(char *str)
{

    // dup2(STDOUT_FILENO,stdout_fd);
    // dup2(STDIN_FILENO,stdin_fd);
// printf("%d%d",stdin_fd,stdout_fd);

    ll i=0;
    const char pipdelimiters[] = "|";
    char *totken = strtok(str, pipdelimiters);
    while (totken != NULL)
    {
        tasks[i]=totken;
        i++;
        totken = strtok(NULL, pipdelimiters);
    }
    ll num_pipe=i-1;

    // // for (ll j = 0; j <i; j++)
    // // {
    // //     getcm(j);
    // //     ll x=0;
    // //     while (runtask[x]!=NULL)
    // //     {
    // //         printf("[%s]+",runtask[x]);
    // //         x++;
    // //     }
    // //     printf("\n");
    // //     printf("input_file [%s]\n",inp_file);
    // //     printf("output_file [%s]\n",out_file);
    // //     printf("output_type [%d]\n",out_type);
    // //     printf("\n");   
    // // }
    // int numpipfd[num_pipe*2];
    // for(i = 0; i < num_pipe; i++){
    //     if(pipe(numpipfd + i*2) < 0) {
    //         perror("couldn't pipe");
    //     }
    // }
int cdread;
int fdread;
int cdwrite;

    for (ll j = 0; j <=num_pipe; j++)
    {
        getcm(j);
        int fildes[2];
        if(j!=num_pipe){
        if (pipe(fildes) < 0) {
            perror("Could not create pipe.");
            exit(1);
        }
        }

        // setting reding for j
        if(j==0)
        {
            if(dup2(stdin_fd,cdread)<0)
            {
                perror("current reading duplication");
                // exit(0);
            }
            // printf("%d %d\n",stdin_fd,cdread);
        }
        else
        {
            if(dup2(fdread,cdread)<0)
            {
                perror("current reading duplication");
                exit(0);
            }
        }
        

        // setting reding for j+1
        if(j==num_pipe)
        {
            // dup2(,fdread);
        }
        else
        {
            if(dup2(fildes[0],fdread)<0)
            {
                perror("next reading duplication");
                exit(0);
            }
            // printf("%d ",fildes[0]);
        }

        // setting wriring for j
        if(j==num_pipe)
        {
            if(dup2(stdout_fd,cdwrite)<0)
            {
                perror("current writing duplication");
                exit(0);
            }
        }
        else
        {
            if(dup2(fildes[1],cdwrite)<0)
            {
                perror("current writing duplication");
                exit(0);
            }
            // printf("%d ",fildes[1]);
        }

    int pid = fork();

    if (pid < 0) {
        perror("Could not create child.");
        exit(0);
    } 
    else if (pid == 0) 
    {
        dup2(cdwrite,STDOUT_FILENO);
        dup2(cdread,STDIN_FILENO);
        if(execvp(runtask[0],runtask)<0)
        {
            perror("command not found");
            exit(0);
        }
        close(cdread);
    }
    else
    {
       wait(NULL);
       if(j!=num_pipe)
        close(fildes[0]);
       
    }
            
       if(j!=num_pipe)
        close(fildes[1]);

        // if(j!=num_pipe){
        //     if(pipe(fd)<0)
        //     {
        //         perror("couldn't pipe");
        //         exit(0);
        //     }
        // }
        //     if(j!=0)
        //     {
        //         if(dup2(fdread,STDIN_FILENO)<0)
        //         {
        //             perror("duplicate input fd");
        //             printf("%d",j);
        //             exit(0);
        //         } 
        //     }
        //     if(j!=num_pipe)
        //     {
        //         if(dup2(fd[1],STDOUT_FILENO)<0)
        //         {
        //             perror("duplicate output fd");
        //             printf("%d",j);
        //             exit(0);
        //         } 
        //         fdread=dup(fd[0]);
        //     }
        // pid_t pid;
		// pid=fork(); 
		// if(pid==-1)
		// {
		// 	perror("fork error : ");
		// 	exit(0);
		// }
		// else if(!pid)
		// {
        //     // close(fd[0]);
		// 	if(execvp(runtask[0],runtask)<0)
		// 	{
		// 		perror("command not found");
		// 		exit(0);
		// 	}
        //     close(fd[1]);
        //     exit(0);
		// } 
		// else
		// {
		// 	wait(NULL);
        //     if(dup2(STDOUT_FILENO,stdout_fd)<0)
        //     {
        //         perror("reassign sdtout");
        //     }
        //     if(dup2(STDIN_FILENO,stdin_fd)<0)
        //     {
        //         perror("reassign STDIN_FILENO");
        //     } 
        //     if(dup2(STDERR_FILENO,stderr_fd)<0)
        //     {
        //         perror("reassign STDERR_FILENO");
        //     }
		// }      
    }
    if(dup2(stdin_fd,STDIN_FILENO)<0)
    {
        perror("reassigning stdin");
        exit(0);
    }
    if(dup2(stdout_fd,STDOUT_FILENO)<0)
    {
        perror("reassigning stdout");
        exit(0);
    }
}

