# 🖥️ C-Process-Scheduler

> **NOTE:** This readme is not complete — I'm still working on the project between classes. But it's useful enough to understand what's going on.

This project is a simulation of an Operating System's process scheduler, written in C.

---

## 📌 Context

I built this to **practice C and low-level concepts** — pointers, dynamic memory, doubly linked lists. The kind of stuff that looks simple but gets real when you actually implement it.

---

## 🛠️ How it works

Each process has an `id`, a `priority`, and an `execution_time`. They're stored in a **doubly linked list** — each node knows who's before it and who's after it.

```c
typedef struct Process {
    int id;
    int priority;
    int execution_time;
    struct Process *suivant;   // next
    struct Process *precedent; // previous
} Process;
```

The project implements **two different scheduling approaches**, which I think is the most interesting part.

---

## ⚙️ Two Scheduling Approaches

### Approach 1 — Sorted insertion + extract from head

Processes are inserted in sorted order by priority using `inserer()`. So the list is always ready — the most urgent process is always at the front.

When it's time to execute, we just grab the head with `extraire_premiere_elt()`.

```c
// inserer() walks the list to find the right spot
// so no matter the insertion order, the list stays sorted
file = inserer(file, create_process(1, 10, 50));
file = inserer(file, create_process(2, 25, 100)); // this will end up first
file = inserer(file, create_process(3,  5, 80));  // this will end up last
```

Cost: O(n) at insertion, O(1) at extraction.

---

### Approach 2 — FIFO insertion + extract best each time

Processes arrive in order and are added to the end with `ajouter_process_a_la_fin()`. No sorting. The list keeps the arrival order.

When we need to run a process, `extraire_meilleure_priorite()` scans the whole list, finds the highest priority, **unplugs it cleanly**, and reconnects the surrounding nodes.

```c
// the "wagon" analogy: we unhook the best node
// and re-link its neighbors directly to each other
if (max->precedent != NULL)
    max->precedent->suivant = max->suivant;
else
    *tete = max->suivant;

if (max->suivant != NULL)
    max->suivant->precedent = max->precedent;

max->precedent = NULL;
max->suivant = NULL; // isolated — safe to return
```

Cost: O(1) at insertion, O(n) at extraction.

---

## 🚀 How to Compile and Run

```bash
gcc -Wall -Wextra -g main.c scheduler.c -o scheduler
./scheduler
```

---

## 📋 Example Output

```
========================================
   Simulateur d'ordonnancement
   Insertion triée + extraction en tête
========================================

État de la file après insertion :
[ID:2 | Priorité:25 | Temps:100ms] <-> [ID:5 | Priorité:20 | Temps:40ms] <-> ...

Démarrage de l'exécution :
  → Processus ID:2 | Priorité:25 | Durée:100ms
  → Processus ID:5 | Priorité:20 | Durée:40ms
  ...

Tous les processus ont été exécutés.
Temps total d'exécution : 330ms

========================================
   Simulateur d'ordonnancement (Part 2)
   Ajout en queue + extraction du meilleur
========================================

File avec l'ordre d'arrivée (pas triée) :
[ID:6 | Priorité:8 | Temps:120ms] <-> [ID:7 | Priorité:30 | Temps:90ms] <-> ...

Exécution par extraction du meilleur à chaque tour :
  → Processus ID:7 | Priorité:30 | Durée:90ms | Démarre à t=0ms
     File restante : [ID:6 | Priorité:8 ...] <-> ...
  ...
```

---

## 🛡️ Memory Leaks (Valgrind)

In C, every `malloc` needs a `free`. I use Valgrind to verify nothing leaks.

```bash
valgrind --leak-check=full ./scheduler
```

Result:

```
== HEAP SUMMARY:
==    in use at exit: 0 bytes in 0 blocks
== All heap blocks were freed -- no leaks are possible
```

Every byte asked for was correctly returned to the system.
