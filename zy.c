
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
char *pidname;

typedef struct node
{
	int id;
    char name[10000];
	struct node* next;
}node;


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
        if(cur->id==x) 
        {
            printf("%s\n",cur->name);
            break;
        }  
        cur=cur->next;
    }
	return head;
}

int main() 
{ 
    struct node* head = NULL;
    int t,x,y,a;
    char *ok;

    scanf("%d",&t);
    while (t--)
    {
    scanf("%d",&x);
        if(x==1)
        {
            scanf("%d",&a);
            scanf("%s",ok);
            head=push(head,a,ok);
        }
        if(x==2)
        {
            scanf("%d",&y);
            head=pop(head,y);
        }
    }

	return 0; 
}
