#include <stdio.h>

int main() {
    int numProcesses, numResources;

    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    
    printf("Enter number of resources: ");
    scanf("%d", &numResources);

    int allocationMatrix[numProcesses][numResources];
    int maxMatrix[numProcesses][numResources];
    int available[numResources];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            scanf("%d", &allocationMatrix[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < numProcesses; i++)
        for (int j = 0; j < numResources; j++)
            scanf("%d", &maxMatrix[i][j]);

    printf("Enter Available Resources:\n");
    for (int j = 0; j < numResources; j++)
        scanf("%d", &available[j]);

    int isFinished[numProcesses], safeSequence[numProcesses], index = 0;
    for (int k = 0; k < numProcesses; k++) {
        isFinished[k] = 0;
    }

    int needMatrix[numProcesses][numResources];
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++)
            needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
    }

    // Finding the safe sequence using Banker's algorithm
    for (int k = 0; k < numProcesses; k++) {
        for (int i = 0; i < numProcesses; i++) {
            if (isFinished[i] == 0) {
                int flag = 0;
                for (int j = 0; j < numResources; j++) {
                    if (needMatrix[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    safeSequence[index++] = i;
                    for (int y = 0; y < numResources; y++)
                        available[y] += allocationMatrix[i][y];
                    isFinished[i] = 1;
                }
            }
        }
    }

    // Checking if the system is in a safe state
    int flag = 1;
    for (int i = 0; i < numProcesses; i++) {
        if (isFinished[i] == 0) {
            flag = 0;
            printf("The system is not safe.\n");
            break;
        }
    }

    if (flag == 1) {
        printf("SAFE Sequence: ");
        for (int i = 0; i < numProcesses - 1; i++)
            printf("P%d -> ", safeSequence[i] + 1);
    }
        printf("P%d\n", safeSequence[numProcesses - 1] + 1);

    return 0;
}
