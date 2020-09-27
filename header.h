#ifndef HEADER_H
#define HEADER_H

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

char arc[1000][10000];
char a[10000000];
char dis[8000000];
char dir[1000000];
char execut[1000000];
char curdir[1000000];
char predir[1000000];
char amd[100000];
char host[100];
char user[100];
char *pidname;
char helper[1000];
int stdin_fd ;
int stderr_fd ;
int stdout_fd;
int job_counter;
int order[40000][2];
char back_pro[40000][1000];
int stat_pro[40000];
int exit_fail;
int cur_pid;
int inpp;
int oupp;
char *tasks[10000];
char *runtask[100];
char *extasks[10000];
char *exruntask[100];
int sym[10000];
int sym_exit[10000];
char inp_file[10000];
char out_file[10000];
char dd[10000];
int out_type;

#endif