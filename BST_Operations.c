#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
int data;
struct node *left;
struct node *right;
} node;
struct node *root=NULL;
struct node *prev = NULL;
int bst(struct node* root);
void leafnode(node *root);
int mirror(struct node* root1, struct node* root2);
int check_mirror(struct node* root);
struct node *insert();
struct node *create();
void current(struct node *root, int level);
void levelorder(struct node *root);
int height(struct node *node);
int get_data();
int main()
{
int choice, data;
char yes_no='Y';
struct node *result=NULL;
while(yes_no=='Y'||yes_no=='y')
{
printf("\n1. Insert");
printf("\n2. Height ");
printf("\n3. Level Order Traversal ");

printf("\n4. Mirror Image ");
printf("\n5. Print leaf nodes ");
printf("\n6. Check if it is a Binary Search tree ");
printf("\nEnter Your Choice");
scanf("%d", &choice);
switch (choice)
{
case 1:
{
root=insert();
}
break;
case 2:
{
height(root);
int h = height(root);
printf("%d ", h);
}
break;
case 3:
levelorder(root);
break;
case 4:
{
if(check_mirror(root))
printf("\nIt has a Mirror Image!\n");
else
printf("\nIt does not have a Mirror Image!\n");
}
break;
case 5:
leafnode(root);
break;
case 6:
{
if(bst(root))
printf("\nIt is Binary Search Tree!\n");
else
printf("It is not a Binary Search Tree!");
}

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
struct node *create()
{
struct node *newnode=(struct node *)malloc(sizeof(struct node));
newnode->data=get_data();
newnode->left=NULL;
newnode->right=NULL;
return newnode;
}
struct node *insert()
{
struct node *newnode=create();
printf("Press -1 to exit out of the child\n");
if (newnode->data==-1)
return 0;
printf("Enter left child of %d\n", newnode->data);
newnode->left=insert();
printf("Enter right child of %d\n", newnode->data);
newnode->right=insert();
return newnode;
}
int get_data()
{
int data;
printf("\nEnter Data");
scanf("%d", &data);
return data;
}

int height(struct node *node)
{
if(node==NULL)return 0;
else
{
int leftheight=height(node->left);
int rightheight=height(node->right);
if(leftheight>rightheight)return (leftheight+1);
else return (rightheight+1);
}
}
void current(struct node *root, int level)
{
if(root==NULL)return;
if(level==1)printf("%d ", root->data);
else if(level>1)
{
current(root->left, level-1);
current(root->right, level-1);
}
}
void levelorder(struct node *root)
{
int h=height(root);
for(int i=1; i<=h; i++)
current(root,i);
}
int mirror(struct node* root1, struct node* root2)
{
if(root1==NULL&&root2==NULL)return 1;
if (root1&&root2&&root1->data==root2->data)
return mirror(root1->left, root2->right)&&mirror(root1->right, root2->left);
return 0;
}
int check_mirror(struct node* root)
{
return mirror(root, root);
}
void leafnode(node *root)
{
if(root==NULL)return;

if(root->left==NULL&&root->right==NULL)
{
printf("%d ", root->data);
return;
}
if(root->left)leafnode(root->left);
if(root->right)leafnode(root->right);
}
int bst(struct node* root)
{
if(root!=NULL)
{
if(!bst(root->left))
return 0;
if(prev!=NULL&&root->data<=prev->data)
return 0;
prev=root;
return bst(root->right);
}
return 1;
}
