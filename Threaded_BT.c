#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum { false, true } boolean;
struct node
{
struct node* left;
boolean lthread;
int value;
boolean rthread;
struct node* right;
};
typedef struct tree
{
char data;
struct tree* left;
struct tree* right;
boolean isThreaded;
} tree;
typedef struct stack
{
tree* data;
struct stack* next;
} stack;
struct node* success(struct node* p);

struct node* predec(struct node* p);
struct node* insert(struct node* root, int ele);
struct node* del(struct node* root, int ele);
struct node* first_block(struct node* root, struct node* par, struct node* ptr);
struct node* sec_block(struct node* root, struct node* par, struct node* ptr);
struct node* third_block(struct node* root, struct node* par, struct node* ptr);
void inorder(struct node* root);
void preorder(struct node* root);
struct node* head=NULL;
tree* create(char data)
{
tree* newnode=(tree*)malloc(sizeof(tree));
newnode->data = data;
newnode->left = NULL;
newnode->right = NULL;
newnode->isThreaded = false;
return newnode;
}
void push(stack** top, tree* data)
{
stack* newnode=(stack*)malloc(sizeof(stack));
newnode->data=data;
newnode->next = *top;
*top = newnode;
}
tree* pop(stack** top)
{
if (*top==NULL)return NULL;
tree* data=(*top)->data;
stack* temp=*top;
*top=(*top)->next;
free(temp);
return data;
}
tree* build(char* expr)
{
int i=0;
tree* root = NULL;
stack* stack = NULL;
while(expr[i]!='\0')
{
char ch=expr[i];
if(ch==' ')
{

i++;
continue;
}
if(ch=='(')i++;
else if(ch=='+'||ch=='-'||ch=='*'||ch=='%')
{
tree* newnode=create(ch);
newnode->left=pop(&stack);
if(stack!=NULL&&stack->data->right==NULL)
{
stack->data->right=newnode;
stack->data->isThreaded=true;
}
push(&stack, newnode);
i++;
}
else if(ch == ')')i++;
else
{
tree* newnode = create(ch);
push(&stack, newnode);
if (stack->next != NULL && stack->next->data->right == NULL)
{
stack->next->data->right = newnode;
stack->next->data->isThreaded = true;
}
i++;
}
}
if (stack != NULL)
{
root = stack->data;
while (stack->next != NULL)stack = stack->next;
stack->data->isThreaded = true;
}
return root;
}
int evaluate(tree* root)
{
if(root==NULL)return 0;
if(root->data =='+')return evaluate(root->left)+evaluate(root->right);
else if (root->data=='-')return evaluate(root->left)-evaluate(root->right);

else if (root->data=='*')return evaluate(root->left)*evaluate(root->right);
else if (root->data=='%')return evaluate(root->left)%evaluate(root->right);
else return root->data-'0';
}
void mem_free(tree* root)
{
if (root == NULL)return;
mem_free(root->left);
if (!root->isThreaded)mem_free(root->right);
free(root);
}
int main()
{
int choice, num;
char expr[100];
while (1)
{
printf("\n");
printf("1.Insert\n");
printf("2.Delete\n");
printf("3.Inorder\n");
printf("4.Evaluate\n");
printf("\nEnter your choice : ");
scanf("%d", &choice);
switch (choice)
{
case 1:
printf("\nEnter number to insert: ");
scanf("%d", &num);
head = insert(head, num);
break;
case 2:
printf("\nEnter number to delete: ");
scanf("%d", &num);
head = del(head, num);
break;
case 3:
inorder(head);
break;
case 4:
printf("Enter an Expression: ");
scanf("%s", expr);

tree* root = build(expr);
int result = evaluate(root);
printf("Result: %d\n", result);
break;
default:
printf("\nWrong choice\n");
}
}
return 0;
}
struct node* insert(struct node* root, int ele)
{
struct node* tmp, * par, * ptr;
int found=0;
ptr=root;
par=NULL;
while(ptr!=NULL)
{
if(ele==ptr->value)
{
found=1;
break;
}
par=ptr;
if(ele<ptr->value)
{
if(ptr->lthread==false)ptr=ptr->left;
else break;
}
else
{
if(ptr->rthread==false)ptr = ptr->right;
else break;
}
}
if (found)printf("\nRepeated");
else
{
tmp=(struct node*)malloc(sizeof(struct node));
tmp->value=ele;
tmp->lthread=true;
tmp->rthread=true;
if (par==NULL)

{
root=tmp;
tmp->left=NULL;
tmp->right=NULL;
}
else if(ele<par->value)
{
tmp->left=par->left;
tmp->right=par;
par->lthread=false;
par->left=tmp;
}
else
{
tmp->left=par;
tmp->right=par->right;
par->rthread=false;
par->right=tmp;
}
}
return root;
}
struct node* del(struct node* root, int ele)
{
struct node* par, * ptr;
int found = 0;
ptr=root;
par=NULL;
while(ptr!=NULL)
{
if(ele==ptr->value)
{
found=1;
break;
}
par = ptr;
if (ele<ptr->value)
{
if(ptr->lthread==false)ptr=ptr->left;
else break;
}
else
{
if (ptr->rthread == false)ptr = ptr->right;
else break;
}

}
if (found == 0)
printf("\nNot present in tree");
else if (ptr->lthread == false && ptr->rthread == false)
root=third_block(root, par, ptr);
else if (ptr->lthread == false)
root=sec_block(root, par, ptr);
else if (ptr->rthread == false)
root=sec_block(root, par, ptr);
else root=first_block(root, par, ptr);
return root;
}
struct node* first_block(struct node* root, struct node* par, struct node* ptr)
{
if(par==NULL)root=NULL;
else if(ptr==par->left)
{
par->lthread=true;
par->left=ptr->left;
}
else
{
par->rthread = true;
par->right = ptr->right;
}
free(ptr);
return root;
}
struct node* sec_block(struct node* root, struct node* par, struct node* ptr)
{
struct node* child, *s, *p;
if (ptr->lthread == false)child=ptr->left;
else child = ptr->right;

if(par==NULL)root=child;
else if(ptr==par->left)par->left=child;
else par->right=child;
s=success(ptr);
p=predec(ptr);
if (ptr->lthread == false)
p->right=s;
else
{
if (ptr->rthread == false)

s->left=p;
}
free(ptr);
return root;
}
struct node* third_block(struct node* root, struct node* par, struct node* ptr)
{
struct node* succ, * parsucc;
parsucc = ptr;
succ = ptr->right;
while(succ->left!=NULL)
{
parsucc = succ;
succ = succ->left;
}
ptr->value=succ->value;
if(succ->lthread==true&&succ->rthread==true)
root=first_block(root, parsucc, succ);
else
root=sec_block(root, parsucc, succ);
return root;
}
struct node* success(struct node* ptr)
{
if (ptr->rthread == true)
return ptr->right;
else
{
ptr = ptr->right;
while (ptr->lthread == false)
ptr = ptr->left;
return ptr;
}
}
struct node* predec(struct node* ptr)
{
if (ptr->lthread==true)
return ptr->left;
else
{
ptr = ptr->left;
while (ptr->rthread==false)
ptr = ptr->right;
return ptr;
}

}
void inorder(struct node* root)
{
struct node* ptr;
if(root==NULL)
{
printf("Empty tree!");
return;
}
ptr=root;
while(ptr->lthread==false)
ptr=ptr->left;
while (ptr!=NULL)
{
printf("%d ", ptr->value);
ptr = success(ptr);
}
}
