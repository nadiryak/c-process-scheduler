#include"scheduler.h"
Process* create_process(int id, int priority, int time){
    Process* nouveau= (Process*) malloc(sizeof(Process));
    // on a alloué de l'espace memoire en fnction de la taille de Process
    
    // on verif
    if (nouveau==NULL){
        fprintf(stderr,"Erreur : échec de l'allocation mémoire.\n");
        return NULL;
    }
    // on associe les donnee à leur espace memoire exacte pointé par nouveau
    // va a cette espace "nouveau" exactement a id 

    nouveau->id=id;
    nouveau->priority=priority;
    nouveau->execution_time=time;

    
    nouveau->suivant=NULL;
    nouveau->precedent=NULL;

    return nouveau;

}

Process* ajouter_process_a_la_fin(Process* tete, Process* nv_p){
  
    if (nv_p==NULL){
        fprintf(stderr,"Erreur : échec de l'allocation mémoire.\n");
        return NULL;
    }
    // si tete n'a pas d'espace memoire allouee donc il pointe vers rien 
    // on return nv_p

    if (tete==NULL){
        return nv_p;
    }

    // sinon je parcours ma liste chainée jusqu'à la fin
    Process* actuel=tete;
    while (actuel->suivant!=NULL){
        actuel=actuel->suivant;
    }
    actuel->suivant=nv_p;
     nv_p->precedent=actuel; //on lie le nv process à la fin de la chaine mais avec des pointeurs
    return tete;   }

void free_all_processes(Process *tete){
    Process* temp;
    while(tete!=NULL){
        temp=tete;
        tete=tete->suivant;
        free(temp);
}
}

// Process* extraire_meilleure_priorite(Process **head)