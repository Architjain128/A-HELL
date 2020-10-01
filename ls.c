#include "header.h"

void callingls(char *str,int zip,char *str1)
{
    ll fh = 0;
    ll fa = 0;
    ll fl = 0;
    ll fal = 0;
    char date_str[250];
    char inp[100][10000];
    char *temp=(char *)malloc(100000*sizeof(char));
    temp[0]='.';

    char *temp2=(char *)malloc(100000*sizeof(char));
    temp2 = strtok(str, " \t");
    ll i=0;
    while( temp2 != NULL ) 
    {
        fh=0;
        if(strcmp(temp2,"-a")==0)fa=1;
        if(strcmp(temp2,"-l")==0)fl=1;
        if(strcmp(temp2,"~")==0)fh=1;
        if(strcmp(temp2,"-al")==0 || strcmp(temp2,"-la")==0)fal=1;
        if(strcmp(temp2,"ls")!=0 && strcmp(temp2,"-a")!=0 && strcmp(temp2,"-l")!=0 && strcmp(temp2,"-al")!=0 && strcmp(temp2,"~")!=0 && strcmp(temp2,"-la")!=0 ){
            if(fh==1)
            strcpy(inp[i],str1);
            else
            strcpy(inp[i],temp2);
            i++;
        }
        temp2 = strtok(NULL, "  \t");
    }
    
    if(i==0){
        strcpy(temp,".");
        struct stat s;
        DIR *Ddir ;
        Ddir = opendir(temp);
        struct dirent *Di;
        if(Ddir==NULL)
        {
		    fprintf(stdout,"\033[1;31m--> ERROR :cannot read directory [ %s ]\033[0m\n",temp);
        exit_fail=1;

            return;
        }
            while((Di=readdir(Ddir))!=NULL)
            {

                if(fal==1|| (fa==1 && fl==1))
                {
                    stat(Di->d_name,&s);
                    printf((s.st_mode & __S_IFDIR)? "d":"-");
                    printf((s.st_mode & S_IRUSR)? "r":"-");
                    printf((s.st_mode & S_IWUSR)? "w":"-");
                    printf((s.st_mode & S_IXUSR)? "x":"-");
                    printf((s.st_mode & S_IRGRP)? "r":"-");
                    printf((s.st_mode & S_IWGRP)? "w":"-");
                    printf((s.st_mode & S_IXGRP)? "x":"-");
                    printf((s.st_mode & S_IROTH)? "r":"-");
                    printf((s.st_mode & S_IWOTH)? "w":"-");
                    printf((s.st_mode & S_IXOTH)? "x":"-");
                    printf(" ");
                    printf("%5lld",(long long int)s.st_nlink);
                    printf(" ");
                    struct passwd *pw = getpwuid(s.st_uid);
                    struct group *gr = getgrgid(s.st_gid);
                    printf("%s %s ",pw->pw_name,gr->gr_name);
                    printf("%5ld ",s.st_size );
                    sprintf(date_str,"%s",ctime(&s.st_ctime));
                    date_str[7]='\0';
                    date_str[10]='\0';
                    date_str[16]='\0';
                    printf("%s ",date_str +4);
                    printf("%s ",date_str +8 );
                    printf("%s ",date_str +11 );
                    printf("%s\n",Di->d_name);
                
                }
                else if(fl==1 && fa==0)
                {
                    if(Di->d_name[0]!='.')
                    {
                        stat(Di->d_name,&s);
                        printf((s.st_mode & __S_IFDIR)? "d":"-");
                        printf((s.st_mode & S_IRUSR)? "r":"-");
                        printf((s.st_mode & S_IWUSR)? "w":"-");
                        printf((s.st_mode & S_IXUSR)? "x":"-");
                        printf((s.st_mode & S_IRGRP)? "r":"-");
                        printf((s.st_mode & S_IWGRP)? "w":"-");
                        printf((s.st_mode & S_IXGRP)? "x":"-");
                        printf((s.st_mode & S_IROTH)? "r":"-");
                        printf((s.st_mode & S_IWOTH)? "w":"-");
                        printf((s.st_mode & S_IXOTH)? "x":"-");
                        printf(" ");
                        printf("%5lld",(long long int)s.st_nlink);
                        printf(" ");
                        struct passwd *pw = getpwuid(s.st_uid);
                        struct group *gr = getgrgid(s.st_gid);
                        printf("%s %s ",pw->pw_name,gr->gr_name);
                        printf("%5ld ",s.st_size );
                        sprintf(date_str,"%s",ctime(&s.st_ctime));
                        date_str[7]='\0';
                        date_str[10]='\0';
                        date_str[16]='\0';
                        printf("%s ",date_str +4);
                        printf("%s ",date_str +8 );
                        printf("%s ",date_str +11 );
                        printf("%s\n",Di->d_name);
                    }
                }
                else{
                    if(fa==1 && fl==0)
                    printf("%s\n",Di->d_name); 
                    else if(fa==0 && fl==0 && fal==0) {
                    if(Di->d_name[0]!='.')
                    printf("%s\n",Di->d_name); 
                    }
                }
            }
    }
    if(i==1)
    {
        strcpy(temp,inp[0]);
        struct stat s;
        DIR *Ddir ;
        Ddir = opendir(temp);
        struct dirent *Di;
        if(Ddir==NULL)
        {
            fprintf(stdout,"\033[1;31m--> ERROR :cannot read directory [ %s ]\033[0m\n",temp);
        exit_fail=1;

            return;
        }
            while((Di=readdir(Ddir))!=NULL)
            {

                 if(fal==1|| (fa==1 && fl==1))
                {
                    stat(Di->d_name,&s);
                    printf((s.st_mode & __S_IFDIR)? "d":"-");
                    printf((s.st_mode & S_IRUSR)? "r":"-");
                    printf((s.st_mode & S_IWUSR)? "w":"-");
                    printf((s.st_mode & S_IXUSR)? "x":"-");
                    printf((s.st_mode & S_IRGRP)? "r":"-");
                    printf((s.st_mode & S_IWGRP)? "w":"-");
                    printf((s.st_mode & S_IXGRP)? "x":"-");
                    printf((s.st_mode & S_IROTH)? "r":"-");
                    printf((s.st_mode & S_IWOTH)? "w":"-");
                    printf((s.st_mode & S_IXOTH)? "x":"-");
                    printf(" ");
                    printf("%5lld",(long long int)s.st_nlink);
                    printf(" ");
                    struct passwd *pw = getpwuid(s.st_uid);
                    struct group *gr = getgrgid(s.st_gid);
                    printf("%s %s ",pw->pw_name,gr->gr_name);
                    printf("%5ld ",s.st_size );
                     sprintf(date_str,"%s",ctime(&s.st_ctime));
                    date_str[7]='\0';
                    date_str[10]='\0';
                    date_str[16]='\0';
                    printf("%s ",date_str +4);
                    printf("%s ",date_str +8 );
                    printf("%s ",date_str +11 );
                    printf("%s\n",Di->d_name);
                
                }
                else if(fl==1 && fa==0)
                {
                    if(Di->d_name[0]!='.')
                    {
                        stat(Di->d_name,&s);
                        printf((s.st_mode & __S_IFDIR)? "d":"-");
                        printf((s.st_mode & S_IRUSR)? "r":"-");
                        printf((s.st_mode & S_IWUSR)? "w":"-");
                        printf((s.st_mode & S_IXUSR)? "x":"-");
                        printf((s.st_mode & S_IRGRP)? "r":"-");
                        printf((s.st_mode & S_IWGRP)? "w":"-");
                        printf((s.st_mode & S_IXGRP)? "x":"-");
                        printf((s.st_mode & S_IROTH)? "r":"-");
                        printf((s.st_mode & S_IWOTH)? "w":"-");
                        printf((s.st_mode & S_IXOTH)? "x":"-");
                        printf(" ");
                        printf("%5lld",(long long int)s.st_nlink);
                        printf(" ");
                        struct passwd *pw = getpwuid(s.st_uid);
                        struct group *gr = getgrgid(s.st_gid);
                        printf("%s %s ",pw->pw_name,gr->gr_name);
                        printf("%5ld ",s.st_size );
                        sprintf(date_str,"%s",ctime(&s.st_ctime));
                        date_str[7]='\0';
                        date_str[10]='\0';
                        date_str[16]='\0';
                        printf("%s ",date_str +4);
                        printf("%s ",date_str +8 );
                        printf("%s ",date_str +11 );
                        printf("%s\n",Di->d_name);
                    
                    }
                }
                else{
                    if(fa==1 && fl==0)
                    printf("%s\n",Di->d_name); 
                    else if(fal==0 && fa==0 && fl==0){
                    if(Di->d_name[0]!='.')
                    printf("%s\n",Di->d_name); 
                    }
                }
            }
    }
    else
    {
        while(i--)
        {
            strcpy(temp,inp[i]);
            struct stat s;
            DIR *Ddir ;
            Ddir = opendir(temp);
            struct dirent *Di;
            if(Ddir==NULL)
            {
                fprintf(stdout,"\033[1;31m--> ERROR :cannot read directory [ %s ]\033[0m\n",temp);
        exit_fail=1;

                return;
            }
            printf("%s:\n",temp);
                while((Di=readdir(Ddir))!=NULL)
                {

                    if(fal==1|| (fa==1 && fl==1))
                    {
                        stat(Di->d_name,&s);
                        printf((s.st_mode & __S_IFDIR)? "d":"-");
                        printf((s.st_mode & S_IRUSR)? "r":"-");
                        printf((s.st_mode & S_IWUSR)? "w":"-");
                        printf((s.st_mode & S_IXUSR)? "x":"-");
                        printf((s.st_mode & S_IRGRP)? "r":"-");
                        printf((s.st_mode & S_IWGRP)? "w":"-");
                        printf((s.st_mode & S_IXGRP)? "x":"-");
                        printf((s.st_mode & S_IROTH)? "r":"-");
                        printf((s.st_mode & S_IWOTH)? "w":"-");
                        printf((s.st_mode & S_IXOTH)? "x":"-");
                        printf(" ");
                        printf("%5lld",(long long int)s.st_nlink);
                        printf(" ");
                        struct passwd *pw = getpwuid(s.st_uid);
                        struct group *gr = getgrgid(s.st_gid);
                        printf("%s %s ",pw->pw_name,gr->gr_name);
                        printf("%5ld ",s.st_size );
                        sprintf(date_str,"%s",ctime(&s.st_ctime));
                        date_str[7]='\0';
                        date_str[10]='\0';
                        date_str[16]='\0';
                        printf("%s ",date_str +4);
                        printf("%s ",date_str +8 );
                        printf("%s ",date_str +11 );
                        printf("%s\n",Di->d_name);
                    }
                    else if(fl==1 && fa ==0)
                    {
                        if(Di->d_name[0]!='.')
                        {
                            stat(Di->d_name,&s);
                            printf((s.st_mode & __S_IFDIR)? "d":"-");
                            printf((s.st_mode & S_IRUSR)? "r":"-");
                            printf((s.st_mode & S_IWUSR)? "w":"-");
                            printf((s.st_mode & S_IXUSR)? "x":"-");
                            printf((s.st_mode & S_IRGRP)? "r":"-");
                            printf((s.st_mode & S_IWGRP)? "w":"-");
                            printf((s.st_mode & S_IXGRP)? "x":"-");
                            printf((s.st_mode & S_IROTH)? "r":"-");
                            printf((s.st_mode & S_IWOTH)? "w":"-");
                            printf((s.st_mode & S_IXOTH)? "x":"-");
                            printf(" ");
                            printf("%5lld",(long long int)s.st_nlink);
                            printf(" ");
                            struct passwd *pw = getpwuid(s.st_uid);
                            struct group *gr = getgrgid(s.st_gid);
                            printf("%s %s ",pw->pw_name,gr->gr_name);
                            printf("%5ld ",s.st_size );
                            sprintf(date_str,"%s",ctime(&s.st_ctime));
                            date_str[7]='\0';
                            date_str[10]='\0';
                            date_str[16]='\0';
                            printf("%s ",date_str +4);
                            printf("%s ",date_str +8 );
                            printf("%s ",date_str +11 );
                            printf("%s\n",Di->d_name);
                        }
                    }
                    else{
                        if(fa==1 && fl==0)
                        printf("%s\n",Di->d_name); 
                        else if(fal==0 && fa==0 && fl==0)
                        if(Di->d_name[0]!='.')
                        printf("%s\n",Di->d_name); 
                    }
                }
            if(i!=0)
            printf("\n");
        }
    }
    return;
}








