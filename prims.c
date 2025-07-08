#include <stdio.h>
#include <stdlib.h>
#define maximum 999
struct Node
{
int vertex;
int weight;
struct Node* next;
};
struct Graph
{
int numvertex;
struct Node* adjacencylist[maximum];
int adjacencymatrix[maximum][maximum];
};
struct Node* createnode(int vertex, int weight)
{
struct Node* newnode=(struct Node*)malloc(sizeof(struct Node));
newnode->vertex=vertex;
newnode->weight=weight;
newnode->next=NULL;
return newnode;
}
struct Graph* creategraph(int numvertex)
{
struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));
graph->numvertex=numvertex;
for(int i=0; i<numvertex; i++)
graph->adjacencylist[i]=0;
for(int i=0; i<numvertex; i++)
{
for(int j=0; j<numvertex; j++)

graph->adjacencymatrix[i][j] = 0;
}
return graph;
}
void addedge(struct Graph* graph, int source, int dest, int weight)
{
struct Node* newnode=createnode(dest, weight);
newnode->next=graph->adjacencylist[source];
graph->adjacencylist[source]=newnode;
newnode=createnode(source, weight);
newnode->next=graph->adjacencylist[dest];
graph->adjacencylist[dest]=newnode;
graph->adjacencymatrix[source][dest]=weight;
graph->adjacencymatrix[dest][source]=weight;
}
void prims_list(int graph_array[maximum][maximum], int numvertex, int startvertex)
{
int parent[maximum];
int element[maximum];
int array[maximum];
for(int i=0; i<numvertex; i++)
{
element[i]=maximum;
array[i]=0;
}
element[startvertex]=0;
parent[startvertex]=-1;
for(int i=0; i<numvertex-1; i++)
{
int minimum=maximum, temp;
for(int m=0; m<numvertex; m++)
{
if (!array[m]&&element[m]<minimum)
{
minimum=element[m];
temp=m;
}
}
array[temp]=1;
for(int j=0; j<numvertex; j++)

{
if(graph_array[temp][j]&&!array[j]&&graph_array[temp][j]<element[j])
{
parent[j]=temp;
element[j]=graph_array[temp][j];
}
}
}
printf("Edge\tWeight\n");
for (int i=1; i<numvertex; i++)
printf("%d--%d\t%d\n", parent[i], i, graph_array[i][parent[i]]);
}

void prims_matrix(struct Graph* graph, int startvertex)
{
int select[maximum]= {0};
int parent[maximum];
int element[maximum];
for (int i=0; i<graph->numvertex; i++)element[i]=maximum;
element[startvertex]=0;
parent[startvertex]=-1;
for (int i=0; i<graph->numvertex-1; i++)
{
int minele=maximum;
int temp;
for(int j=0; j<graph->numvertex; j++)
{
if(!select[j]&&element[j]<minele)
{
temp=j;
minele=element[temp];
}
}
select[temp] = 1;
for(int j=0; j<graph->numvertex; j++)
{
if(graph->adjacencymatrix[temp][j]!=0&&!select[j]&&graph->adjacencymatrix[temp][j]<element[j])
{
parent[j]=temp;
element[j]=graph->adjacencymatrix[temp][j];
}
}
}

printf("Edge\tWeight\n");
for (int i=1; i<graph->numvertex; i++)
{
printf("%d--%d\t%d\n", parent[i], i, element[i]);
}
}
int main()
{
int numvertex, numedge, startvertex, source, dest, weight;
int graph_array[maximum][maximum]={0};
printf("\nEnter the number of vertices: ");
scanf("%d", &numvertex);
struct Graph* graph=creategraph(numvertex);
printf("\nEnter the number of edges: ");
scanf("%d", &numedge);
for (int i=0; i<numedge; i++)
{
printf("\nEnter edge %d (source destination weight): ", i+1);
scanf("%d %d %d", &source, &dest, &weight);
addedge(graph, source, dest, weight);
graph_array[source][dest]=weight;
graph_array[dest][source]=weight;
}
printf("\nEnter the starting vertex: ");
scanf("%d", &startvertex);
int choice;
do
{
printf("\n1. Prim's Algorithm using Adjacency List");
printf("\n2. Prim's Algorithm using Adjacency Matrix");
printf("\n3. Exit\n");
printf("\nEnter your choice: ");
scanf("%d", &choice);
switch (choice)
{
case 1:
prims_list(graph_array, numvertex, startvertex);
break;
case 2:
prims_matrix(graph, startvertex);
break;

case 3:
printf("Exiting...\n");
break;
default:
printf("\nInvalid choice. Please try again.\n");
}
}
while(choice!=3);
return 0;
}
