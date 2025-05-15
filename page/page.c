#include <stdio.h>
#include <stdlib.h>

int findOptimal(int pages[], int n, int frame[], int frameSize, int index) {
    int farthest = index, pos = -1;
    for (int i = 0; i < frameSize; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frame[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i;
    }
    return (pos == -1) ? 0 : pos;
}

void fifo(int pages[], int n, int frameSize) {
    int frame[frameSize];
    int front = 0, pageFaults = 0;
    int count = 0;

    printf("\nFIFO Page Replacement:\n");

    for (int i = 0; i < frameSize; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frame[front] = pages[i];
            front = (front + 1) % frameSize;
            pageFaults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

void lru(int pages[], int n, int frameSize) {
    int frame[frameSize], count[frameSize];
    int time = 0, pageFaults = 0;

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < frameSize; i++) {
        frame[i] = -1;
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0, pos = 0, min = time;

        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                count[j] = time++;
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < frameSize; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
                if (count[j] < min) {
                    min = count[j];
                    pos = j;
                }
            }
            frame[pos] = pages[i];
            count[pos] = time++;
            pageFaults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

void optimal(int pages[], int n, int frameSize) {
    int frame[frameSize];
    int pageFaults = 0;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < frameSize; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = -1;
            for (int j = 0; j < frameSize; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                pos = findOptimal(pages, n, frame, frameSize, i + 1);
            }

            frame[pos] = pages[i];
            pageFaults++;
        }

        printf("Frames: ");
        for (int j = 0; j < frameSize; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}

int main() {
    int n, frameSize, choice;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frameSize);

    do {
        printf("\n--- Page Replacement Algorithms ---\n");
        printf("1. FIFO\n2. LRU\n3. Optimal\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                fifo(pages, n, frameSize);
                break;
            case 2:
                lru(pages, n, frameSize);
                break;
            case 3:
                optimal(pages, n, frameSize);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
