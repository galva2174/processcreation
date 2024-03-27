#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

// Function to display the tree structure of processes and threads
void displayTree(char *taskName, int level, pid_t pid, pthread_t tid) 
{
    for (int i = 0; i < level; i++) 
    {
        printf("  ");
    }
    printf("|- Task Name: %s, State: Running, PID: %d, TID: %lu\n", taskName, pid, tid);
}

// Function to be executed by each thread
void *threadFunction(void *arg) 
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    displayTree((char *)arg, 2, pid, tid);
    pthread_exit(NULL);
}

int main() 
{
    pid_t pid;
    pthread_t tid;
    int num_processes = 3; // Number of child processes
    int num_threads = 2; // Number of threads per process

    // Parent process information
    pid = getpid();
    tid = pthread_self();
    displayTree("Parent", 0, pid, tid);

    // Forking child processes
    for (int i = 0; i < num_processes; i++) 
    {
        pid = fork();

        if (pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) 
        { // Child process
            pid_t child_pid = getpid();
            tid = pthread_self();
            displayTree("Child", 1, child_pid, tid);

            // Create threads in the child process
            pthread_t threads[num_threads];
            for (int j = 0; j < num_threads; j++) 
            {
                char threadName[20];
                sprintf(threadName, "Thread %d", j + 1);
                pthread_create(&threads[j], NULL, threadFunction, (void *)threadName);
            }

            // Wait for threads to finish
            for (int j = 0; j < num_threads; j++) 
            {
                pthread_join(threads[j], NULL);
            }

            exit(EXIT_SUCCESS);
        }
    }

    // Wait for child processes to finish
    for (int i = 0; i < num_processes; i++) 
    {
        wait(NULL);
    }

    return 0;
}
