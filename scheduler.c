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

Process* extraire_meilleure_priorite(Process **tete){
    if (*tete==NULL){
    return NULL;}

    Process* actuel=*tete;
    Process* max=*tete;
    
    while (actuel!=NULL){ //on cherche le process avec la priorité la plus haute
        
        if (actuel->priority > max->priority){ 
            max=actuel;
        }
        actuel=actuel->suivant;  //on avance après chaque verif
    }
    
    
    // on recoude les wagons de la liste
    if (max->precedent!=NULL){
        max->precedent->suivant=max->suivant;
}   else{
    *tete=max->suivant;
}

if (max->suivant != NULL) {
        max->suivant->precedent = max->precedent;   
     }
    
max->precedent=NULL; max->suivant=NULL;  // on isole le max pour écraser les ancienne adresse(le processuer va crooire qu'il est tjrs attaché à sa liste)
return max;        
}

Process* inserer (Process* tete, Process* nv) { 
      if (tete == NULL || nv->priority > tete->priority) {
        nv->suivant = tete; // Cas où la liste est vide ou le nouveau est le plus important
        if (tete != NULL) {
            tete->precedent = nv;
            }nv->precedent = NULL; // le nouveau est le premier, et donc y'a personne à sa gauche;
            return nv; 
    }
    Process* actuel=tete;
    while(actuel->suivant != NULL && actuel->suivant-> priority >= nv->priority){// On parcourt la liste pour trouver où mettre le nouveau wagon
        actuel=actuel->suivant;}
    nv->suivant=actuel->suivant;       //on insère nv entre actuel et le suivant
    nv->precedent=actuel;

    if (actuel->suivant!=NULL){
        actuel->suivant->precedent=nv; // si ce n'est pas la fin de la liste en double le chainage entre le suivant et nv
    }
    actuel->suivant=nv;  
return tete;}

Process* extraire_premiere_elt(Process **tete ){
    
    if (*tete == NULL) return NULL; // si c'est une liste vide, ça return vide

    Process* cible = *tete;   // on cible la tete
    *tete=cible->suivant; // on passse un autre wagon (le suivant) à l'adresse de lal tete

    if (cible->suivant != NULL) 
    {
        cible->suivant->precedent=NULL; // si ce n'est pas une liste à un elt, je mets à jour le suivant comme tete, donc il a rien à sa gauche
    }
    cible->suivant=NULL;cible->precedent=NULL; // j'isole la cible et je la renvoie
    return cible;

}
