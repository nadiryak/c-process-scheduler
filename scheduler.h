#ifndef SCHEDULER_H
#define SCHEDULER_H

#include<stdio.h>
#include<stdlib.h>

// Structure -> process
// une structure qui stock des infos sur des taches a executer

typedef struct Process{
    int id; 
    int priority; //priorite pour execution de 1 _ 10
    int execution_time; 
    struct Process *suivant; // un pointeur qui pointe vers le prochain process
    struct Process *precedent;// un pointeur qui pointe vers le process precedent
} Process ;

// Prototypes des fonctions (on les implémentera plus tard)
Process* create_process(int id, int priority, int time);

Process* ajouter_process_a_la_fin(Process *tete, Process *nv_p);


void free_all_processes(Process* tete);

Process* extraire_meilleure_priorite(Process **head);

Process* inserer(Process *tete, Process*nv);
Process* extraire_premiere_elt(Process **tete );

#endif