void callingla(char *str,int zip,char *str1)
{
        ll fh=0;
    char date_str[250];
    char inp[100][10000];
    char *temp;
    temp=(char *)malloc(100000*sizeof(char));
    temp[0]='.';

    char *temp2;
    temp2 = strtok(str, " \t");
    ll i=0;
    while( temp2 != NULL ) 
    {
        fh=0;
        if(strcmp(temp2,"~")==0)fh=1;
        
        if(strcmp(temp2,"la")!=0){
            if(fh==1)
            strcpy(inp[i],str1);
            else
            strcpy(inp[i],temp2);
            i++;
        }
        temp2 = strtok(NULL, "  \t");
    }
    
    if(i==0)
    {
        strcpy(temp,".");
        struct stat s;
        DIR *Ddir ;
        Ddir = opendir(temp);
        struct dirent *Di;
        if(Ddir==NULL)
        {
           	fprintf(stdout,"\033[1;31m--> ERROR :cannot read directory [ %s ]\033[0m\n",temp);
        exit_fail=1;

            return;
        }
            while((Di=readdir(Ddir))!=NULL)
            {
                stat(Di->d_name,&s);
                printf((s.st_mode & __S_IFDIR)? "d":"-");
                printf((s.st_mode & S_IRUSR)? "r":"-");
                printf((s.st_mode & S_IWUSR)? "w":"-");
                printf((s.st_mode & S_IXUSR)? "x":"-");
                printf((s.st_mode & S_IRGRP)? "r":"-");
                printf((s.st_mode & S_IWGRP)? "w":"-");
                printf((s.st_mode & S_IXGRP)? "x":"-");
                printf((s.st_mode & S_IROTH)? "r":"-");
                printf((s.st_mode & S_IWOTH)? "w":"-");
                printf((s.st_mode & S_IXOTH)? "x":"-");
                printf(" ");
                printf("%5lld",(long long int)s.st_nlink);
                printf(" ");
                struct passwd *pw = getpwuid(s.st_uid);
                struct group *gr = getgrgid(s.st_gid);
                printf("%s %s ",pw->pw_name,gr->gr_name);
                printf("%5ld ",s.st_size );
                sprintf(date_str,"%s",ctime(&s.st_ctime));
                date_str[7]='\0';
                date_str[10]='\0';
                date_str[16]='\0';
                printf("%s ",date_str +4);
                printf("%s ",date_str +8 );
                printf("%s ",date_str +11 );
                printf("%s\n",Di->d_name);
            }
              
    }
    if(i==1)
    {
        strcpy(temp,inp[0]);
        struct stat s;
        DIR *Ddir ;
        Ddir = opendir(temp);
        struct dirent *Di;
        if(Ddir==NULL)
        {
            fprintf(stdout,"\033[1;31m--> ERROR :cannot read directory [ %s ]\033[0m\n",temp);
        exit_fail=1;

            return;

        }
        while((Di=readdir(Ddir))!=NULL)
        {
            printf((s.st_mode & __S_IFDIR)? "d":"-");
            printf((s.st_mode & S_IRUSR)? "r":"-");
            printf((s.st_mode & S_IWUSR)? "w":"-");
            printf((s.st_mode & S_IXUSR)? "x":"-");
            printf((s.st_mode & S_IRGRP)? "r":"-");
            printf((s.st_mode & S_IWGRP)? "w":"-");
            printf((s.st_mode & S_IXGRP)? "x":"-");
            printf((s.st_mode & S_IROTH)? "r":"-");
            printf((s.st_mode & S_IWOTH)? "w":"-");
            printf((s.st_mode & S_IXOTH)? "x":"-");
            printf(" ");
            printf("%5lld",(long long int)s.st_nlink);
            printf(" ");
            struct passwd *pw = getpwuid(s.st_uid);
            struct group *gr = getgrgid(s.st_gid);
            printf("%s %s ",pw->pw_name,gr->gr_name);
            printf("%5ld ",s.st_size );
                sprintf(date_str,"%s",ctime(&s.st_ctime));
            date_str[7]='\0';
            date_str[10]='\0';
            date_str[16]='\0';
            printf("%s ",date_str +4);
            printf("%s ",date_str +8 );
            printf("%s ",date_str +11 );
            printf("%s\n",Di->d_name);   
        }
    }
    else
    {
        while(i--)
        {
            strcpy(temp,inp[i]);
            struct stat s;
            DIR *Ddir ;
            Ddir = opendir(temp);
            struct dirent *Di;
            if(Ddir==NULL)
            {
            	fprintf(stdout,"\033[1;31m--> ERROR :cannot read directory [ %s ]\033[0m\n",temp);
        exit_fail=1;

                return;
            }
            printf("%s:\n",temp);
                while((Di=readdir(Ddir))!=NULL)
                {
                    stat(Di->d_name,&s);
                    printf((s.st_mode & __S_IFDIR)? "d":"-");
                    printf((s.st_mode & S_IRUSR)? "r":"-");
                    printf((s.st_mode & S_IWUSR)? "w":"-");
                    printf((s.st_mode & S_IXUSR)? "x":"-");
                    printf((s.st_mode & S_IRGRP)? "r":"-");
                    printf((s.st_mode & S_IWGRP)? "w":"-");
                    printf((s.st_mode & S_IXGRP)? "x":"-");
                    printf((s.st_mode & S_IROTH)? "r":"-");
                    printf((s.st_mode & S_IWOTH)? "w":"-");
                    printf((s.st_mode & S_IXOTH)? "x":"-");
                    printf(" ");
                    printf("%5lld",(long long int)s.st_nlink);
                    printf(" ");
                    struct passwd *pw = getpwuid(s.st_uid);
                    struct group *gr = getgrgid(s.st_gid);
                    printf("%s %s ",pw->pw_name,gr->gr_name);
                    printf("%5ld ",s.st_size );
                     sprintf(date_str,"%s",ctime(&s.st_ctime));
                    date_str[7]='\0';
                    date_str[10]='\0';
                    date_str[16]='\0';
                    printf("%s ",date_str +4);
                    printf("%s ",date_str +8 );
                    printf("%s ",date_str +11 );
                    printf("%s\n",Di->d_name);
                    
                }
            if(i!=0)
            printf("\n");
        }
    }
    return;
}
