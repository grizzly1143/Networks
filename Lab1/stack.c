#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void create_stack (struct Stack * stack) {
    stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->head = NULL;
    stack->size = 0;
}

struct Node * create_node (int value) {
    struct Node * res = (struct Node *) malloc(sizeof(struct Node));
    res->value = value;
    res->next = NULL;
    return res;
}

int peek (struct Stack * stack) {
    if (stack->size == 0) {
        fprintf(stderr, "Error! Stack is empty.\n");
        return NULL;
    } else {
        return stack->head->value;
    }
}

void push (struct Stack * stack, int data) {
    if (stack == NULL) {
        stack = (struct Stack *) malloc(sizeof(struct Stack));
        stack->head = create_node(data);
        stack->size++;
    } else if (stack->size == 0) {
        stack->head = create_node(data);
        stack->size++;
    } else {
        struct Node * node = create_node(data);
        node->next = stack->head;
        stack->head = node;
        stack->size++;
    }
}

void pop (struct Stack * stack) {
    if (stack->size == 0) {
        fprintf(stderr, "Error! Stack is empty.\n");
    } else {
        struct Stack * temp = stack->head;
        stack->head = stack->head->next;
        free(temp);
        stack->size--;
    }
}

int empty (struct Stack * stack) {
    if (stack->size == 0) {
        return 1;
    } else {
        return 0;
    }
}

void display (struct Stack * stack) {
    struct Node * temp = stack->head;
    while (temp != NULL) {
        printf ("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

void stack_size (struct Stack * stack) {
    printf("Stack size is: %d\n", stack->size);
}