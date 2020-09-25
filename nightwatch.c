#include "header.h"

void nightwatch(char *str, char *str1){
    char *temp2;
    char s[10000];
    char pork[10000];
    char inp[3][20];
    ll i=0;
    temp2 = strtok(str, " \t");
    while( temp2 != NULL && i<10 ) 
    {
        if(strcmp(temp2,"nightswatch")!=0 && strcmp(temp2,"-n")!=0){
            strcpy(inp[i],temp2);
            i++;
            if(i==3)
            break;
        }
        temp2 = strtok(NULL, " \t");
    }
    ll sec=0;
     ll base=pow(10,strlen(inp[0])-1);
        for(ll o=0;o<strlen(inp[0]);o++)
        {   
            ll u=inp[0][o]-'0';
            if(u>=0 && u<=9){
            sec+=(u*base);
            base/=10;
            }
        }

        if(strcmp(inp[1],"interrupt")==0 && i==2)
        {
            
            sprintf(pork,"/proc/interrupts");
            FILE *fp = fopen(pork,"r");
            fseek(fp, 0, SEEK_SET);
            
                while (fgets(s, sizeof(s), fp) != NULL) {
                    fprintf(stdout,"%s", s);
                    break;
                }
                

                fd_set readfds;
                struct timeval tv;
                int ch;
                int run=1, ret;
                FD_ZERO(&readfds);

                while ( run)
                {
                    char s[100000];
                    sprintf(pork,"/proc/interrupts");
                    FILE *fp = fopen(pork,"r");
                    fseek(fp, 0, SEEK_END);
                    ll pount=0;
                    while (fgets(s, sizeof(s), fp) != NULL) {
                        // fprintf(stdout,"%d %s", pount,s);
                        if(pount==2){
                            char *temp3;
                            ll kick=0;
                            temp3 = strtok(s, " \t");
                            while( temp3 != NULL ) 
                            {
                                if(kick==0)
                                fprintf(stdout,"%6s", " ");
                                else if(kick<=8)
                                printf("%10s ", temp3);
                                temp3 = strtok(NULL, " \t");
                                kick++;
                            }
                            fprintf(stdout,"\n");
                            break;
                        }
                        pount++;
                    }
                    FD_SET(STDIN_FILENO, &readfds);
                    tv.tv_sec = 0;
                    tv.tv_usec = 0;
                    ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
                    if (ret < 0) {
                   		fprintf(stdout,"\033[1;31m--> ERROR : undefined keystroke\033[0m\n");
        exit_fail=1;

                        exit(1);
                    } 
                    else if (ret == 0) 
                    {
                    } 
                    else if (FD_ISSET(STDIN_FILENO, &readfds)) 
                    {
                        ch = fgetc(stdin);
                        if (ch == 'q') {
                            run=0;
                        }
                    }
                    sleep(sec);

                }
        }
        else if(strcmp(inp[1],"newborn")==0 && i==2){
            sprintf(pork,"/proc/loadavg");
            FILE *fp = fopen(pork,"r");
            fseek(fp, 0, SEEK_SET);


            fd_set readfds;
            struct timeval tv;
            int ch;
            int run=1, ret;
            FD_ZERO(&readfds);
            while ( run )
            {
                char s[100000];
                sprintf(pork,"/proc/loadavg");
                FILE *fp = fopen(pork,"r");
                fseek(fp, 0, SEEK_END);
                ll pount=0;
                while (fgets(s, sizeof(s), fp) != NULL) {
                    if(pount==0){
                        char *temp3;
                        ll kick=0;
                        temp3 = strtok(s, " \t");
                        while( temp3 != NULL ) 
                        {
                            if(kick==4)
                            fprintf(stdout,"%s", temp3);
                            temp3 = strtok(NULL, " \t");
                            kick++;
                        }
                        break;
                    }
                    pount++;
                }
                FD_SET(STDIN_FILENO, &readfds);
                tv.tv_sec = 0;
                tv.tv_usec = 0;
                ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
                if (ret < 0) {
                    fprintf(stdout,"\033[1;31m--> ERROR : undefined keystroke\033[0m\n");
        exit_fail=1;

                    exit(1);
                } 
                else if (ret == 0) 
                {
                } 
                else if (FD_ISSET(STDIN_FILENO, &readfds)) 
                {
                    ch = fgetc(stdin);
                    if (ch == 'q') {
                        run=0;
                    }
                }
                sleep(sec);
            }
        }
        else{
            printf("--> ERROR : command not found\n");
        exit_fail=1;

        }
}
