#include <stdio.h>
#define MAX 10
#define RESOURCE_TYPES 3

void calculateNeed(int need[MAX][RESOURCE_TYPES], int max[MAX][RESOURCE_TYPES], int allocation[MAX][RESOURCE_TYPES], int numProcesses, int numResources) {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafeState(int processes, int resources, int available[], int max[][RESOURCE_TYPES], int allot[][RESOURCE_TYPES], int safeSeq[]) {
    int finish[processes], work[resources];
    int count = 0;
    for (int i = 0; i < processes; i++) {
        finish[i] = 0;
    }

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }
    while (count < processes) {
        int found = 0;
        for (int p = 0; p < processes; p++) {
            if (finish[p] == 0) {
                int canAllocate = 1;
                for (int r = 0; r < resources; r++) {
                    if (max[p][r] - allot[p][r] > work[r]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int r = 0; r < resources; r++) {
                        work[r] += allot[p][r];
                    }
                    safeSeq[count++] = p;
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int numProcesses, numResources;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    int max[numProcesses][numResources], allocation[numProcesses][numResources], available[numResources];
    int need[numProcesses][numResources];
    int safeSeq[numProcesses];

    printf("\nEnter the maximum resources required for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nEnter the resources currently allocated to each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("\nEnter the available resources:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    calculateNeed(need, max, allocation, numProcesses, numResources);

    if (isSafeState(numProcesses, numResources, available, max, allocation, safeSeq)) {
        printf("\nThe system is in a safe state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < numProcesses; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("\nThe system is not in a safe state.\n");
    }

    return 0;
}
