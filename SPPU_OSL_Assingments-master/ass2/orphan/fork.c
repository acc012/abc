#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of integers to sort: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int pid = fork();

    if (pid > 0) {  // Parent process
        printf("Parent process is sorting the array.\n");
        bubbleSort(arr, n);
        printf("Sorted array by parent process: ");
        printArray(arr, n);

        // Wait for child process to prevent it from becoming a zombie
        wait(NULL);
        printf("Child process has completed and parent process exits.\n");

    } else if (pid == 0) {  // Child process
        printf("Child process is sorting the array.\n");
        bubbleSort(arr, n);
        printf("Sorted array by child process: ");
        printArray(arr, n);

        // Demonstrating orphan state by sleeping for some time
        printf("Child process going to sleep to become orphan.\n");
        sleep(5);
        printf("Child process wakes up and exits.\n");
    } else {
        printf("Fork failed.\n");
        return 1;
    }

    return 0;
}
