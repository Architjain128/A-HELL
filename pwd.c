#include "header.h"

void callingpwd(char *str)
{
	char inp[10][10000];
    char *temp2;
    temp2 = strtok(str, " \t");
    ll i=0;
    while( temp2 != NULL &&  i<10) 
    {
        if(strcmp(temp2,"pwd")!=0 ){
            strcpy(inp[i],temp2);
            i++;
        }
        temp2 = strtok(NULL, "  \t");
    }

	if(i!=0)
	{
		printf("\033[0;33m-->WARNING : syntax invalid, multiple arguments output for : [ pwd ]\033[0m\n");
		printf("\033[0m");
	}

	char lot[1024];
	getcwd(lot,sizeof(lot));
	printf("%s\n",lot);

}