# include "header.h"
void callingoverkill()
{
    for(int j=0;j<job_counter;j++)
    {
        if(order[j][1]==-1 )
        {
            if(kill(order[j][0],9)<0)
            {
                // perror("kjob");
            }
            stat_pro[order[j][0]]=0;
        }
    }
    return;
}
