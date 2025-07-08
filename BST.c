#include <stdio.h>
#include <stdlib.h>
struct node
{
int data;
struct node *left;
struct node *right;
};
struct node *root=NULL;
struct node *create(int);
void insert(int);
struct node *delete(struct node *, int);
int search(int);
void inorder(struct node *);
void postorder();
void preorder();
int get_data();
int main()
{
int choice, data;
int yes_no='Y';
struct node *result=NULL;
while(yes_no=='Y'||yes_no=='y')
{
printf("\n1. Insert");
printf("\n2. Delete");
printf("\n3. Search");
printf("\n4. Inorder ");
printf("\n5. Post Order ");
printf("\n6. Pre Order ");
printf("\nEnter Your Choice");
scanf("%d", &choice);
switch (choice)
{

case 1:
{
data=get_data();
insert(data);
}
break;
case 2:
{
data=get_data();
root=delete (root, data);
}
break;
case 3:
{
data=get_data();
if(search(data)==1)
printf("\nFound!");
else
printf("\nNot found!");
}
break;
case 4:
inorder(root);
break;
case 5:
postorder(root);
break;
case 6:
preorder(root);
break;
default:
printf("\nWrong choice");
break;
}
printf("\nContinue? Y for Yes, N for No");
fflush(stdin);
scanf(" %c", &yes_no);
}
return 0;
}
struct node *create(int data)
{
struct node *newnode=(struct node *)malloc(sizeof(struct node));
newnode->data=data;
newnode->left=NULL;
newnode->right=NULL;

return newnode;
}
void insert(int data)
{
struct node *newnode=create(data);
if (newnode!=NULL)
{
if (root==NULL)
{
root=newnode;
return;
}
struct node *temp=root;
struct node *prev=NULL;
while(temp!=NULL)
{
prev=temp;
if(data>temp->data)
temp=temp->right;
else
temp=temp->left;
}
if (data>prev->data)
prev->right=newnode;
else
prev->left=newnode;
}
}
struct node *delete(struct node *root, int key)
{
if (root==NULL)
return root;
if (key<root->data)
root->left=delete(root->left, key);
else if (key>root->data)
root->right=delete (root->right, key);
else
{
if (root->left==NULL)
{
struct node *temp=root->right;
free(root);
return temp;
}
else if(root->right==NULL)
{
struct node *temp=root->left;

free(root);
return temp;
}
struct node *curr=root;
while(curr!=NULL&&curr->left!= NULL)
curr=curr->left;
struct node *temp=curr;
root->data=temp->data;
root->right=delete (root->right, temp->data);
}
return root;
}
int search(int key)
{
struct node *temp=root;
while(temp!=NULL)
{
if(key==temp->data)
return 1;
else if(key>temp->data)
temp=temp->right;
else if(key<temp->data)
temp=temp->left;
}
return 0;
}
void inorder(struct node *root)
{
if(root==NULL)return;
inorder(root->left);
printf("%d ", root->data);
inorder(root->right);
}
void preorder(struct node *root)
{
if(root==NULL)return;
printf("%d ", root->data);
preorder(root->left);
preorder(root->right);
}
void postorder(struct node *root)
{
if(root==NULL)return;
postorder(root->left);
postorder(root->right);
printf("%d ", root->data);
}

int get_data()
{
int data;
printf("\nEnter Data");
scanf("%d", &data);
return data;
}
