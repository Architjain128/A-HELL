#include "header.h"

int pathx()
{
    for(ll i=0;i<strlen(execut);i++)
    {
        if(curdir[i]!=execut[i])
        return 0;
    }
    return 1;
}
void prompt_pathy()
{
    if(execut==curdir)
    {
       
        char temp[]= "~";
        memset(dir, '\0', sizeof(dir));
        strcpy(dir,temp);
        
    }
    else if(pathx()==1)
    {
        dir[0]='~';
        ll j=1;
        for(ll i=strlen(execut);i<strlen(curdir);i++)
        {
            dir[j]=curdir[i];
            j++;
        }
        dir[j]='\0';
    }
    else
    {
        
        memset(dir, '\0', sizeof(dir));
        strcpy(dir,curdir);
    }
    
}
void prompt_init()
{
    gethostname(host , 100);
    strcpy(user,getlogin());
    getcwd(execut,sizeof(execut));
}