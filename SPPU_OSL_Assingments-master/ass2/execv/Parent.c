#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sortarray(int arr[], int n)
{
    int temp;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(arr[i] > arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main()
{
    int arr[50], n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    sortarray(arr, n);

    // Prepare command-line arguments for execve
    char *args[n + 2];
    args[0] = "./child";
    for(int i = 0; i < n; i++)
    {
        asprintf(&args[i + 1], "%d", arr[i]);
    }
    args[n + 1] = NULL;

    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return 1;
    }

    if(pid == 0)
    {
        // Child process: execute "child" program with the sorted array
        execve(args[0], args, NULL);
        perror("execve");
        exit(1);
    }
    else
    {
        // Parent process: wait for the child process to finish
        wait(NULL);
    }

    // Free allocated memory
    for(int i = 1; i <= n; i++)
    {
        free(args[i]);
    }

    return 0;
}
