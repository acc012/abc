#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int arr[50], i;

    printf("Received array elements:\n");
    for(i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);  // Convert argv[i] to int and store in arr[]
        printf("%d ", arr[i - 1]);
    }
    printf("\n");

    printf("Reverse array:\n");
    for(i = argc - 1; i >= 1; i--)
    {
        printf("%d ", arr[i - 1]);  // Use arr directly, no need to convert again
    }
    printf("\n");

    return 0;
}
