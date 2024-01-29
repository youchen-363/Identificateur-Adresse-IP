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
*  Nom du fichier :     structures.h                                          *
*                                                                             *
******************************************************************************/

#ifndef _STRUCTURES 

#define _STRUCTURES
#include "constantes.h"

// Structure stockant une adresse IP sous forme de chaines de caractères en séparant la partie adresse et la partie masque : utilisé pour les extractions
typedef struct{ 
    char* charBytes [NB_BYTES];
    char* charMask;
} StringAddress;

// Structure stockant une adresse IP sous forme d'entiers / chaine d'entiers en séparant la partie adresse et la partie masque : utilisée pour les calculs
typedef struct{ 
    int decimalByte [NB_BYTES]; 
    int decimalMask;
} DecimalAddress;

// Structure stockant une adresse IP sous forme d'adresse Réseau, d'adresse Host en et de pseudo boolean indiquant l'existance de l'adresse réseau.
typedef struct{ 
    int hostAddress [NB_BYTES]; 
    int netAddress [NB_BYTES];
    int existNet;
} Addresses;

#endif
