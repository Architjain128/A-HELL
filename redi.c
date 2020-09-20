
// #include <stdio.h>
// #include <math.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <sys/stat.h>
// #include <sys/time.h>
// #include <sys/types.h>
// #include <sys/select.h>
// #include <dirent.h>
// #include <string.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <pwd.h>
// #include <grp.h>
// #include <time.h>
// #include <errno.h>
// extern int errno;
// typedef long long int ll;

// int stdin_fd ;
// int stderr_fd ;
// int stdout_fd;
#include "header.h"
void callingredi(char *str)
{
    
    stdin_fd = dup(STDIN_FILENO);
    stderr_fd = dup(STDERR_FILENO);
    stdout_fd = dup(STDOUT_FILENO);

    // ll flag_pipe=0;
    ll flag_inp=0;
    // ll flag_out=0;
    // ll flag_outappen=0;


    // for(ll i=0;i<strlen(str);i++)
    // {
    //     if(str[i]=='|')flag_pipe++;
    //     if(str[i]=='<')flag_inp=1;
    //     if(str[i]=='>'){
    //         if(i+1<strlen(str) && str[i+1]=='>'){
    //             flag_outappen=1;
    //         }
    //         else if(i-1<strlen(str) && str[i-1]!='>') {
    //             flag_out = 1;
    //         }
    //     }
    // }


    // if(flag_pipe==0)
    // {


        ll i=0;
        ll j=0;
        // char task[100][10000];
        char *runtask[100];
        char inp_file[1000];
        char out_file[1000];
        int out_type;
        ll temp_flag_inp=0;
        ll temp_flag_out=0;
        ll temp_flag_outappen=0;
        ll temp_flag_kick=0;
        const char delimiters[] = " \t\n\0";
        char *totken = strtok(str, delimiters);
        while (totken != NULL)
        {
            if(temp_flag_outappen==1)
            {
                out_type=2;
                temp_flag_outappen=0;
                strcpy(out_file,totken);
                temp_flag_kick=1;
            }
            if(temp_flag_out==1)
            {
                out_type=1;
                temp_flag_out=0;
                temp_flag_kick=1;
                strcpy(out_file,totken);
            }
            if(temp_flag_inp==1)
            {
                temp_flag_inp=0;
                temp_flag_kick=1;
                strcpy(inp_file,totken);
            }
            // strcpy(task[i],totken);

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
                if(temp_flag_kick!=1){
                runtask[j]=totken;
                j++;
                }
            }

          

            i++;
            // printf("tooken  %lld: [%s]\n", i, totken);
            totken = strtok(NULL, delimiters);
        }


        if(flag_inp==1)
        {
            int inp_fd = open(inp_file , O_RDONLY);
            if(inp_fd<0)
            {
                perror("input file");
            }
            else{
                if(dup2(inp_fd,STDIN_FILENO)<0)
                {
                    perror("duplicate input fd");

                }    
            }
        }
        if(out_type==1)
        {
            int out_fd = open(out_file , O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(out_fd<0)
            {
                perror("output file");
            }
            else{
                if(dup2(out_fd,STDOUT_FILENO)<0)
                {
                    perror("duplicate output fd");
                }    
            }
        }
        if( out_type==2)
        {
            int out_fd = open(out_file ,  O_WRONLY | O_CREAT | O_APPEND , 0644);
            if(out_fd<0)
            {
                perror("output append file");
            }
            else{
                if(dup2(out_fd,STDOUT_FILENO)<0)
                {
                    perror("duplicate output append fd");
                }    
            }
        }

        if(execvp(runtask[0],runtask)<0)
        {
            perror("command not found");
        }

        if(dup2(STDOUT_FILENO,stdout_fd)<0)
        {
            perror("reassign sdtout");
        }
        if(dup2(STDIN_FILENO,stdin_fd)<0)
        {
            perror("reassign STDIN_FILENO");
        } 
        if(dup2(STDERR_FILENO,stderr_fd)<0)
        {
            perror("reassign STDERR_FILENO");
        }   
    
}