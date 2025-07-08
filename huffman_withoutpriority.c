#include <stdio.h>
#include <stdlib.h>

// Define a structure for a Huffman tree node
struct Node {
    char data;
    unsigned frequency;
    struct Node* left;
    struct Node* right;
};

// Function to create a new Huffman tree node
struct Node* newNode(char data, unsigned frequency) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// Function to build the Huffman tree and return the root node
struct Node* buildHuffmanTree(char data[], unsigned frequency[], int size) {
    struct Node* nodes[size];

    // Create leaf nodes for each character and insert them into the nodes array
    for (int i = 0; i < size; ++i) {
        nodes[i] = newNode(data[i], frequency[i]);
    }

    // Repeat until there is only one node left in the nodes array
    while (size > 1) {
        // Find the two nodes with the lowest frequencies
        int min1 = 0, min2 = 1;
        if (nodes[min1]->frequency > nodes[min2]->frequency) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < size; ++i) {
            if (nodes[i]->frequency < nodes[min1]->frequency) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->frequency < nodes[min2]->frequency) {
                min2 = i;
            }
        }

        // Create a new internal node with the combined frequency
        struct Node* newnode = newNode('$', nodes[min1]->frequency + nodes[min2]->frequency);
        newnode->left = nodes[min1];
        newnode->right = nodes[min2];

        // Remove the two nodes with the lowest frequencies and insert the new node
        nodes[min1] = newnode;
        nodes[min2] = nodes[size - 1];
        size--;
    }

    // The remaining node is the root of the Huffman tree
    return nodes[0];
}

// Function to print Huffman codes from the root node
void printHuffmanCodes(struct Node* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printHuffmanCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printHuffmanCodes(root->right, arr, top + 1);
    }

    if (root->left == NULL && root->right == NULL) {
        printf("Character: %c, Code: ", root->data);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// Function to perform Huffman coding
void huffmanCoding(char data[], unsigned frequency[], int size) {
    struct Node* root = buildHuffmanTree(data, frequency, size);
    int arr[100], top = 0;
    printf("Huffman Codes:\n");
    printHuffmanCodes(root, arr, top);
}

int main() {
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

    huffmanCoding(new_str, freq, length2);

    return 0;
}
