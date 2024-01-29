/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet :        2                                                     *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé :           Analyse adresse IP                                    *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 :        BERNARD-NICOD Vivien                                  *
*                                                                             *
*  Nom-prénom2 :        GOUJON Maël                                           *
*                                                                             *
*  Nom-prénom3 :        HOFFLER Marie-Ange                                    *
*                                                                             *
*  Nom-prénom4 :        KOH Youchen                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier :     main.c                                                *
*                                                                             *
******************************************************************************/

#include <setjmp.h>
#include <stdio.h>
#include "constantes.h"
#include "afficherIP.h"

int main() {
    char address[MAX_LENGTH];   // Variable stockant l'adresse renseignée par l'utilisateur
    jmp_buf ptRep;              // Point de reprise pour la gestion des exceptions
    Exception exept;            // Variable stockant l'état de l'exception selon les points de reprises

    //pose du point de reprise
    exept=setjmp(ptRep);

    // Test de la valeur de retour
    switch (exept) {
    // Gestion du cas ou l'adresse renseignée est valide
    case OK :
        printf("Veuillez renseigner votre adresse ip: ");
        fgets(address, MAX_LENGTH, stdin);
        printAddressInformations(address, ptRep);
        break;
    // Gestion du cas ou l'adresse renseignée est invalide
    case INVALID_ADDRESS :
        printf("Adresse IP invalide \n\n");
        printf("Veuillez renseigner votre adresse ip: ");
        fgets(address, MAX_LENGTH, stdin);
        printAddressInformations(address, ptRep);
        break;
    // Gestion du cas ou l'un des octets renseigné est invalide
    case INVALID_BYTE :
        printf("Octet invalide \n\n");
        printf("Veuillez renseigner votre adresse ip: ");
        fgets(address, MAX_LENGTH, stdin);
        printAddressInformations(address, ptRep);
        break;
    default :
        printf("\nAnomalie inconnue\n");
    }
    return (exept);
}