 #include <stdio.h>
 #include "scheduler.h"
// // #include<time.h>

// // int main(){

// //     Process *processus_1=create_process(1,5,100);
    
// //     // on fait un check et on s'arrete si l'allocation a echouee
// //     if (processus_1==NULL){
// //         printf("L'allocation de memoire a echouee");
// //         return 1;
// //     }

// //     // on teste d'afficher le contenu 

// //     printf("--- Test de création ---\n");
// //     printf("ID : %d\n", processus_1->id);
// //     printf("Priorite : %d\n", processus_1->priority);
// //     printf("Temps : %d ms\n", processus_1->execution_time);



// //     free(processus_1);
// //     printf("Liberation de memoire avec succes");
// //     return 0;   
// // }
// #include <stdio.h>
// #include "scheduler.h"

// int main() {
//     // 1. Création de deux processus distincts
//     Process *p1 = create_process(1, 10, 50); // Très prioritaire
//     Process *p2 = create_process(2, 1, 200); // Peu prioritaire

//     if (p1 == NULL || p2 == NULL) return 1;

//     // 2. LE CHAÎNAGE (C'est ici que la magie opère)
//     p1->suivant = p2;      // p1 pointe vers p2
//     p2->precedent = p1;    // p2 pointe vers p1 (doublement chaînée)

//     // 3. Test de navigation : On part de p1 pour afficher les infos de p2
//     printf("Je suis le processus %d.\n", p1->id);
//     if (p1->suivant != NULL) {
//         printf("Mon successeur est le processus %d avec une priorite de %d.\n", 
//                 p1->suivant->id, p1->suivant->priority);
//     }

//     // 4. LIBÉRATION (Attention, il faut libérer les deux !)
//     free(p1);
//     free(p2);

//     printf("\nTout a ete libere.\n");
//     return 0;
// 
int main() {
    Process *liste = NULL;

    // On ajoute 3 processus à la chaîne
    liste = ajouter_process_a_la_fin(liste, create_process(1, 10, 30));
    liste = ajouter_process_a_la_fin(liste, create_process(2, 5, 100));
    liste = ajouter_process_a_la_fin(liste, create_process(3, 8, 20));

    // Test d'affichage simple
    Process *curr = liste;
    while(curr != NULL) {
        printf("Processus ID: %d | Priority: %d\n", curr->id, curr->priority);
        curr = curr->suivant;
    }

    // ON NETTOIE TOUT
    free_all_processes(liste);

    return 0;
}