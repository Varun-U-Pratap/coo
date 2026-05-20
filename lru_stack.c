#include <stdio.h>

#define MAX 50

int stack[MAX], top = -1;

int  stackSize()             { return top + 1; }
int  inStack(int p)          { for(int i=0;i<=top;i++) if(stack[i]==p) return 1; return 0; }
void removeFromStack(int p)  {
    int i;
    for (i = 0; i <= top; i++) if (stack[i] == p) break;
    for (; i < top; i++) stack[i] = stack[i + 1];
    top--;
}
void push(int p)             { stack[++top] = p; }

void printStack(int nf, int page, int hit) {
    printf("  Page %2d │ [", page);
    int sz = stackSize();
    for (int i = 0; i < nf - sz; i++) printf("  _ ");
    for (int i = 0; i < sz; i++)      printf(" %2d ", stack[i]);
    printf("] │ %s\n", hit ? "HIT " : "MISS ✗");
}

void lru(int pages[], int np, int nf) {
    int faults = 0;

    printf("\n╔═══════════════════════════════════╗\n");
    printf("║   LRU Algorithm  (Stack-based)    ║\n");
    printf("╚═══════════════════════════════════╝\n");
    printf("  Stack: bottom → top  (top = most recent)\n");
    printf("  Page    │ Frames%-*s│ Result\n", (nf*4-4), "");
    printf("  ─────────┼");
    for (int i = 0; i < nf; i++) printf("────");
    printf("──┼────────\n");

    for (int i = 0; i < np; i++) {
        int hit = inStack(pages[i]);
        if (hit) {
            removeFromStack(pages[i]);   
        } else {
            if (stackSize() == nf)
                removeFromStack(stack[0]); 
            faults++;
        }
        push(pages[i]);
        printStack(nf, pages[i], hit);
    }
    printf("  ─────────┴");
    for (int i = 0; i < nf; i++) printf("────");
    printf("──┴────────\n");
    printf("  Total Page Faults: %d / %d\n", faults, np);
}

int main() {
    int pages[MAX], np, nf;

    printf("┌──────────────────────────────────┐\n");
    printf("│  LRU Page Replacement via Stack  │\n");
    printf("└──────────────────────────────────┘\n");

    printf("Number of frames  : "); scanf("%d", &nf);
    printf("Number of pages   : "); scanf("%d", &np);
    printf("Enter page string : ");
    for (int i = 0; i < np; i++) scanf("%d", &pages[i]);

    lru(pages, np, nf);
    return 0;
}
