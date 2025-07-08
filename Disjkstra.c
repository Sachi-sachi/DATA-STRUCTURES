#include <stdio.h>
#include <stdlib.h>
struct AdjListNode
{
int dest;
int weight;
struct AdjListNode* next;
};
struct AdjList
{
struct AdjListNode* head;
};
struct Graph
{
int n;
struct AdjList* array;
};
struct AdjListNode* newAdjListNode(int dest, int weight)
{
struct AdjListNode* newnode=(struct AdjListNode*)malloc(sizeof(struct AdjListNode));
newnode->dest=dest;
newnode->weight=weight;
newnode->next=NULL;
return newnode;
}
struct Graph* createGraph(int n)
{
struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));
graph->n=n;
graph->array=(struct AdjList*)malloc(n * sizeof(struct AdjList));
for (int i=0; i <n; ++i)
graph->array[i].head=NULL;

return graph;
}
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
struct AdjListNode* newnode=newAdjListNode(dest, weight);
newnode->next=graph->array[src].head;
graph->array[src].head=newnode;
newnode=newAdjListNode(src, weight);
newnode->next=graph->array[dest].head;
graph->array[dest].head=newnode;
}
int minimumdistance(int dist[], int shortest[], int n)
{
int min=999, min_index;
for(int i=0; i<n; i++)
{
if(!shortest[i]&&dist[i]<min)
{
min=dist[i];
min_index=i;
}
}
return min_index;
}
void display(int dist[], int n)
{
printf("Vertex Distance from Source\n");
for (int i=0; i<n; i++)
printf("%d\t\t%d\n", i, dist[i]);
}
void printPath(int parent[], int j) {
if (parent[j] == -1) {
printf("%d -> ", j);
return;
}
printPath(parent, parent[j]);
printf("%d -> ", j);
}
void dijkstra_list(struct Graph* graph, int src)
{
int n=graph->n;
int dist[n];
int shortest[n];
int parent[n];
for(int i=0; i<n; i++)

{
dist[i]=999;
shortest[i]=0;
parent[i]=-1;
}
dist[src]=0;
for(int i=0; i<n-1; i++)
{
int u=minimumdistance(dist, shortest, n);
shortest[u]=1;
struct AdjListNode* temp=graph->array[u].head;
while(temp!=NULL)
{
int v=temp->dest;
if(!shortest[v]&&dist[u]!=999&&dist[u]+temp->weight<dist[v])
{
dist[v]=dist[u]+temp->weight;
parent[v]=u;
}
temp=temp->next;
}
}
printf("Vertex Distance from Source Path\n");
for (int i=0; i<n; i++)
{
printf("%d\t\t%d\t\t", i, dist[i]);
printPath(parent, i);
printf("\n");
}
}

void dijkstra_matrix(int **graph_matrix, int start, int n)
{
int dist[n];
int shortest[n];
for(int i=0; i<n; i++)
{
dist[i]=999;
shortest[i]=0;
}
dist[start]=0;
for (int count=0; count<n-1; count++)
{
int u=minimumdistance(dist, shortest, n);
shortest[u]=1;
for(int v=0; v<n; v++)

{
if(!shortest[v]&&graph_matrix[u][v]&&dist[u]!=999&&dist[u]+graph_matrix[u][v]<dist[v])
dist[v]=dist[u]+graph_matrix[u][v];
}
}
display(dist, n);
}
int main()
{
int n, e, src, choice, start;
printf("Enter the number of vertices: ");
scanf("%d", &n);
struct Graph* graph=createGraph(n);
int **graph_matrix=(int**)malloc(n * sizeof(int *));
printf("Enter the number of edges: ");
scanf("%d", &e);
for (int i=0; i<n; i++)
graph_matrix[i]=(int*)malloc(n * sizeof(int));
for (int i=0; i<n; i++)
{
for (int j=0; j<n; j++)
{
graph_matrix[i][j]=0;
}
}
for (int i=0; i<e; i++)
{
int src, dest, weight;
printf("Enter edge %d (source destination weight): ", i + 1);
scanf("%d %d %d", &src, &dest, &weight);
graph_matrix[src][dest]=weight;
graph_matrix[dest][src]=weight;
addEdge(graph, src, dest, weight);
}
printf("Enter the start vertex: ");
scanf("%d", &start);
do
{
printf("\n1. Dijkstra's Algorithm using Adjacency List");
printf("\n2. Dijkstra's Algorithm using Adjacency Matrix");
printf("\n3. Exit\n");
printf("\nEnter your choice: ");
scanf("%d", &choice);

switch (choice)
{
case 1:
dijkstra_list(graph, start);
break;
case 2:
dijkstra_matrix(graph_matrix, start, n);
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
