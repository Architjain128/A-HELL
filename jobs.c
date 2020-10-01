# include "header.h"

void callingjobs(){
    ll j=0;
    for (ll i=0;i<job_counter;i++)
    {
        if(order[i][1]==0)
        {
            printf("[%lld] running as shell %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);
            j++;
        }
        else if(order[i][1]==-1 || stat_pro[order[i][0]]==2)
        {
            if(stat_pro[order[i][0]]==0)
            {
                printf("[%lld] stopped %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);
            }
            else if(stat_pro[order[i][0]]==2)
            {
                char * var2=(malloc(sizeof(char)*1005));
                sprintf(var2,"/proc/%d/stat",order[i][0]);
                FILE *f =fopen(var2,"r");
                if(f==NULL) 
                {
                    printf("[%lld] stopped (unknown) %s [%d]\n",j,back_pro[order[i][0]],order[i][0]);
                }
                else
                {
                    ll z=0;
                    int p;
                    char r[300];
                    char s;
                    char * atr;
                    for(z=0;z<3;z++)
                    {
                        if(z==0)   fscanf(f,"%d",&p);
                        if(z==1)   fscanf(f,"%s",r);
                        if(z==2)   fscanf(f," %c",&s);
                    }
                    if(s=='R') stat_pro[i]=2;
                    if(s=='S') stat_pro[i]=2;
                    if(s!='S'&&s!='R') stat_pro[i]=1;
                    if(stat_pro[i]==1)   atr="stopped";
                    else     atr="running";
                    printf("[%lld] %s %s [%d]\n",j,atr,back_pro[order[i][0]],order[i][0]);
                }

            }
            j++;
        }
    }
    return;
}





