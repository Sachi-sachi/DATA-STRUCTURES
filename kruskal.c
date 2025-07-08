#include <stdio.h>
#include <stdlib.h>
#define MAX 999
struct edge
{
int src, dest, cost;
};
struct Node
{
int dest, cost;
struct Node *next;
};
struct Graph
{
int vertex, edge;
struct Node **adjlist;
};
int find(int parent[], int i);
void unionsets(int parent[], int x, int y);
void kruskal_matrix(int **graph, int vertex, int edge);

void kruskal_adjlist(struct Graph *graph)
{
int vertex=graph->vertex;
int edge=graph->edge;
int sum=0;
struct edge *edges=(struct edge*)malloc(edge* sizeof(struct edge));
int count=0;
for(int i=0; i<vertex; ++i)
{
struct Node *node=graph->adjlist[i];
while(node!=NULL)

{
if(node->dest>i)
{
edges[count].src=i;
edges[count].dest=node->dest;
edges[count].cost=node->cost;
count++;
}
node=node->next;
}
}
for(int i=0; i<count-1;++i)
{
for(int j=0; j<count-i-1; ++j)
{
if(edges[j].cost>edges[j+1].cost)
{
struct edge temp=edges[j];
edges[j]=edges[j+1];
edges[j+1]=temp;
}
}
}
int *parent=(int*)malloc(vertex* sizeof(int));
for(int i=0; i<vertex; ++i)
parent[i]=i;
printf("Edges in the Minimum Spanning Tree:\n");
for(int i=0; i<count; ++i)
{
if(find(parent, edges[i].src)!=find(parent, edges[i].dest))
{
printf("%d - %d cost: %d\n", edges[i].src, edges[i].dest, edges[i].cost);
sum=sum+edges[i].cost;
unionsets(parent, find(parent, edges[i].src), find(parent, edges[i].dest));
}
}
printf("\nMinimum Cost= %d\n", sum);
free(edges);
free(parent);
}
struct Graph *creategraph(int vertex, int edge)
{
struct Graph *graph=(struct Graph *)malloc(sizeof(struct Graph));
graph->vertex=vertex;
graph->edge=edge;
graph->adjlist=(struct Node**)malloc(vertex* sizeof(struct Node *));

for(int i=0; i<vertex; ++i)
graph->adjlist[i]=NULL;
return graph;
}
void addedge(struct Graph *graph, int src, int dest, int cost)
{
struct Node *newnode=(struct Node *)malloc(sizeof(struct Node));
newnode->dest=dest;
newnode->cost=cost;
newnode->next=graph->adjlist[src];
graph->adjlist[src]=newnode;
newnode = (struct Node *)malloc(sizeof(struct Node));
newnode->dest=src;
newnode->cost=cost;
newnode->next=graph->adjlist[dest];
graph->adjlist[dest] = newnode;
}
void kruskal_matrix(int **graph, int vertex, int edge)
{
struct edge *edges=(struct edge*)malloc(edge* sizeof(struct edge));
int count=0, sum=0;
for(int i=0; i<vertex; ++i)
{
for(int j=i+1; j<vertex; ++j)
{
if(graph[i][j]!=MAX)
{
edges[count].src=i;
edges[count].dest=j;
edges[count].cost=graph[i][j];
count++;
}
}
}
for(int i=0; i<count-1; ++i)
{
for(int j=0; j<count-i-1; ++j)
{
if (edges[j].cost>edges[j + 1].cost)
{
struct edge temp=edges[j];
edges[j]=edges[j+1];
edges[j+1]=temp;
}

}
}
int *parent=(int*)malloc(vertex* sizeof(int));
for(int i=0; i<vertex; ++i)
parent[i]=i;
printf("Edges in the Minimum Spanning Tree:\n");
for(int i=0; i<count; ++i)
{
int x=find(parent, edges[i].src);
int y=find(parent, edges[i].dest);
if (x!=y)
{
printf("%d - %d cost: %d\n", edges[i].src, edges[i].dest, edges[i].cost);
sum=sum+edges[i].cost;
unionsets(parent, x, y);
}
}
printf("\nMinimum Cost= %d\n", sum);
free(edges);
free(parent);
}

int find(int parent[], int i)
{
if(parent[i]==i)return i;
return find(parent, parent[i]);
}
void unionsets(int parent[], int x, int y)
{
int first=find(parent,x);
int second=find(parent,y);
parent[first]=second;
}
int main()
{
int vertex, edge;
printf("Enter number of vertices: ");
scanf("%d", &vertex);
printf("Enter number ofedges: ");
scanf("%d", &edge);
int **adjMatrix=(int**)malloc(vertex* sizeof(int *));
for(int i=0; i<vertex; ++i)
{

adjMatrix[i]=(int*)malloc(vertex* sizeof(int));
for (int j=0; j<vertex; ++j)
adjMatrix[i][j]=MAX;
}
struct Graph *graph=creategraph(vertex, edge);
printf("Enter the Source, Destination and Cost:\n");
for (int i=0; i<edge;++i)
{
int src, dest, cost;
scanf("%d %d %d", &src, &dest, &cost);
addedge(graph, src, dest, cost);
adjMatrix[src][dest]=adjMatrix[dest][src]=cost;
}

int choice;
do
{
printf("\n1. Kruskal's Algorithm using Adjacency List");
printf("\n2. Kruskal's Algorithm using Adjacency Matrix");
printf("\n3. Exit\n");
printf("\nEnter your choice: ");
scanf("%d", &choice);
switch(choice)
{
case 1:
kruskal_adjlist(graph);
break;
case 2:
kruskal_matrix(adjMatrix, vertex, edge);
break;
case 3:
printf("Exiting...\n");
break;
default:
printf("\nInvalid choice.\n");
}
}
while(choice!=3);
return 0;
}
