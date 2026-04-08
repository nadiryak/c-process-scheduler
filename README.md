# 🖥️ C-Process-Scheduler
#NOTE: This readme is not complete and that for som stuff i'm working in it, so i've studies, when i find time i code so the readme it's not complet but it still usefull

This project is a simple simulation of an Operating System's process scheduler. 

## 📌 Context
I decided to build this project to **refresh my C programming skills**. It had been a while since I last worked with low-level concepts, so I wanted to solidify my understanding of **pointers** and **dynamic memory management** before moving forward.

## 🛠️ How it works
The scheduler uses a **doubly linked list** to store processes. 
Think of it like a chain: each "Process" (a node) knows who is before it and who is after it. This makes it easy to add or remove tasks in the middle of the list.

### Code Highlight: Adding a Process
To add a new task, the program "walks" through the list until it finds the end, then hooks up the new process:

```c
// Moving to the end of the list
Process* actuel = tete;
while (actuel->suivant != NULL) {
    actuel = actuel->suivant;
}

// Linking the new process
actuel->suivant = nv_p;
nv_p->precedent = actuel; 
```

## 🚀 How to Compile and Run
I use specific flags (`-Wall -Wextra`) to make sure the code is clean and has no hidden warnings.

1. Compile:
```bash
gcc -Wall -Wextra -g main.c scheduler.c -o test_scheduler
```

2. Run:
```bash
./test_scheduler
```

## 📋 Example Output
When you run the test, you will see the list of processes and their priorities:
```
Processus ID: 1 | Priority: 10
Processus ID: 2 | Priority: 5
Processus ID: 3 | Priority: 8
```

## 🛡️ Checking for Memory Leaks (Valgrind)
In C, if you open a door (`malloc`), you must close it (`free`). I used Valgrind to make sure my program doesn't "leak" memory.

Command used:
```bash
valgrind --leak-check=full ./test_scheduler
```

The result is perfect:
```
== HEAP SUMMARY:
==    in use at exit: 0 bytes in 0 blocks
==    total heap usage: 4 allocs, 4 frees, 1,120 bytes allocated
== 
== All heap blocks were freed -- no leaks are possible
```

This confirms that every byte I asked for was correctly returned to the system.
