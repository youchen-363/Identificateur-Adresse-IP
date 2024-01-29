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
*  Nom du fichier :     verifierIP.c                                          *
*                                                                             *
******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "constantes.h"
#include "verifierIP.h"
#include "extraireIP.h"

/* 
Fonction de vérification d'existence d'un masque pour une adresse ip.
Prend une chaine de caracteres en entrée correspondant à l'adresse IP
Renvoie vrai ou faux selon l'existence du masque dans la chaine renseignée
*/
int existMask(char* address){
    char* exist = strchr(address, '/');
    if(exist){
        return 1;
    }
    return 0;
}

/* 
Fonction de vérification de la validité d'un octet.
Prend une chaine de caractères en entrée correspondant à l'octet à vérifier ainsi que sa taille.
Renvoie 0 ou 1 selon la validité de l'octet.
*/
int isValidByte(char* object, int objectSize ){
    char *endptr;
    char *byte = malloc(NB_BYTES * sizeof(char));   // Allouer de la mémoire pour la nouvelle chaîne de caractères
    int digitalByte;                                // Variable de type entier récupérant l'octet sous format digital

    //Verification de la taille d'un octet compris entre 1 et 3 caractères
    if(objectSize > 3 || objectSize < 1){
        printf("un octet est de mauvaise taille %d %s\n", objectSize, object);
        free(byte);
        return 0;
    }

    //vérification du caractere numérique de l'octet
    strncpy(byte, object, objectSize);
    byte[objectSize]= '\0';
    if(!isdigit(*byte)){
        printf("un octet possede des caracteres non numeriques\n");
        free(byte);
        return 0;
    }

    //vérification de la valeur de l'octet compris entre 0 et 255
    digitalByte = strtol(byte, &endptr, 10);
    if(digitalByte < 0 || digitalByte > 255){
        printf("un octet a une valeur non conforme\n");
        free(byte);
        return 0;
    }
    free(byte);
    return 1;
}

/* 
Fonction de vérification de la validité de la partie IP d'une adresse ip.
Prend une chaine de caractères en entrée correspondant à l'adresse ip à vérifier.
Renvoie 0 ou 1 selon la validité de la partie IP de l'adresse ip.
*/
int isValidIpAddress(char *adress) {
    int dots = 0;       //nombre de points recensés dans l'adresse IP transmise
    int byteSize;       //taille de l'octet en cours d'analyse
    char *occurence, *currentPtr, *ptrLongueur;

    //boucle de vérification des octets renseignés
    currentPtr = adress;
    occurence = strchr(currentPtr, '.');
    while(occurence){
        byteSize = strlen(currentPtr) - strlen(occurence);
        if(!isValidByte(currentPtr, byteSize)){
            return 0;
        }
        currentPtr = occurence + 1;
        occurence = strchr(currentPtr, '.');
        dots ++;
    }

    //gestion de la derniere occurence
    if(existMask(adress)){
        occurence = strchr(currentPtr, '/');
        if(!isValidByte(currentPtr, strlen(currentPtr) - strlen(occurence))){
            return 0;
        }
    } else {
        if(!isValidByte(currentPtr, strlen(currentPtr) - 1)){
            return 0;
        }
    }
    
    //gestion du cas ou tous les octets sont valides mais le nombre d'octets renseignés est invalide
    if(dots != 3){
        printf("nombre d'octets renseignes invalide\n");
        return 0;
    }
    return 1;
}

/* 
Fonction de vérification de la validité d'un masque d'adresse IP.
Prend une chaine de caractères en entrée correspondant au masque à analyser.
Renvoie 0 ou 1 selon la validité du masque.
*/
int isValidMask(char *mask){
    char* endptr;
    int maskValue;  //variable stockant la valeur numérique du masque

    //gestion du cas ou le masque n'est pas numérique
    if(!isdigit(*mask)){
        printf("le masque n'est pas numerique\n");
        return 0;
    }

    //gestion du cas ou le masque a une valeur invalide
    maskValue = strtol(mask, &endptr, 10);
    if(maskValue < 0 || maskValue > 32){
        printf("le masque a une valeur non conforme\n");
        return 0;
    }
    return 1;
}

/* 
Fonction de vérification de la validité d'une adresse ip complete renseignée avec ou sans masque.
Prend une chaine de caractères en entrée correspondant a l'adresse ip à analyser.
Renvoie 0 ou 1 selon la validité de cette adresse.
*/
int isValidFormat(char* address){
    //gestion du cas ou l'utilisateur ne renseigne rien
    if (!address) {
        printf("adresse ip non renseignee\n");
        return 0;
    }
    //gestion du cas ou la partie IP n'est pas valide
    if(!isValidIpAddress(address)){
        return 0;
    }
    //gestion du cas ou la partie IP est valide et un maszque est renseigné
    if(existMask(address)){
        if(!isValidMask(getMask(address))){
            return 0;
        }
    }
    return 1;
}






