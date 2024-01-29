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
*  Nom du fichier :     afficherIP.c                                          *
*                                                                             *
******************************************************************************/


#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constantes.h"
#include "structures.h"
#include "extraireIP.h"
#include "format.h"
#include "afficherIP.h"

/*
Fonction d'affichage des informations d'une adresse IP
Prend en entrée une adresse IP valide stockée sous format décimal ainsi qu'un point de reprise assurant la validité de l'adresse IP
Affiche la classe et le type de l'adresse IP
*/
void printType(DecimalAddress address, jmp_buf jump){
    char class = getAddressClass(address.decimalByte[0], jump); // Variable de type caractère stockant la classe de l'adresse IP
    char* type = getAdressType(address);                        // Variable de type chaine de caractères stockant le type de l'adresse IP
    FILE *fichier = fopen("enregistrements.txt", "a");          // Ouverture du fichier dans lequel va être enregistré l'affichage
    printf("classe : %c\n", class);
    printf("type : %s\n", type);

    if (fichier != NULL){
        fprintf(fichier, "classe : %c\n", class);
        fprintf(fichier, "type : %s\n", type);
        fclose(fichier);
    }
}

/*
Fonction d'affichage du détail d'une adresse IP
Prend en entrée une adresse IP valide stockée sous format décimal ainsi qu'un point de reprise assurant la validité de l'adresse IP
Affiche l'adresse réseau et l'adresse host l'adresse IP
*/
void printAddresses(DecimalAddress address, jmp_buf jump){
    Addresses addresses = getAddresses(address, jump);      // Initialisation de la structure convertissant l'adresse IP en adresse Réseau et adresse Host
    FILE *fichier = fopen("enregistrements.txt", "a");      // Ouverture du fichier dans lequel va être enregistré l'affichage
    
    if(addresses.existNet){
        printf("@reseau : %d.%d.%d.%d\n",addresses.netAddress[0],addresses.netAddress[1],addresses.netAddress[2],addresses.netAddress[3]);
    } else {
        printf("@reseau : non defini (classe E sans masque)\n");
    }
    printf("@host : %d.%d.%d.%d\n",addresses.hostAddress[0],addresses.hostAddress[1],addresses.hostAddress[2],addresses.hostAddress[3]);

    if (fichier != NULL){
        if(addresses.existNet){
            fprintf(fichier, "@reseau : %d.%d.%d.%d\n",addresses.netAddress[0],addresses.netAddress[1],addresses.netAddress[2],addresses.netAddress[3]);
        } else {
            fprintf(fichier, "@reseau : non defini (classe E sans masque)\n");
        }
        fprintf(fichier, "@host : %d.%d.%d.%d\n",addresses.hostAddress[0],addresses.hostAddress[1],addresses.hostAddress[2],addresses.hostAddress[3]);
        fclose(fichier);
    }
}

/*
Fonction d'affichage de l'ensemble des informations relatives à une adresse IP.
Prend en entrée une adresse IP sous forme de chaine de charactères ainsi qu'un point de reprise assurant la validité de l'adresse IP
Affiche l'ensemble des informations relatives à cette adresse IP : Classe, Type, adresse Réseau, adresse Host.
*/
void printAddressInformations(char* address, jmp_buf ptRep){
    DecimalAddress addressDecimal;                                              // Structure stockant l'adresse IP sous format décimal
    addressDecimal = stringAddressToDecimal(extractFields(address, ptRep));
    FILE *fichier = fopen("enregistrements.txt", "a");                          // Ouverture du fichier dans lequel va être enregistré l'affichage

    // Obtenir la date et l'heure actuelle
    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);

    // Formater la date et l'heure et l'enregistrer dans la variable datetime
    char datetime[50];
    strftime(datetime, sizeof(datetime), "%d/%m/%Y %H:%M:%S", current_time);
    

    // Affichage dans la console
    printf("\n--------------------------------------\n");
    printf("--- DETAIL DE L'ADRESSE RENSEIGNEE ---\n");
    printf("--------------------------------------\n\n");
    printf("adresse complete : %s\n", address);

    // Enregistrement dans le fichier
    if (fichier != NULL){
        fprintf(fichier, "---------------------------------\n");
        fprintf(fichier, "Recherche du %s\n", datetime);
        fprintf(fichier, "\n=================================\n");
        fprintf(fichier,"DETAIL DE L'ADRESSE IP RENSEIGNEE\n");
        fprintf(fichier,"=================================\n\n");
        fprintf(fichier,"adresse complete : %s\n", address);
        fclose(fichier);
    }

    // Affichage et enregistrement des informations détaillées de l'adresse IP
    printType(addressDecimal, ptRep);
    printAddresses(addressDecimal, ptRep);

    // Sauts de ligne dans la console
    printf("\n\n");

    // Sauts de ligne dans le fichier
    fichier = fopen("enregistrements.txt", "a");
    if (fichier != NULL){
        fprintf(fichier, "\n\n");
        fclose(fichier);
    }
}