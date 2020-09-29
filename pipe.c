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
void callingredi_num();

void getcm(ll a)
{
    ll j=0;
    inpp=0;
    oupp=0;
    ll temp_flag_inp=0;
    ll temp_flag_out=0;
    ll temp_flag_outappen=0;
    ll temp_kick=0;
    strcpy(restr,"");
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
            inpp=1;
            temp_flag_inp=1;
            temp_kick=1;
        }
        else if(strcmp(totken,">")==0)
        {
            oupp=1;
            temp_flag_out=1;
            temp_kick=1;
        }
        else if(strcmp(totken,">>")==0)
        {
            oupp=1;
            temp_flag_outappen=1;
            temp_kick=1;
        }
        else{
            if(temp_kick==0)
            {
                runtask[j]=totken;
                strcat(restr,totken);
                strcat(restr," ");
                j++;
            }
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
        exit_fail=1;

            exit(EXIT_FAILURE);
        }
    }

    int hi = 0;
    int j = 0;
    while(hi<=num_pipe) 
    {
        getcm(hi);
        strcpy(restr,"");
        ll x=0;
        while (runtask[x]!=NULL)
        {
            // printf("[%s]+",runtask[x]);
            strcat(restr,runtask[x]);
            strcat(restr," ");
            x++;
        }

        if(strlen(inp_file)!=0)
        {
            strcat(restr,"< ");
            strcat(restr,inp_file);
            // printf("input_file [%s]\n",inp_file);
        }
         if(strlen(out_file)!=0)
        {
            if(out_type==1)
            {
                strcat(restr,"> ");
            strcat(restr,out_file);
            // printf("input_file [%s]\n",inp_file);
            }
            if(out_type==2)
            {
                strcat(restr,">> ");
                strcat(restr,out_file);
            }
        }
        // printf("\n\n[%s]\n\n",restr);
        // printf("output_file [%s]\n",out_file);
        // printf("output_type [%d]\n",out_type);
        // printf("\n");   
    
        signal(SIGCHLD, SIG_IGN);

        pid = fork();
        if(pid<0)
        {
            perror("fork error");
            exit_fail=1;

        }
        else if(pid==0) 
        {
            if(hi<num_pipe)
            {
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup21");
                    exit_fail=1;
                    // exit(EXIT_FAILURE);
                }
            } 
            if( j!=0)
            {
                if(dup2(pipefds[j-2], 0) < 0){
                    perror(" dup22");
                    exit_fail=1;
                    // exit(EXIT_FAILURE);
                }
            }
           
            

            for(i = 0; i < 2*num_pipe; i++){
                    close(pipefds[i]);
            }



            if(inpp>0 || oupp>0)
            {
                callingredi_num();
            }
            else
            {
                // fprintf(stderr,"[%s]",runtask[0]);
                // if(strcmp(runtask[0],"pwd")==0)
                // {
                //     callingpwd();
                // }
                // else if(strcmp(runtask[0],"cd")==0)
                // {
                //     callingcd(restr,0,execut);
                // }
                // else if(strcmp(runtask[0],"echo")==0)
                // {
                //     callingecho(str,0,execut);
                // }
                // else if(strcmp(runtask[0],"ls")==0)
                // {
                //     callingls(restr,0,execut);
                // }
                // else if(strcmp(runtask[0],"pinfo")==0)
                // {
                //     callingpinfo(restr,0,execut);
                // }
                // else if(strcmp(runtask[0],"history")==0)
                // {
                //     callinghistory(restr,0,execut);
                // }
                // else if(strcmp(runtask[0],"nightswatch")==0)
                // {
                //     nightwatch(restr,execut);
                // }
                // else if(strcmp(runtask[0],"setenv")==0)
                // {
                //     callingsetenv(restr);
                // }
                // else if(strcmp(runtask[0],"unsetenv")==0)
                // {
                //     callingunsetenv(restr);
                // }
                // else if(strcmp(runtask[0],"jobs")==0)
                // {
                //     callingjobs();
                // }
                // else if(strcmp(runtask[0],"kjob")==0)
                // {
                //     callingkjob(restr);
                // }
                // else if(strcmp(runtask[0],"overkill")==0)
                // {
                //     callingoverkill();
                // }
                // else if(strcmp(runtask[0],"fg")==0)
                // {
                //     callingfg(restr);
                // }
                // else if(strcmp(runtask[0],"bg")==0)
                // {
                //     callingbg(restr);
                // }
                // else if(strcmp(runtask[0],"exit")==0 || strcmp(runtask[0],"quit")==0)
                // {
                //     exitmsg();
                //         exit(0); 
                // }
                // else
                // {
                //     callingcmd(restr,0,execut);
                // }
                if( execvp(runtask[0], runtask) < 0 )
                {
                    perror("oops");
                    exit_fail=1;
                    // exit(EXIT_FAILURE);
                }
            }
            return;         
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
   


