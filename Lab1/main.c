#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "stack.h"

int main() {
    int fd[2];
    char str[10];
    pid_t p;
    pid_t ppid = getpid();
    struct Stack * stack;
    stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->head = NULL;
    stack->size = 0;
    if (pipe(fd)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    p = fork();
    if (p < 0)
    {
        fprintf(stderr, "Fork Failed" );
        return 1;
    }
    else if (p == 0)
    {
        while (1) {
            close(fd[1]);
            read(fd[0], str, 10);
            printf("Server(child) received: %s\n", str);
            if (strcmp(str, "peek") == 0) {
                printf("Server is peeking from stack.\n");
                peek(stack);
            }
            if (strcmp(str, "create") == 0) {
                printf("Server is creating stack.\n");
                create_stack(stack);
            }
            if (strcmp(str, "stack_size") == 0) {
                stack_size(stack);
            }
            if (strcmp(str, "display") == 0) {
                printf("Server is displaying stack:\n");
                display(stack);
            }
            if (strcmp(str, "pop") == 0) {
                printf("Server is popping from stack\n");
                pop(stack);
            }
            if (strcmp(str, "empty") == 0) {
                if (empty(stack) == 0) {
                    printf("Stack is not empty.\n");
                } else {
                    printf("Stack is not empty.\n");
                }
            }
            if (strcmp(str, "push") == 0){
                printf("Data to push: ");
                int data;
                fscanf(stdin, "%d",&data);
                printf("Server is pushing %d to stack\n", data);
                push(stack, data);
            }
            if (strcmp(str, "exit") == 0){
                printf("Exiting the program\n");
                kill(ppid, SIGKILL);
                close(fd[0]);
                close(fd[1]);
                exit(0);
            }
            kill(ppid, SIGCONT);
        }
    }
    else
    {
        while (1) {
            printf("Write a command to execute: ");
            scanf("%s", str);
            printf("Client(parent) sent: %s\n", str);
            close(fd[0]);
            write(fd[1], str, strlen(str)+1);
            kill(ppid, SIGSTOP);
        }
    }
}