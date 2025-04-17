#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define RESOURCE_TYPES 3

// Function to check whether a cycle is present in the graph
int isCyclic(int graph[MAX][MAX], int numProcesses) {
    int visited[MAX] = {0};   // visited[] keeps track of visited processes
    int recStack[MAX] = {0};  // recStack[] is used for detecting back edges in DFS

    // Helper function for DFS traversal
    int dfs(int graph[MAX][MAX], int process, int visited[MAX], int recStack[MAX]) {
        if (recStack[process])
            return 1;  // Found a cycle

        if (visited[process])
            return 0;  // Already visited, no cycle here

        visited[process] = 1;
        recStack[process] = 1;

        // Visit all adjacent processes (neighbors in the graph)
        for (int i = 0; i < numProcesses; i++) {
            if (graph[process][i] && dfs(graph, i, visited, recStack))
                return 1;  // Cycle detected
        }

        recStack[process] = 0;  // Backtrack
        return 0;
    }

    // Check for cycles in all processes
    for (int i = 0; i < numProcesses; i++) {
        if (!visited[i]) {
            if (dfs(graph, i, visited, recStack))
                return 1;  // Cycle found
        }
    }
    return 0;  // No cycle found
}

// Function to detect deadlock by building the Wait-For graph
int detectDeadlock(int numProcesses, int allocation[MAX][RESOURCE_TYPES], int need[MAX][RESOURCE_TYPES], int numResources) {
    int graph[MAX][MAX] = {0}; // Initialize the graph with 0s (no edges)

    // Build the Wait-For graph
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numProcesses; j++) {
            if (i != j) {
                int canAllocate = 1;
                for (int r = 0; r < numResources; r++) {
                    if (need[i][r] > allocation[j][r]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    graph[i][j] = 1; // i is waiting for j
                }
            }
        }
    }

    // Detect cycles in the Wait-For graph
    if (isCyclic(graph, numProcesses)) {
        printf("\nDeadlock detected in the system.\n");
        return 1;  // Deadlock detected
    }
    printf("\nNo deadlock detected.\n");
    return 0;  // No deadlock
}

// Function to calculate the Need matrix
void calculateNeed(int need[MAX][RESOURCE_TYPES], int max[MAX][RESOURCE_TYPES], int allocation[MAX][RESOURCE_TYPES], int numProcesses, int numResources) {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int main() {
    int numProcesses, numResources;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    int max[numProcesses][numResources], allocation[numProcesses][numResources], available[numResources];
    int need[numProcesses][numResources];

    // Input the maximum resources required for each process
    printf("\nEnter the maximum resources required for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input the resources currently allocated to each process
    printf("\nEnter the resources currently allocated to each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input the available resources
    printf("\nEnter the available resources:\n");
    for (int i = 0; i < numResources; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate the Need matrix
    calculateNeed(need, max, allocation, numProcesses, numResources);

    // Detect deadlock
    detectDeadlock(numProcesses, allocation, need, numResources);

    return 0;
}
