#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
extern int errno;
typedef long long int ll;

int stdin_fd ;
int stderr_fd ;
int stdout_fd;
char str[100000];
char *tasks[10000];
char *runtask[100];
char inp_file[10000];
char out_file[10000];
int out_type;

void getcm(ll a)
{
    ll i=0;
    ll j=0;
    ll temp_flag_inp=0;
    ll temp_flag_out=0;
    ll temp_flag_outappen=0;
    ll temp_flag_kick=0;
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

int main()
{
    fgets(str,sizeof(str),stdin);
    str[strlen(str)-1]='\0';
    
    stdin_fd = dup(STDIN_FILENO);
    stderr_fd = dup(STDERR_FILENO);
    stdout_fd = dup(STDOUT_FILENO);



    ll flag_pipe=0;

    ll i=0;
    const char pipdelimiters[] = "|";
    char *totken = strtok(str, pipdelimiters);
    while (totken != NULL)
    {
        tasks[i]=totken;
        // printf("%lld %s\n",i,tasks[i]);
        i++;
        totken = strtok(NULL, pipdelimiters);
    }
    ll num_flag_pipe=i;


    // for (ll j = 0; j <i; j++)
    // {
    //     getcm(j);
    //     ll x=0;
    //     while (runtask[x]!=NULL)
    //     {
    //         printf("[%s]+",runtask[x]);
    //         x++;
    //     }
    //     printf("\n");

    //     printf("input_file [%s]\n",inp_file);
    //     printf("output_file [%s]\n",out_file);
    //     printf("output_type [%d]\n",out_type);
    //     printf("\n");
      
    // }
    // int numpipfd[flag_pipe*2];
    //   for(i = 0; i < (flag_pipe); i++){
    //     if(pipe(numpipfd + i*2) < 0) {
    //         perror("couldn't pipe");
    //         exit(EXIT_FAILURE);
    //     }
    // }

    for (ll j = 0; j <num_flag_pipe; j++)
    {
        getcm(j);
        // ll x=0;
        // while (runtask[x]!=NULL)
        // {
        //     printf("[%s]+",runtask[x]);
        //     x++;
        // }
        // printf("\n");

        // printf("input_file [%s]\n",inp_file);
        // printf("output_file [%s]\n",out_file);
        // printf("output_type [%d]\n",out_type);
        // printf("\n");
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
            // if(strcmp(inp_file,"")!=0)
            // {
            //     int inp_fd = open(inp_file , O_RDONLY);
            //     if(inp_fd<0)
            //     {
            //         perror("input file");
            //     }
            //     else{
            //         if(dup2(inp_fd,STDIN_FILENO)<0)
            //         {
            //             perror("duplicate input fd");
            //         }    
            //     }
            // }
            // else
            // {
            //     if(j!=0){
            //     if(dup2(numpipfd[2*j-2],STDIN_FILENO)<0)
            //     {
            //         perror("duplicate input pipe fd");
            //     } 
            //     }  
            // }
            
            // if(strcmp(out_file,"")!=0 && out_type==1)
            // {
            //     int out_fd = open(out_file
            //      , O_WRONLY | O_CREAT | O_TRUNC, 0644);
            //     if(out_fd<0)
            //     {
            //         perror("output file");
            //     }
            //     else{
            //         if(dup2(out_fd,STDOUT_FILENO)<0)
            //         {
            //             perror("duplicate output fd");
            //         }    
            //     }
            // }
            //  else
            // {
            //     if(j!=(flag_pipe+1)){
            //     if(dup2(numpipfd[2*j+1],STDIN_FILENO)<0)
            //     {
            //         perror("duplicate output pipefd");
            //     } 
            //     }  
            // }
            // if(strcmp(out_file,"")!=0 && out_type==2)
            // {
            //     int out_fd = open(out_file ,  O_WRONLY | O_CREAT | O_APPEND , 0644);
            //     if(out_fd<0)
            //     {
            //         perror("output append file");
            //     }
            //     else{
            //         if(dup2(out_fd,STDOUT_FILENO)<0)
            //         {
            //             perror("duplicate output append fd");
            //         }    
            //     }
            // }
            //  else
            // {
            //     if(j!=flag_pipe+1){
            //     if(dup2(numpipfd[2*j+1],STDIN_FILENO)<0)
            //     {
            //         perror("duplicate output append pipe fd");
            //     } 
            //     }  
            // }

    

        pid_t pid;
		pid=fork(); 

		if(pid==-1)
		{
			perror("fork error : ");
			return 0;
		}
		else if(!pid)
		{
			if(execvp(runtask[0],runtask)<0)
			{
				perror("command not found");
				exit(EXIT_FAILURE);
			}
            // close(numpipfd[2*j+1]);
		} 
		else
		{
			wait(NULL);
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
    }
    

}

