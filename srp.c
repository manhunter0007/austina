#include<stdio.h>
#include<string.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

void check();

int main() {
    puts("grammar is E->E+E\n E->E*E\n E->(E)\n E->id");
    puts("enter input string");
    scanf("%s", a);
    c = strlen(a);
    strcpy(act, "SHIFT->");
    puts("stack\t input\t action");

    // Initialize i and j
    i = 0;
    j = 0;

    for (k = 0; i < c && j < c; k++, i++, j++) {
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i] = a[j];
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            a[j] = ' ';
            a[j + 1] = ' ';
            printf("\n$%s\t%s$\t%sid", stk, a, act);
            check();
        } else {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbols", stk, a, act);
            check();
        }
    }

    if (strcmp(stk, "E") == 0)
        printf("\nAccepted\n");
    else
        printf("\nRejected\n");

    return 0;
}

void check() {
    strcpy(ac, "REDUCE TO E");
    
    // Reduction rules
    while (strlen(stk) > 1) {
        int len = strlen(stk);
        
        // E -> id reduction
        for (z = 0; z < len - 1; z++) {
            if (stk[z] == 'i' && stk[z + 1] == 'd') {
                stk[z] = 'E';
                stk[z + 1] = '\0';
                printf("\n$%s\t%s$\t%s", stk, a, ac);
                return;
            }
        }
        
        // E -> E + E reduction
        for (z = 0; z < len - 2; z++) {
            if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
                stk[z] = 'E';
                stk[z + 1] = '\0';
                stk[z + 2] = '\0';
                printf("\n$%s\t%s$\t%s", stk, a, ac);
                return;
            }
        }
        
        // E -> E * E reduction
        for (z = 0; z < len - 2; z++) {
            if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
                stk[z] = 'E';
                stk[z + 1] = '\0';
                stk[z + 2] = '\0';
                printf("\n$%s\t%s$\t%s", stk, a, ac);
                return;
            }
        }
        
        // E -> (E) reduction
        if (stk[0] == '(' && stk[len - 1] == ')') {
            stk[0] = 'E';
            stk[1] = '\0';
            stk[len - 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            return;
        }
        
        // If no reduction applies, break the loop
        break;
    }
}
