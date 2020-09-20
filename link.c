#include "header.h"
typedef struct node
{
	int id;
    char name[10000];
	struct node* next;
}node;
struct node* head = NULL;
node* push( struct node*head, int a,char *b);
node* pop(struct node*head,int x);
node* push( struct node*head, int a,char *b)
{
	struct node*new;
	new = (struct node*)malloc(sizeof(node));
	new->id=a;
	strcpy(new->name,b);
	new->next=head;
	head=new;
	return head;
}
node* pop(struct node*head,int x)
{
	struct node* cur = head; 
    while (cur!=NULL)
    {
        printf("ohohoh");
        if(cur->id==x) 
        {
            printf("%s\n",cur->name);
            break;
        }  
        cur=cur->next;
    }
	return head;
}
void callingpop(int a){
    head=pop(head,a);
}
void callingpush(int a,char* str,char* str9){
    char pa[10000];
    strcpy(pa,str9);
    strcat(pa,"/pid.txt");
     FILE *hp;
    hp = fopen(pa,"a+");
    if(hp<0)
    {
        perror("opening pid.txt");
        return;
    }
        fprintf(hp,"%d\n",a);
        fprintf(hp,"%s\n",str);

}
void callingdelpid(char* str)
{
    char pa[10000];
    strcpy(pa,str);
    strcat(pa,"/pid.txt");
    remove(pa);
}
void callingpop2(int a){
    head=pop(head,a);
}
void callingpush2(int a,char* str){
    head=push(head,a,str);
}
