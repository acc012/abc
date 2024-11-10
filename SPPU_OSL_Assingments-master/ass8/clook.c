#include <stdio.h>
#include <stdlib.h>

void clook(int request[], int n, int head);

int main() {
    int n, head;

    printf("Enter number of requests: ");
    scanf("%d", &n);
    int request[n];

    printf("Enter the head position: ");
    scanf("%d", &head);

    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    clook(request, n, head);

    return 0;
}

void clook(int request[], int n, int head) {
    int seek_seq[n];
    int seek_count = 0;
    int total_dist = 0;

    // Copy and sort the request array
    int temp[n];
    for (int i = 0; i < n; i++) {
        temp[i] = request[i];
    }

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

    // Service the requests to the right of the head
    for (int i = index; i < n; i++) {
        seek_seq[seek_count++] = temp[i];
    }

    // Wrap around to the beginning
    for (int i = 0; i < index; i++) {
        seek_seq[seek_count++] = temp[i];
    }

    // Calculate the total distance
    total_dist = abs(temp[n-1] - head) + abs(temp[n-1] - temp[0]) + abs(temp[index - 1] - temp[0]);

    // Print the seek sequence
    printf("Seek sequence: ");
    for (int i = 0; i < seek_count; i++) {
        printf("-> %d ", seek_seq[i]);
    }
    printf("\nTotal distance: %d\n", total_dist);
}
