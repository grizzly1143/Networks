#ifndef NWLAB1_STACK_H
#define NWLAB1_STACK_H
struct Node {
    int value;
    struct Node * next;
};

struct Stack {
    struct Node * head;
    int size;
};

int peek (struct Stack * stack);

void push (struct Stack * stack, int data);

void pop (struct Stack * stack);

int empty (struct Stack * stack);

void display (struct Stack * stack);

void create_stack (struct Stack * stack);

void stack_size (struct Stack * stack);

struct Node * create_node (int value);
#endif
