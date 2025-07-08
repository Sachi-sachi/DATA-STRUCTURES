#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 100
void read_graph();
void insert(int,int);
void dfs_rec_list(int);

struct Queue
{
int items[MAX_VERTICES];
int front;
int rear;
};

struct Node
{
int vertex;
struct Node* next;
};
typedef struct diffnode
{
struct diffnode *nextp;
int v_copy;
} diffnode;
diffnode *G[20];
int visit_copy[20];

struct Graph
{
int numVertices;
struct Node* adjList[MAX_VERTICES];
int adjMatrix[MAX_VERTICES][MAX_VERTICES];
};
struct Queue* createQueue();
void enqueue(struct Queue* q, int value);
int dequeue(struct Queue* q);
int isEmpty(struct Queue* q);

bool isBipartite(struct Graph* graph, int startVertex) {
int color[MAX_VERTICES] = {0};
struct Queue* q = createQueue();
color[startVertex] = 1;
enqueue(q, startVertex);
while (!isEmpty(q)) {
int currVertex = dequeue(q);
struct Node* temp = graph->adjList[currVertex];
while (temp) {
int adjVertex = temp->vertex;
if (color[adjVertex] == color[currVertex]) {
return false;
}
if (color[adjVertex] == 0) {
color[adjVertex] = -color[currVertex];
enqueue(q, adjVertex);
}
temp = temp->next;
}
}
return true;
}

struct Queue* createQueue()
{
struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
q->front = -1;
q->rear = -1;
return q;
}
void enqueue(struct Queue* q, int value)

{
if (q->rear == MAX_VERTICES - 1)
{
printf("Queue is full\n");
}
else
{
if (q->front == -1)
{
q->front = 0;
}
q->rear++;
q->items[q->rear] = value;
}
}
int dequeue(struct Queue* q)
{
int item;
if (isEmpty(q))
{
printf("Queue is empty\n");
item = -1;
}
else
{
item = q->items[q->front];
q->front++;
if (q->front > q->rear)
{
q->front = q->rear = -1;
}
}
return item;
}
int isEmpty(struct Queue* q)
{
return q->rear == -1;
}

void bfsAdjMatrix(struct Graph* graph, int startNode)
{
int visited[MAX_VERTICES] = {0};
struct Queue* q = createQueue();
visited[startNode] = 1;
printf("\nBFS using (adjacency matrix) %d: ", startNode);
printf("%d ", startNode);
enqueue(q, startNode);

while (!isEmpty(q))
{
int currNode = dequeue(q);
for (int i = 0; i < graph->numVertices; i++)
{
if (graph->adjMatrix[currNode][i] == 1 && !visited[i])
{
printf("%d ", i);
visited[i] = 1;
enqueue(q, i);
}
}
}
printf("\n");
}
void bfsAdjList(struct Graph* graph, int startNode)
{
int visited[MAX_VERTICES] = {0};
struct Queue* q = createQueue();
visited[startNode] = 1;
printf("BFS using (adjacency list) %d: ", startNode);
printf("%d ", startNode);
enqueue(q, startNode);
while (!isEmpty(q))
{
int currNode = dequeue(q);
for (int i = 0; i < graph->numVertices; i++)
{
if (graph->adjMatrix[currNode][i] == 1 && !visited[i])
{
printf("%d ", i);
visited[i] = 1;
enqueue(q, i);
}
}
}
printf("\n");
}

struct Node* createNode(int vertex)
{
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->vertex = vertex;
newNode->next = NULL;
return newNode;

}
struct Graph* createGraph(int numVertices)
{
struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
graph->numVertices = numVertices;
for (int i = 0; i < numVertices; ++i)
{
graph->adjList[i] = NULL;
}
for (int i = 0; i < numVertices; i++)
{
for (int j = 0; j < numVertices; j++)
{
graph->adjMatrix[i][j] = 0;
}
}
return graph;
}
void addEdge(struct Graph* graph, int src, int dest)
{
struct Node* newNode = createNode(dest);
newNode->next = graph->adjList[src];
graph->adjList[src] = newNode;
graph->adjMatrix[src][dest] = 1;
graph->adjMatrix[dest][src] = 1;
}

