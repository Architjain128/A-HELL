#include "header.h"
void callingpwd();
void callingcd(char *str,int zip, char *str1);
void callingecho(char *str,int zip, char *str1);
void callingls(char *str,int zip, char *str1);
void callingpinfo(char *str,int zip, char *str1);
void callinghistory(char *str,int zip, char *str1);
void callingcmd(char *str,int zip, char *str1);
void nightwatch(char *str, char *str1);
void callingsetenv(char *str);
void callingunsetenv(char *str);
void callingfg(char *str);
void callingbg(char *str);
void callingjobs();
void callingoverkill();
void callingkjob(char *str);
void exitmsg();


void callingredi(char *str)
{
    ll flag_inp=0;
    ll flag_out=0;
    ll flag_outappen=0;
    int inp_fd; 
    int out_fd; 
    for(ll i=0;i<strlen(str);i++)
    {
        // if(str[i]=='|')flag_pipe++;
        if(str[i]=='<')flag_inp=1;
        if(str[i]=='>'){
            if(i+1<strlen(str) && str[i+1]=='>'){
                flag_outappen=1;
            }
            else if(i-1<strlen(str) && str[i-1]!='>') {
                flag_out = 1;
            }
        }
    }


        ll i=0;
        ll j=0;
        char *reruntask[100];
        char inp_file[1000];
        char out_file[1000];
        int out_type;
        ll temp_flag_inp=0;
        ll temp_flag_out=0;
        ll temp_flag_outappen=0;
        ll temp_flag_kick=0;
        strcpy(restr,"");
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
                reruntask[j]=totken;
                strcat(restr,totken);
                strcat(restr," ");
                j++;
                }
            }
            i++;
            // printf("tooken  %lld: [%s]\n", i, totken);
            totken = strtok(NULL, delimiters);
        }
        reruntask[j]=NULL;


        if(flag_inp==1)
        {
            inp_fd = open(inp_file , O_RDONLY);
            if(inp_fd<0)
            {
                perror("input file");
        exit_fail=1;

                printf("\033[0;33m--> WARNING : input file [%s] not exist, enter data in STDIN mode  \033[0m\n",inp_file);
                flag_inp=0;
            }
            else{
                if(dup2(inp_fd,STDIN_FILENO)<0)
                {
                    perror("duplicate input fd");
        exit_fail=1;

                exit(0);

                }    
            }
        }
        if(flag_out==1 && out_type==1)
        {
            out_fd = open(out_file , O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(out_fd<0)
            {
                perror("output file");
        exit_fail=1;

                exit(0);

            }
            else{
                if(dup2(out_fd,STDOUT_FILENO)<0)
                {
                    perror("duplicate output fd");
        exit_fail=1;

                exit(0);

                }    
            }
        }
        if( flag_outappen==1 && out_type==2)
        {
            out_fd = open(out_file ,  O_WRONLY | O_CREAT | O_APPEND , 0644);
            if(out_fd<0)
            {
                perror("output append file");
        exit_fail=1;

                exit(0);

            }
            else{
                if(dup2(out_fd,STDOUT_FILENO)<0)
                {
                    perror("duplicate output append fd");
        exit_fail=1;

                exit(0);

                }    
            }
        }

        pid_t pid;
        pid=fork();
        if(pid<0)
        {
            close(out_fd);
            perror("forking");
            exit_fail=1;

                exit(0);

        }
        else if(pid==0)
        {
            if(strcmp(reruntask[0],"pwd")==0)
            {
                callingpwd();
            }
            else if(strcmp(reruntask[0],"cd")==0)
            {
                callingcd(restr,0,execut);
            }
            else if(strcmp(reruntask[0],"echo")==0)
            {
                callingecho(restr,0,execut);
            }
            else if(strcmp(reruntask[0],"ls")==0)
            {
                callingls(restr,0,execut);
            }
            else if(strcmp(reruntask[0],"pinfo")==0)
            {
                callingpinfo(restr,0,execut);
            }
            else if(strcmp(reruntask[0],"history")==0)
            {
                callinghistory(restr,0,execut);
            }
            else if(strcmp(reruntask[0],"nightswatch")==0)
            {
                nightwatch(restr,execut);
            }
            else if(strcmp(reruntask[0],"setenv")==0)
            {
                callingsetenv(restr);
            }
            else if(strcmp(reruntask[0],"unsetenv")==0)
            {
                callingunsetenv(restr);
            }
            else if(strcmp(reruntask[0],"jobs")==0)
            {
                callingjobs();
            }
            else if(strcmp(reruntask[0],"kjob")==0)
            {
                callingkjob(restr);
            }
            else if(strcmp(reruntask[0],"overkill")==0)
            {
                callingoverkill();
            }
            else if(strcmp(reruntask[0],"fg")==0)
            {
                callingfg(restr);
            }
            else if(strcmp(reruntask[0],"bg")==0)
            {
                callingbg(restr);
            }
            else if(strcmp(reruntask[0],"exit")==0 || strcmp(reruntask[0],"quit")==0)
            {
                  exitmsg();
                    exit(0); 
            }
            else
            {
                callingcmd(restr,0,execut);
            }
            
            // else if (execvp(reruntask[0],reruntask)<0)
            // {
            //     perror("command not found");
            //     exit_fail=1;
            //     exit(0);
            // }
            
            exit(0);
        }
        else
        {
            // wait(NULL);
            if(dup2(stdout_fd,STDOUT_FILENO)<0)
            {
                perror("reassign sdtout");
                exit_fail=1;
            }
            if(dup2(stdin_fd,STDIN_FILENO)<0)
            {
                perror("reassign STDIN_FILENO");
                exit_fail=1;
            } 
        }    
        return;
}