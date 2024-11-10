#include <stdio.h>
#include <stdlib.h>

#define MAX 199

void scan(int request[], int n, int head);

int main() {
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    int head;
    printf("Enter head position: ");
    scanf("%d", &head);

    scan(request, n, head);
    return 0;
}

void scan(int request[], int n, int head) {
    int seek_count = 0;
    int seek_seq[MAX];
    
    // Copy the request array and sort it
    int temp[MAX];
    for (int i = 0; i < n; i++) {
        temp[i] = request[i];
    }

    // Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    // Find the first request greater than the head
    int index = 0;
    while (index < n && temp[index] < head) {
        index++;
    }

    // Move in the right direction first (to the end of the disk)
    for (int i = index; i < n; i++) {
        seek_seq[seek_count++] = temp[i];
    }

    // Move in the left direction after reaching the end of the right direction
    for (int i = index - 1; i >= 0; i--) {
        seek_seq[seek_count++] = temp[i];
    }

    // Calculate the total distance using the simplified formula
    int total_dist = abs(MAX - head) + abs(MAX - temp[0]);

    // Print the seek sequence
    printf("Seek sequence: ");
    for (int i = 0; i < seek_count; i++) {
        printf("-> %d ", seek_seq[i]);
    }

    // Print total distance
    printf("\nTotal distance: %d\n", total_dist);
}