void dfs_rec_list(int i)
{
diffnode *p;
printf("%d ",i);
p=G[i];
visit_copy[i]=1;
while(p!=NULL)
{
i=p->v_copy;
if(!visit_copy[i])
dfs_rec_list(i);
p=p->nextp;
}
}
void insert(int vi,int vj)
{
diffnode *p,*q;

q=(diffnode*)malloc(sizeof(diffnode));
q->v_copy=vj;
q->nextp=NULL;
if(G[vi]==NULL)
G[vi]=q;
else
{
p=G[vi];
while(p->nextp!=NULL)
p=p->nextp;
p->nextp=q;
}
}

void dsf_withoutrec_list(struct Graph* graph, int startVertex)
{
int visited[MAX_VERTICES] = {0};
printf("\nDFS (Iteration) %d: ", startVertex);
int stack[MAX_VERTICES];
int top = -1;
stack[++top] = startVertex;
visited[startVertex] = 1;
while (top != -1)
{
int vertex = stack[top--];
printf("%d ", vertex);
struct Node* temp = graph->adjList[vertex];
while (temp)
{
int adjVertex = temp->vertex;
if (!visited[adjVertex])
{
stack[++top] = adjVertex;
visited[adjVertex] = 1;
}
temp = temp->next;
}
}
printf("\n");
}

void dfs_matrix_rec(int vertex, int visited[], int adjacencyMatrix[][MAX_VERTICES], int numVertices)
{

printf("%d ", vertex);
visited[vertex] = 1;
for (int i = 0; i < numVertices; i++)
{
if (adjacencyMatrix[vertex][i] == 1 && !visited[i])
{
dfs_matrix_rec(i, visited, adjacencyMatrix, numVertices);
}
}
}
void dfs_matrix_without_recursion(int startVertex, int adjacencyMatrix[][MAX_VERTICES], int numVertices)
{
int visited[MAX_VERTICES] = {0};
int stack[MAX_VERTICES];
int top = -1;
printf("\nDFS (Iteration) %d: ", startVertex);
stack[++top] = startVertex;
visited[startVertex] = 1;
printf("%d ", startVertex);
while (top != -1)
{
int vertex = stack[top];
int found = 0;
for (int i = 0; i < numVertices; i++)
{
if (adjacencyMatrix[vertex][i] == 1 && !visited[i])
{
printf("%d ", i);
stack[++top] = i;
visited[i] = 1;
found = 1;
break;
}
}
if (!found)
top--;
}
printf("\n");
}

int main()
{
int numVertices, numEdges, choice, startVertex, src, dest;

int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES] = {0};
printf("\nEnter the number of vertices: ");
scanf("%d", &numVertices);
struct Graph* graph = createGraph(numVertices);
printf("\nEnter the number of edges: ");
scanf("%d", &numEdges);
for (int i = 0; i < numEdges; ++i)
{
printf("Enter edge %d (source destination): ", i + 1);
scanf("%d %d", &src, &dest);
addEdge(graph, src, dest);
insert(src,dest);
adjacencyMatrix[src][dest] = 1;
}
printf("\nEnter the starting vertex: ");
scanf("%d", &startVertex);
do
{
printf("\n1. DFS using adjacency list with recursion");
printf("\n2. DFS using adjacency list without recursion");
printf("\n3. DFS using adjacency matrix with recursion");
printf("\n4. DFS using adjacency matrix without recursion");
printf("\n5. BFS using adjacency matrix");
printf("\n6. BFS using adjacency list");
printf("\n7. To check if the input graph is Bipartite or not");
printf("\n8. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice)
{
case 1:
for(int i=0; i<numVertices; i++)
visit_copy[i]=0;
dfs_rec_list(startVertex);
break;
case 2:
dsf_withoutrec_list(graph, startVertex);
break;
case 3:
for(int i=0; i<numVertices; i++)
visit_copy[i]=0;
dfs_matrix_rec(startVertex, visit_copy, adjacencyMatrix, numVertices);

break;
case 4:
dfs_matrix_without_recursion(startVertex, adjacencyMatrix, numVertices);
break;
case 5:
bfsAdjMatrix(graph, startVertex);

break;
case 6:
bfsAdjList(graph, startVertex);
break;
case 7:
if (isBipartite(graph, startVertex))printf("The graph is bipartite as its vertices can be divided into two
independent sets.\n");
else printf("The graph is not bipartite as its vertices cannot be divided into two independent sets.\n");
break;
case 8:
printf("Exiting...\n");
break;
default:
printf("Invalid choice. Please try again.\n");
}
}
while (choice != 8);
return 0;
}
