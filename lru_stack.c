#include <stdio.h>

int findPage(int stack[], int size, int page) {
    for (int i = 0; i < size; i++) if (stack[i] == page) return i;
    return -1;
}

int main() {
    int stack[10], n, frames, pages[50], top = 0;
    printf("Enter number of pages and frames: ");
    scanf("%d %d", &n, &frames);
    printf("Enter the page reference string: ");
    for(int i=0; i<n; i++) scanf("%d", &pages[i]);

    printf("\n--- LRU Stack Visualization ---\n");
    for (int i = 0; i < n; i++) {
        int index = findPage(stack, top, pages[i]);
        if (index != -1) {
            // Page exists, shift up and push to top
            for (int j = index; j < top - 1; j++) stack[j] = stack[j+1];
            stack[top - 1] = pages[i];
        } else {
            // Page fault
            if (top < frames) {
                stack[top++] = pages[i];
            } else {
                for (int j = 0; j < frames - 1; j++) stack[j] = stack[j+1]; // Drop bottom
                stack[frames - 1] = pages[i];
            }
        }
        printf("Ref %d -> Stack (Bottom to Top): [", pages[i]);
        for(int j=0; j<top; j++) printf(" %d ", stack[j]);
        printf("]\n");
    }
    return 0;
}