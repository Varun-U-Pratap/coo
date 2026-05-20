#include <stdio.h>
#include <string.h>

#define MAX 50

int inFrames(int frames[], int n, int page) {
    for (int i = 0; i < n; i++)
        if (frames[i] == page) return 1;
    return 0;
}

void printFrames(int frames[], int n, int page, int hit) {
    printf("  Page %2d │ ", page);
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) printf("  _ ");
        else                  printf(" %2d ", frames[i]);
    }
    printf("│ %s\n", hit ? "HIT " : "MISS ✗");
}

void printHeader(int n) {
    printf("  Page    │");
    for (int i = 0; i < n; i++) printf(" F%d ", i + 1);
    printf("│ Result\n");
    printf("  ─────────┼");
    for (int i = 0; i < n; i++) printf("────");
    printf("┼────────\n");
}

void fifo(int pages[], int np, int nf) {
    int frames[MAX], idx = 0, faults = 0;
    memset(frames, -1, sizeof(frames));

    printf("\n╔══════════════════════════════╗\n");
    printf("║        FIFO Algorithm        ║\n");
    printf("╚══════════════════════════════╝\n");
    printHeader(nf);

    for (int i = 0; i < np; i++) {
        int hit = inFrames(frames, nf, pages[i]);
        if (!hit) {
            frames[idx % nf] = pages[i];
            idx++;
            faults++;
        }
        printFrames(frames, nf, pages[i], hit);
    }
    printf("  ─────────┴");
    for (int i = 0; i < nf; i++) printf("────");
    printf("┴────────\n");
    printf("  Total Page Faults: %d / %d\n", faults, np);
}

int farthestUse(int pages[], int np, int frames[], int nf, int cur) {
    int farthest = -1, idx = 0;
    for (int i = 0; i < nf; i++) {
        int j;
        for (j = cur + 1; j < np; j++)
            if (pages[j] == frames[i]) break;
        if (j == np) return i;    
        if (j > farthest) { farthest = j; idx = i; }
    }
    return idx;
}

void optimal(int pages[], int np, int nf) {
    int frames[MAX], filled = 0, faults = 0;
    memset(frames, -1, sizeof(frames));

    printf("\n╔══════════════════════════════╗\n");
    printf("║      Optimal Algorithm       ║\n");
    printf("╚══════════════════════════════╝\n");
    printHeader(nf);

    for (int i = 0; i < np; i++) {
        int hit = inFrames(frames, nf, pages[i]);
        if (!hit) {
            if (filled < nf) frames[filled++] = pages[i];
            else             frames[farthestUse(pages, np, frames, nf, i)] = pages[i];
            faults++;
        }
        printFrames(frames, nf, pages[i], hit);
    }
    printf("  ─────────┴");
    for (int i = 0; i < nf; i++) printf("────");
    printf("┴────────\n");
    printf("  Total Page Faults: %d / %d\n", faults, np);
}

int main() {
    int pages[MAX], np, nf;

    printf("┌─────────────────────────────────┐\n");
    printf("│  Page Replacement: FIFO/Optimal │\n");
    printf("└─────────────────────────────────┘\n");

    printf("Number of frames  : "); scanf("%d", &nf);
    printf("Number of pages   : "); scanf("%d", &np);
    printf("Enter page string : ");
    for (int i = 0; i < np; i++) scanf("%d", &pages[i]);

    fifo(pages, np, nf);
    optimal(pages, np, nf);
    return 0;
}
