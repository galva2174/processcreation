This project is a simple C program that demonstrates how to create and visualize a tree of processes and threads. The program uses fork() to create child processes and pthread_create() to create threads within each child process.

## Features
Parent Process: The main process creates several child processes.
Child Processes: Each child process creates threads.
Thread Creation: Each child process spawns multiple threads, and the relationships are displayed in a tree structure.
## How It Works
The program creates:
1 parent process.
3 child processes (using fork()).
2 threads in each child process (using pthread_create()).
Each process and thread prints its Process ID (PID) and Thread ID (TID) in a hierarchical format.
