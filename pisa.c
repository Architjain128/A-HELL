#include "header.h"

char *tasks[10000];
char *runtask[100];
char inp_file[10000];
char out_file[10000];
int out_type;
ll ret=0;
void execute_process(int input, int output){
	pid_t pid = fork();
	if(pid < 0){
		fprintf(stderr,"Child process could not be created\n");
		ret= 0;
	}
	else if(pid==0)
	{
		if(input!=0) close(0);
		if(output!=1) close(1);
		dup2(input,0); dup2(output, 1); // set the inp/op sources accordingly
		if (execvp(runtask[0], runtask)<0)
		{
            perror("command not found");
			exit(0);
		}	
	}
	else{
		wait(NULL);
		ret= 1;
	}
}

int redor(int input, int output)
{
    //one complete command without any pipes
    char output_file1[1000], output_file2[1000], input_file[1000];
    int indirec = 0, outdirec = 0, outappend = 0; //flags for checking
    int i = -1;

    while (runtask[++i])
    {
        if (strcmp(runtask[i], "<") == 0)
        {
            if(!runtask[i+1]) {
                fprintf(stderr, "mysh: syntax error: Invalid usage of pipes or redirection\n");
                return 1;
            }
            runtask[i] = NULL;
            // stdin should become runtask[i+1]
            strcpy(input_file, runtask[i+1]);
            indirec = 1;
        }
        else if (strcmp(runtask[i], ">") == 0)
        {
            if(!runtask[i+1]) {
                fprintf(stderr, "mysh: syntax error: Invalid usage of pipes or redirection\n");
                return 1;
            }
            runtask[i] = NULL;
            // stdout should become runtask[i+1]
            strcpy(output_file1, runtask[i + 1]);
            outdirec = 1;
        }
        else if (strcmp(runtask[i], ">>") == 0)
        {
            if(!runtask[i+1]) {
                fprintf(stderr, "mysh: syntax error: Invalid usage of pipes or redirection\n");
                return 1;
            }
            runtask[i] = NULL;
            //stdout should become runtask[i+1] and append to file
            strcpy(output_file2, runtask[i+1]);
            outappend = 1;
        }
        // runtask[i] = args[i];
    }

    int fd_inp=input, fd_op=output;
    if (indirec){
        fd_inp = open(input_file, O_RDONLY, 0);
        if (fd_inp < 0){
            perror("Could not open input file");
            return 1;
        }
    }
    if (outdirec)
    {
        fd_op = open(output_file1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_op < 0){
            perror("Could not open output file");
            return 1;
        }
    }
    else if (outappend)
    {
        fd_op = open(output_file2, O_APPEND | O_WRONLY | O_CREAT, 0644);
        if (fd_op < 0){
            perror("Could not open output file");
            return 1;
        }
    }

    int ret = 0;
    // it's not a builtin process so execute via execvp
        execute_process(fd_inp,fd_op);
    if(ret==0) return 0;
    return 1;
}


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



void callingpiponly2(char *str)
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
    ll tot_com = i;

    int fd[2];
    i=-1;
    ll fd_in=0,com_done=0;
    for (ll j = 0; j < tot_com; j++)
    {
        ret=0;
        if(pipe(fd)<0)
        {
            perror("piping");
            exit(EXIT_FAILURE);
        }
        if(j==0)
        {
            ret = redor(fd_in,fd[1]);
        }
        else if(j==tot_com-1)
        {
            ret = redor(fd_in,stdout_fd);
        }
        else
        {
            ret = 0;
		    execute_process(fd_in,fd[1]);
        }
        	if(ret==0) return ;
			close(fd[1]);
      		fd_in = fd[0];
    }
}