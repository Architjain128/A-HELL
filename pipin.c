
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
int com_count;
char str[100000];

typedef struct Node
{
    ll flag_inp;
    ll flag_out;
    ll flag_outappen;
    char *runtask[100];
    char inp_file[10000];
    char out_file[10000];
    int out_type;
    ll temp_flag_inp;
    ll temp_flag_out;
    ll temp_flag_outappen;
    ll temp_flag_kick;
    struct Node* next;
}Node;


int main()
{
    fgets(str,sizeof(str),stdin);
    str[strlen(str)-1]='\0';
    stdin_fd = dup(STDIN_FILENO);
    stderr_fd = dup(STDERR_FILENO);
    stdout_fd = dup(STDOUT_FILENO);
    
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* cur = (struct Node*)malloc(sizeof(struct Node));
    struct Node* cur_dash = (struct Node*)malloc(sizeof(struct Node));
    cur->flag_inp=0;
    cur->flag_out=0;
    cur->flag_outappen=0;
    cur->temp_flag_inp=0;
    cur->temp_flag_out=0;
    cur->temp_flag_outappen=0;
    cur->temp_flag_kick=0;

    com_count = 1;

    const char delimiters[] = " \t\n\0";
    char *totken = strtok(str, delimiters);
    ll j=0;
    while (totken != NULL)
    {
        if(cur->temp_flag_outappen==1)
        {
            cur->out_type=2;
            cur->temp_flag_outappen=0;
            strcpy(cur->out_file,totken);
            cur->temp_flag_kick=1;
        }
        if(cur->temp_flag_out==1)
        {
            cur->out_type=1;
            cur->temp_flag_out=0;
            cur->temp_flag_kick=1;
            strcpy(cur->out_file,totken);
        }
        if(cur->temp_flag_inp==1)
        {
            cur->temp_flag_inp=0;
            cur->temp_flag_kick=1;
            strcpy(cur->inp_file,totken);
        }
        // strcpy(task[i],totken);

        if(strcmp(totken,"<")==0)
        {
            cur->temp_flag_inp=1;
            cur->flag_inp=1;
        }
        else if(strcmp(totken,">")==0)
        {
            cur->temp_flag_out=1;
            cur->flag_out=1;
        }
        else if(strcmp(totken,">>")==0)
        {
            cur->temp_flag_outappen=1;
            cur->flag_outappen=1;
        }
        else if(strcmp(totken,"|")==0)
        {
            cur->runtask[j]=NULL;
            j=0;
            if(com_count==1)
            {
                head=cur_dash;
            }
            else
            {
                cur_dash->next=cur;
                cur_dash=cur;
            }
            com_count++;
            free(cur);
            struct Node* cur = (struct Node*)malloc(sizeof(struct Node));
            cur->flag_inp=0;
            cur->flag_out=0;
            cur->flag_outappen=0;
            cur->temp_flag_inp=0;
            cur->temp_flag_out=0;
            cur->temp_flag_outappen=0;
            cur->temp_flag_kick=0;
        }
        else{
            if(cur->temp_flag_kick!=1){
                fprintf(stderr,"%d %lld %s\n",com_count,j,totken);
                strcpy(cur->runtask[j],totken);
                j++;
            }
        }
        totken = strtok(NULL, delimiters);
    }
    if(com_count==1)
    {
        head=cur;
        cur_dash=head;
    }
    else
    {
        cur_dash->next=cur;
        cur_dash=cur;
    }
    free(cur);


    // printing
    struct Node* oof = head;
printf("%d\n",com_count);
    while (com_count--)
    {
        ll p=0;
        while(oof->runtask[p]!=NULL){
        printf("[%s]+",oof->runtask[p]);
        p++;
        }
        printf("\n");
        printf("input_file [%s]\n",oof->inp_file);
        printf("output_file [%s]\n",oof->out_file);
        printf("output_type [%d]\n",oof->out_type);
        printf("\n");
            oof=oof->next;
    }
    


    

}