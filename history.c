#include "header.h"

void addhistory(char *str,char *str1)
{
    char pa[10000];
    char pa1[10000];
    strcpy(pa,str1);
    strcpy(pa1,str1);
    strcat(pa,"/history.txt");
    strcat(pa1,"/history2.txt");
    FILE *hp;
    hp = fopen(pa,"a+");
    if(hp<0)
    {
       fprintf(stdout,"\033[1;31m--> ERROR :cannot open history.txt\033[0m\n");
        exit_fail=1;
        return;
    }
      ll ctount=0;
    for (char c = getc(hp); c != EOF; c = getc(hp)) 
    if (c == '\n') 
    ctount ++;

    if(ctount<20)
    {
        fprintf(hp,"%s\n",str);
        fclose(hp);
    }
    else{
    char s[10000];
        FILE * hp2;
			hp2 = fopen (pa1,"a+");
			int pount=0;
			fseek(hp2,0,0);
			fseek(hp,0,0);
			fseek(hp, 0, SEEK_END);
                int pos = ftell(hp);
                while (pos) {
                    fseek(hp, --pos, SEEK_SET); 
                    if (fgetc(hp) == '\n') {
                        if (pount++ == 19) break;
                    }
                }
                while (fgets(s, sizeof(s), hp) != NULL) {
                    fprintf(hp2,"%s", s);
                }
			fprintf(hp2, "%s\n",str );
			fclose(hp);
			fclose(hp2);
			remove(pa);
			rename(pa1,pa);
    }
}


void callinghistory(char *str,int zip,char *str1){
    char inp[2][10];
    char *temp2;
    temp2 = strtok(str, " \t");
    ll i=0;
    while( temp2 != NULL &&  i<2) 
    {
        if(strcmp(temp2,"history")!=0 ){
            strcpy(inp[i],temp2);
            // strcat(inp[i],"\n");
            i++;
            if(i==2)i=1;
        }
        temp2 = strtok(NULL, "  \t");
    }
    char pa[10000];
    strcpy(pa,str1);
    strcat(pa,"/history.txt");
    FILE *hp;
    hp = fopen(pa,"r");
    if(hp<0)
    {
       fprintf(stdout,"\033[1;31m--> ERROR :cannot open history.txt\033[0m\n");
        exit_fail=1;

        return;
    }

    ll ctount=0;
    for (char c = getc(hp); c != EOF; c = getc(hp)) 
    if (c == '\n') 
    ctount ++;

	if(i>1)
	{
		fprintf(stdout,"\033[0;33m--> WARNING : syntax invalid, multiple arguments output for : [ history ]\033[0m\n");
        i=0;
	}
    if(i==0)
    {
        int pount=0;
        char s[1000000];
        if(ctount>10)
        {
               fseek(hp, 0, SEEK_END);
                int pos = ftell(hp);
                while (pos) {
                    fseek(hp, --pos, SEEK_SET); 
                    if (fgetc(hp) == '\n') {
                        if (pount++ == 10) break;
                    }
                }
                while (fgets(s, sizeof(s), hp) != NULL) {
                    fprintf(stdout,"%s", s);
                }
        }
        else
        {

            fseek(hp, 0, SEEK_SET);
                while (fgets(s, sizeof(s), hp) != NULL) {
                    fprintf(stdout,"%s", s);
                }
                 while (fgets(s, sizeof(s), hp) != NULL) {
                    fprintf(stdout,"%s", s);
                }
        }
    }
    else
    {
        int tount=0;
        int pount=0;
        char s[1000000];
        char gg[10];
        strcpy(gg,inp[0]);
        ll base=pow(10,strlen(gg)-1);
        for(ll o=0;o<strlen(gg);o++)
        {   
            ll u=gg[o]-'0';
            if(u>=0 && u<=9){
            tount+=(u*base);
            base/=10;
            }
        }
        if(tount>20)
        {
            fprintf(stdout,"\033[0;33m--> WARNING : max value of argument is 20 \033[0m\n");
             tount=20;
        }
        else if(ctount<tount)
        {
            fprintf(stdout,"\033[0;33m--> WARNING : insufficiet history data  \033[0m\n");
            tount=ctount;
        }
        else{
               fseek(hp, 0, SEEK_END);
                int pos = ftell(hp);
                while (pos) {
                    fseek(hp, --pos, SEEK_SET); 
                    if (fgetc(hp) == '\n') {
                        if (pount++ == tount) break;
                    }
                }
                while (fgets(s, sizeof(s), hp) != NULL) {
                    fprintf(stdout,"%s", s);
                }
        }
        
    }
    
}