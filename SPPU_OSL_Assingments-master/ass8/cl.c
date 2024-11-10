#include<stdio.h>
#include<stdlib.h>

#define MAX 199

void clook(int request[],int n, int head){
    int seek_count =0;
    int seek_seq[MAX];

    int temp[MAX];
    for(int i=0; i<n; i++){
        temp[i] = request[i];
    }

    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(temp[j] > temp[j+1]){
                int swap = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = swap;
            }
        }
    }
    int index = 0;
    while( index < n && temp[index] < head ){
        index++;
    }

    for(int i=index; i<n; i++){
        seek_seq[seek_count++] = temp[i];
    }

    for(int i=index-1; i>=0; i--){
        seek_seq[seek_count++] = temp[i];
    }

    int total_dist = abs(temp[n-1] - head) + abs(temp[0] - head) + abs(temp[n-1] - temp[0]);

    printf("seek sequence: ");
    for(int i =0; i<seek_count; i++){
          printf("%d ->", seek_seq[i]);
    }
    printf("total distance travelled:%d ", total_dist);
}

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
