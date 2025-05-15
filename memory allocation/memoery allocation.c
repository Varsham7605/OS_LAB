#include <stdio.h>

struct Block {

    int size;

    int allocated;

};



struct File {

    int size;

    int block_no;

};



void resetBlocks(struct Block blocks[], int n) {

    for (int i = 0; i < n; i++) {

        blocks[i].allocated = 0;

    }

}



void firstFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {

    printf("\n\tMemory Management Scheme – First Fit\n");

    printf("File_no:\tFile_size\tBlock_no:\tBlock_size:\n");



    for (int i = 0; i < n_files; i++) {

        files[i].block_no = -1;

        for (int j = 0; j < n_blocks; j++) {

            if (!blocks[j].allocated && blocks[j].size >= files[i].size) {

                files[i].block_no = j + 1;

                blocks[j].allocated = 1;

                printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, files[i].size, j + 1, blocks[j].size);

                break;

            }

        }

        if (files[i].block_no == -1) {

            printf("%d\t\t%d\t\t_\t\t_\n", i + 1, files[i].size);

        }

    }

}



void bestFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {

    printf("\n\tMemory Management Scheme – Best Fit\n");

    printf("File_no:\tFile_size\tBlock_no:\tBlock_size:\n");



    for (int i = 0; i < n_files; i++) {

        int bestIdx = -1;

        for (int j = 0; j < n_blocks; j++) {

            if (!blocks[j].allocated && blocks[j].size >= files[i].size) {

                if (bestIdx == -1 || blocks[j].size < blocks[bestIdx].size) {

                    bestIdx = j;

                }

            }

        }

        if (bestIdx != -1) {

            blocks[bestIdx].allocated = 1;

            files[i].block_no = bestIdx + 1;

            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, files[i].size, bestIdx + 1, blocks[bestIdx].size);

        } else {

            printf("%d\t\t%d\t\t_\t\t_\n", i + 1, files[i].size);

        }

    }

}



void worstFit(struct Block blocks[], int n_blocks, struct File files[], int n_files) {

    printf("\n\tMemory Management Scheme – Worst Fit\n");

    printf("File_no:\tFile_size\tBlock_no:\tBlock_size:\n");



    for (int i = 0; i < n_files; i++) {

        int worstIdx = -1;

        for (int j = 0; j < n_blocks; j++) {

            if (!blocks[j].allocated && blocks[j].size >= files[i].size) {

                if (worstIdx == -1 || blocks[j].size > blocks[worstIdx].size) {

                    worstIdx = j;

                }

            }

        }

        if (worstIdx != -1) {

            blocks[worstIdx].allocated = 1;

            files[i].block_no = worstIdx + 1;

            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, files[i].size, worstIdx + 1, blocks[worstIdx].size);

        } else {

            printf("%d\t\t%d\t\t_\t\t_\n", i + 1, files[i].size);

        }

    }

}



int main() {

    int n_blocks, n_files, choice;



    printf("Memory Management Scheme\n");



    printf("Enter the number of blocks: ");

    scanf("%d", &n_blocks);



    printf("Enter the number of files: ");

    scanf("%d", &n_files);



    struct Block blocks[n_blocks];

    struct File files[n_files];



    printf("\nEnter the size of the blocks:\n");

    for (int i = 0; i < n_blocks; i++) {

        printf("Block %d: ", i + 1);

        scanf("%d", &blocks[i].size);

        blocks[i].allocated = 0;

    }



    printf("Enter the size of the files:\n");

    for (int i = 0; i < n_files; i++) {

        printf("File %d: ", i + 1);

        scanf("%d", &files[i].size);

    }



    do {

        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);



        resetBlocks(blocks, n_blocks); // Reset block allocation before each strategy



        switch (choice) {

            case 1:

                firstFit(blocks, n_blocks, files, n_files);

                break;

            case 2:

                bestFit(blocks, n_blocks, files, n_files);

                break;

            case 3:

                worstFit(blocks, n_blocks, files, n_files);

                break;

            case 4:

                printf("\nExiting...\n");

                break;

            default:

                printf("Invalid choice.\n");

        }

    } while (choice != 4);



    return 0;

}
