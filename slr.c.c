#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

// Define the parsing table
char action[11][4][10] = {
    {"s5", "s4", "", ""},
    {"", "", "", "acc"},
    {"", "r2", "s7", "r2"},
    {"", "r4", "r4", "r4"},
    {"s5", "s4", "", ""},
    {"", "r6", "r6", "r6"},
    {"s5", "s4", "", ""},
    {"s5", "s4", "", ""},
    {"", "s6", "", ""},
    {"", "r1", "s7", "r1"},
    {"", "r3", "r3", "r3"}
};

int goto_table[11][3] = {
    {1, 2, 3},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, 8, 3},
    {-1, -1, -1},
    {-1, -1, 9},
    {-1, -1, 10},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1}
};

int stack[STACK_SIZE];
int top = -1;

void push(int state) {
    stack[++top] = state;
}

int pop() {
    return stack[top--];
}

int main() {
    char input[100];
    printf("Enter an arithmetic expression (end with $): ");
    scanf("%s", input);

    push(0); // Start with initial state 0
    int ip = 0; // Input pointer

    while (1) {
        int state = stack[top];
        char symbol = input[ip];

        int col;
        if (symbol == 'id')
            col = 0;
        else if (symbol == '+')
            col = 1;
        else if (symbol == '*')
            col = 2;
        else if (symbol == '$')
            col = 3;
        else {
            printf("Error in input\n");
            exit(1);
        }

        char *act = action[state][col];
        if (act[0] == 's') {
            // Shift
            int nextState = atoi(&act[1]);
            push(nextState);
            ip++;
        } else if (act[0] == 'r') {
            // Reduce
            int rule = atoi(&act[1]);
            int ntlen;
            if (rule == 1) ntlen = 1;
            else if (rule == 2 || rule == 3 || rule == 4 || rule == 6) ntlen = 3;
            else ntlen = 5;
            for (int i = 0; i < ntlen; i++) {
                pop();
            }
            int newState = goto_table[stack[top]][rule - 1];
            push(newState);
        } else if (strcmp(act, "acc") == 0) {
            printf("String accepted\n");
            break;
        } else {
            printf("Error in parsing\n");
            exit(1);
        }
    }

    return 0;
}

/*
E -> E + T | T
T -> T * F | F
F -> ( E ) | id

State 0:
    Action:
        id   -> shift 5
        (    -> shift 4
    Goto:
        E    -> 1
        T    -> 2
        F    -> 3

State 1:
    Action:
        +    -> shift 6
        $    -> accept

State 2:
    Action:
        +    -> reduce T -> F
        *    -> shift 7
        $    -> reduce T -> F

State 3:
    Action:
        +    -> reduce F -> id
        *    -> reduce F -> id
        $    -> reduce F -> id

State 4:
    Action:
        id   -> shift 5
        (    -> shift 4
    Goto:
        E    -> 8
        T    -> 2
        F    -> 3

State 5:
    Action:
        +    -> reduce F -> id
        *    -> reduce F -> id
        $    -> reduce F -> id

State 6:
    Action:
        id   -> shift 5
        (    -> shift 4
    Goto:
        T    -> 9
        F    -> 3

State 7:
    Action:
        id   -> shift 5
        (    -> shift 4
    Goto:
        F    -> 10

State 8:
    Action:
        +    -> reduce E -> T
        $    -> reduce E -> T

State 9:
    Action:
        +    -> reduce T -> T * F
        *    -> shift 7
        $    -> reduce T -> T * F

State 10:
    Action:
        +    -> reduce F -> ( E )
        *    -> reduce F -> ( E )
        $    -> reduce F -> ( E )
*/ 
