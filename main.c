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
//     // 1. Création de deux processus différents
//     Process *p1 = create_process(1, 10, 50); // Très prioritaire
//     Process *p2 = create_process(2, 1, 200); // Peu prioritaire

//     if (p1 == NULL || p2 == NULL) return 1;

//     // 2. LE CHAÎNAGE
//     p1->suivant = p2;      // p1 pointe dvers p2
//     p2->precedent = p1;    // p2 pointe vers p1 (doublement chaînée)

//     // Test de navigation : On part de p1 pour afficher les infos de p2
//     printf("Je suis le processus %d.\n", p1->id);
//     if (p1->suivant != NULL) {
//         printf("Mon successeur est le processus %d avec une priorite de %d.\n", 
//                 p1->suivant->id, p1->suivant->priority);
//     }

//     
//     free(p1);
//     free(p2);

//     printf("\nTout a ete libere.\n");
//     return 0;
// 
// int main() {
//     Process *liste = NULL;

    
//     liste = ajouter_process_a_la_fin(liste, create_process(1, 10, 30));
//     liste = ajouter_process_a_la_fin(liste, create_process(2, 5, 100));
//     liste = ajouter_process_a_la_fin(liste, create_process(3, 8, 20));

//     // Test d'affichage simple
//     Process *curr = liste;
//     while(curr != NULL) {
//         printf("Processus ID: %d | Priority: %d\n", curr->id, curr->priority);
//         curr = curr->suivant;
//     }

//     // On libère de la mémoire
//     free_all_processes(liste);

//     return 0;
// }

#include <stdio.h>
#include "scheduler.h"


// on affiche tous les processus de la liste
void afficher_liste(Process *tete) {
    Process *curr = tete;

    if (curr == NULL) {
        printf("(liste vide)\n");
        return;
    }

    while (curr != NULL) {
        printf("[ID:%d | Priorité:%d | Temps:%dms]",
               curr->id, curr->priority, curr->execution_time);
        if (curr->suivant != NULL) printf(" <-> ");
        curr = curr->suivant;
    }
    printf("\n");
}


int main() {

    printf("========================================\n");
    printf("   Simulateur d'ordonnancement  \n");
    printf("   Insertion triée + extraction en tête \n");
    printf("========================================\n\n");

    // on intialise notre file de processus avec NULL (elle est vide)  
    Process *file = NULL;

    // on insère les processus un par un
    // inserer() les place automatiquement au bon endroit selon leur priorité
    file = inserer(file, create_process(1, 10,  50));
    file = inserer(file, create_process(2, 25, 100));
    file = inserer(file, create_process(3,  5,  80));
    file = inserer(file, create_process(4, 15,  60));
    file = inserer(file, create_process(5, 20,  40));

    printf("État de la file après insertion (du plus au moins prioritaire) :\n");
    afficher_liste(file);

    // maintenant on simule l'exécution
    // à chaque tour de boucle, on extrait le premier élément (le plus prioritaire)
    // on "l'exécute" (ici on affiche juste ses infos) puis on libère sa mémoir et on passe au suivant 
    printf("\nDémarrage de l'exécution :\n");

    int temps_total = 0; // on initialise le temps à zero et on l'incrémente en additionnant le temps_execuition de chaqu process

    while (file != NULL) {

        // on prend le processus le plus prioritaire en tête de liste
        Process *p = extraire_premiere_elt(&file);

        printf("  → Processus ID:%d | Priorité:%d | Durée:%dms \n", p->id, p->priority, p->execution_time);

        // on incrémente le compteur de temps
        temps_total += p->execution_time;

        // on libère ce processus 
        free(p);
    }

    printf("\nTous les processus ont été exécutés.\n");
    printf("Temps total d'exécution : %dms\n", temps_total);


    // =========================================================
    // ajouter_process_a_la_fin + extraire_meilleure_priorite
    // =========================================================
    // ici on ne trie pas à l'insertion — on ajoute juste les processus
    // dans l'ordre où ils arrivent, comme une vraie file d'attente brute
    // ensuite on cherche manuellement le meilleur à chaque fois
    // c'est une autre approche de l'ordonnancement

    printf("\n========================================\n");
    printf("   Simulateur d'ordonnancement \n");
    printf("   Ajout en queue + extraction du meilleur \n");
    printf("========================================\n\n");

    Process *file2 = NULL;

    // on ajoute les processus à la fin — pas de tri, juste ajout en queue l'ordre est conservé
    file2 = ajouter_process_a_la_fin(file2, create_process(6,  8, 120));
    file2 = ajouter_process_a_la_fin(file2, create_process(7, 30,  90));
    file2 = ajouter_process_a_la_fin(file2, create_process(8, 12,  45));
    file2 = ajouter_process_a_la_fin(file2, create_process(9,  3,  70));

    printf("File brute (ordre d'arrivée, pas triée) :\n");
    afficher_liste(file2);

    // maintenant à chaque tour on cherche le processus avec la priorité max avec extraire_meilleure_priorite
    // on le décroche et on recoud les wagons autour de lui
    printf("\nExécution par extraction du meilleur à chaque tour :\n");

    int temps_total2 = 0;

    while (file2 != NULL) {

        // on cherche et on extrait le processus le plus prioritaire
        Process *meilleur = extraire_meilleure_priorite(&file2);

        printf("  → Processus ID:%d | Priorité:%d | Durée:%dms"
               " | Démarre à t=%dms\n",
               meilleur->id, meilleur->priority,
               meilleur->execution_time, temps_total2);

        temps_total2 += meilleur->execution_time;

        // libération de mémoire 
        free(meilleur);

        // on affiche l'état de la liste après chaque extraction
        printf("     File restante : ");
        afficher_liste(file2);
    }

    printf("\nTous les processus ont été exécutés.\n");
    printf("Temps total d'exécution : %dms\n", temps_total2);

    return 0;
}
