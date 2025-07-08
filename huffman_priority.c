#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char data;
    unsigned frequency;
    struct Node* left;
    struct Node* right;
};

struct PriorityQueue
{
    unsigned size;
    unsigned capacity;
    struct Node** array;
};

struct Node* createNode(char data, unsigned frequency)
{
    struct Node* node=(struct Node*)malloc(sizeof(struct Node));
    node->data=data;
    node->frequency=frequency;
    node->left=node->right=NULL;
    return node;
}

struct PriorityQueue* createPriorityQueue(unsigned capacity)
{
    struct PriorityQueue* pq=(struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->size=0;
    pq->capacity=capacity;
    pq->array=(struct Node**)malloc(capacity * sizeof(struct Node*));
    return pq;
}

void minHeapify(struct PriorityQueue* pq, int idx)
{
    int smallest=idx;
    int left=2*idx+1;
    int right=2*idx+2;

    if(left<pq->size&&pq->array[left]->frequency<pq->array[smallest]->frequency)
        smallest = left;
    if(right<pq->size&&pq->array[right]->frequency<pq->array[smallest]->frequency)
        smallest=right;

    if(smallest!=idx)
    {
     struct Node* temp=pq->array[idx];
        pq->array[idx]=pq->array[smallest];
        pq->array[smallest]=temp;

        minHeapify(pq, smallest);
    }
}

struct Node* HuffmanTree(char data[], unsigned freq[], int size)
{
    struct Node *left, *right, *top;
    struct PriorityQueue* pq=createPriorityQueue(size);

    for (int i=0; i<size; ++i)
        pq->array[i] = createNode(data[i], freq[i]);

    pq->size=size;
    for(int i=size/2-1; i>=0; --i)
        minHeapify(pq, i);

    while(pq->size>1)
    {
        left=pq->array[0];
        pq->array[0]=pq->array[pq->size-1];
        --pq->size;
        minHeapify(pq, 0);

        right=pq->array[0];
        pq->array[0]=pq->array[pq->size-1];
        --pq->size;
        minHeapify(pq, 0);

        top=createNode('$', left->frequency+right->frequency);
        top->left=left;
        top->right=right;
        pq->array[pq->size]=top;
        ++pq->size;
        minHeapify(pq, pq->size-1);
    }

    return pq->array[0];
}

void HuffmanCodes(struct Node* root, int arr[], int current)
{
    if(root->left)
    {
        arr[current]=0;
        HuffmanCodes(root->left, arr, current+1);
    }
    if(root->right)
    {
        arr[current]=1;
        HuffmanCodes(root->right, arr, current+1);
    }
    if(!root->left && !root->right)
    {
        printf("%c: ",root->data);
        for (int i=0; i<current; ++i)
            printf("%d", arr[i]);
        printf("\n");
    }
}

int main()
{
char original_str[100], new_str[100];
    int length=0, length2=0;

    printf("Enter a String:\n");
    scanf("%s", original_str);


    while(original_str[length]!='\0')
    {
        length++;
    }

    int isdupe[256]={0};

    for(int i=0;i<length;i++)
    isdupe[i]=0;

    for(int i=0; i<length; i++)
    {
        char current=original_str[i];

        if(isdupe[current]==0)
        {
            new_str[length2++]=current;
            isdupe[current]=1;
        }
    }

    new_str[length2]='\0';

    printf("\nTrimmed string: %s\n", new_str);
    printf("\nLength of Trimmed String :: %d\n", length2);

    int cnt=0;
    int freq[256]={0};

    for(int i=0; i<length2; i++)
    {
        char letter=new_str[i];

        for(int j=0; j<length; j++)
        {
            if(letter==original_str[j])cnt++;
        }

        freq[i]=cnt;
        cnt=0;
    }

    for(int i=0; i<length2; i++)
        printf("\n %c :: %d\n", new_str[i], freq[i]);

    struct Node* root=HuffmanTree(new_str, freq, length2);

    printf("Huffman Codes:\n");
    int arr[100], top = 0;
    HuffmanCodes(root, arr, top);

    return 0;
}

