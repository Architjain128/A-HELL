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

    int status;
    pid_t pid;

    int pipefds[2*num_pipe];

    for(i = 0; i < (num_pipe); i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }

    int hi = 0;
    int j = 0;
    while(hi<=num_pipe) 
    {
        getcm(hi);
    signal(SIGCHLD, SIG_IGN);

        // printf("%d cmd copied\n",hi);
        pid = fork();
        if(pid<0)
        {
            perror("fork error");
        }
        else if(pid==0) 
        {
            if(hi<num_pipe){
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup21");
                    exit(EXIT_FAILURE);
                }
            }
            if( j!=0){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror(" dup22");
                    exit(EXIT_FAILURE);
                }
            }
            for(i = 0; i < 2*num_pipe; i++){
                    close(pipefds[i]);
            }

            if( execvp(runtask[0], runtask) < 0 ){
                    perror("oops");
                    exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }
        hi++;
        j+=2;
    }
    for(i = 0; i < 2 * num_pipe; i++){
        close(pipefds[i]);
    }
    for(i = 0; i <=num_pipe; i++)
        wait(&status);
    // printf("ALL Done");
}
   


