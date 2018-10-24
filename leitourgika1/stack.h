#ifndef STACK_H
#define STACK_H

// A structure to represent a stack 
struct StackNode {
    char *data; 
    struct StackNode* next; 
}; 

struct StackNode* newNode(char *data);
int isEmpty(struct StackNode *root);
void push(struct StackNode** root, char *data);
char *pop(struct StackNode** root);
char *peek(struct StackNode* root);
int exists(struct StackNode* root, char *str);

#endif