#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 199

void sstf(int request[], int n, int head){
    int seek_seq[n];
    int seek_count = 0;
    int total_dist = 0;
    int visited[MAX] = {false};

    for(int i=0; i<n; i++){
        int min = MAX;
        int index = -1;
        for(int j=0; j<n; j++){
            if(!visited[j]){
                int dist = abs(request[j] - head);

                if(dist < min){
                    min = dist;
                    index = j;
                }
            }
        }
        if(index != -1){
            visited[index] = true;
            seek_seq[seek_count++] = request[index];
            total_dist += abs(request[index] - head);
            head = request[index]; 
        }
    } 
    printf("sequence is:");
    for(int i=0; i<seek_count;i++){
        printf("%d ->", seek_seq[i]);
    }
    printf("\nTotal distance travelled is: %d",total_dist);

}

int main(){
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the position of head: ");
    scanf("%d", &head);
    int request[n];
    
    printf("Enter the requests: ");
    for(int i=0; i<n; i++){
        scanf("%d", &request[i]);
    }
    sstf(request, n, head);

    return 0;
    

}