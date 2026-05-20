#include <stdio.h>

// Function to implement First Fit allocation
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[10];
    int blocks[10];
    
    // Copy the block sizes to avoid altering the original array for other algorithms
    for(int i = 0; i < m; i++) blocks[i] = blockSize[i];
    for(int i = 0; i < n; i++) allocation[i] = -1;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(blocks[j] >= processSize[i]) {
                allocation[i] = j;
                blocks[j] -= processSize[i];
                break;
            }
        }
    }
    
    printf("\n--- First Fit Visual Output ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Function to implement Best Fit allocation
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[10];
    int blocks[10];
    
    for(int i = 0; i < m; i++) blocks[i] = blockSize[i];
    for(int i = 0; i < n; i++) allocation[i] = -1;
    
    for(int i = 0; i < n; i++) {
        int bestIdx = -1;
        for(int j = 0; j < m; j++) {
            if(blocks[j] >= processSize[i]) {
                if(bestIdx == -1 || blocks[bestIdx] > blocks[j]) {
                    bestIdx = j;
                }
            }
        }
        
        if(bestIdx != -1) {
            allocation[i] = bestIdx;
            blocks[bestIdx] -= processSize[i];
        }
    }
    
    printf("\n--- Best Fit Visual Output ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

// Function to implement Worst Fit allocation
void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[10];
    int blocks[10];
    
    for(int i = 0; i < m; i++) blocks[i] = blockSize[i];
    for(int i = 0; i < n; i++) allocation[i] = -1;
    
    for(int i = 0; i < n; i++) {
        int worstIdx = -1;
        for(int j = 0; j < m; j++) {
            if(blocks[j] >= processSize[i]) {
                if(worstIdx == -1 || blocks[worstIdx] < blocks[j]) {
                    worstIdx = j;
                }
            }
        }
        
        if(worstIdx != -1) {
            allocation[i] = worstIdx;
            blocks[worstIdx] -= processSize[i];
        }
    }
    
    printf("\n--- Worst Fit Visual Output ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;
    int blockSize[10], processSize[10];
    
    printf("Enter number of memory blocks: "); 
    scanf("%d", &m);
    printf("Enter sizes of blocks:\n");
    for(int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }
    
    printf("\nEnter number of processes: "); 
    scanf("%d", &n);
    printf("Enter sizes of processes:\n");
    for(int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    
    // Execute and display all three contiguous allocation strategies
    firstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    worstFit(blockSize, m, processSize, n);
    
    return 0;
}