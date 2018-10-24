// C program for linked list implementation of stack 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
  
// A structure to represent a stack 
struct StackNode 
{ 
    char *data; 
    struct StackNode* next; 
}; 
  
struct StackNode* newNode(char *data) 
{ 
    struct StackNode* stackNode = (struct StackNode*) malloc(sizeof(struct StackNode)); 
    stackNode->data = (char*)malloc(10*sizeof(char));
    strcpy(stackNode->data, data); 
    stackNode->next = NULL; 
    return stackNode; 
} 
  
int isEmpty(struct StackNode *root) 
{ 
    return !root; 
} 
  
void push(struct StackNode** root, char *data) 
{ 
    struct StackNode* stackNode = newNode(data); 
    stackNode->next = *root; 
    *root = stackNode; 
    printf("%s pushed to stack\n", data); 
} 
  
char *pop(struct StackNode** root) 
{ 
    if (isEmpty(*root)) 
        return 0; 
    struct StackNode* temp = *root; 
    *root = (*root)->next; 
    char *popped = temp->data; 
    free(temp); 
  
    return popped; 
} 
  
char *peek(struct StackNode* root) 
{ 
    if (isEmpty(root)) 
        return 0; 
    return root->data; 
} 

int exists(struct StackNode* root, char *str){
    if (isEmpty(root)) 
        return 0; 
    struct StackNode* temp = root;
    while(temp){
        if(!strcmp(str, temp->data))
            return 1;
        temp = temp->next;
    }
}