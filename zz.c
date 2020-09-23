#include "header.h"





char *tasks[10000];
char *runtask[100];
char inp_file[10000];
char out_file[10000];
int out_type;
char str[10000000];

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




int main()
{
	int stdinfd;
	int stdoutfd;
	dup2(STDOUT_FILENO,stdoutfd);
	dup2(STDIN_FILENO,stdinfd);
	fgets(str,sizeof(str),stdin);
    str[strlen(str)-1]='\0';
	int i=0;
    const char pipdelimiters[] = "|";
    char *totken = strtok(str, pipdelimiters);
    while (totken != NULL)
    {
        tasks[i]=totken;
        i++;
        totken = strtok(NULL, pipdelimiters);
    }
    ll num_pipes=i-1;
	ll pipefds[num_pipes*2];
	for( int i = 0; i < num_pipes; i++ ){
		if( pipe(pipefds + i*2) < 0 ){
			perror("pipe");
			exit(0);
		}
	}

	ll commandc = 0;
	for(ll j=0;j<=num_pipes;j++){
		getcm(j);
		pid_t pid = fork();
		if( pid == 0 ){
			/* child gets input from the previous command,
				if it's not the first command */
			if( j!=0 )
			{
				if( dup2(pipefds[(commandc-1)*2], STDIN_FILENO) < 0)
				{
					perror("pop");
					exit(0);
				}
			}
			/* child outputs to next command, if it's not
				the last command */
			if( j!=num_pipes ){
				if( dup2(pipefds[commandc*2+1], STDOUT_FILENO) < 0 ){
					perror("pop");
					exit(0);
				}
			}
 			for(i = 0; i < 2*num_pipes; i++){
                    close(pipefds[i]);
            }

            if( execvp(runtask[0], runtask) < 0 ){
                    perror("cmd");
                    exit(EXIT_FAILURE);
            }
		
		}
		 else if( pid < 0 ){
			perror("kb");
		}
		
		commandc++;
	}

/* parent closes all of its copies at the end */
	for( i = 0; i < 2 * num_pipes; i++ ){
		close( pipefds[i] );
}
}