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
*  Nom du fichier :     format.c                                              *
*                                                                             *
******************************************************************************/

#include <stdlib.h>
#include "constantes.h"
#include "structures.h"
#include "format.h"

/*
>>> fonction générale de la partie : CONVERTIR EN VALEURS NUMERIQUES
Fonction convertissant une adresse IP sous forme de caractères en adresse IP numérique.
Prend en entrée une structure stockant les informations de l'adresse IP sous forme de caractères.
Renvoie en sortie une structure stockant les informations de l'adresse IP sous forme de nombres.
*/
DecimalAddress stringAddressToDecimal(StringAddress address){
    DecimalAddress decimalAddress;  // Structure accueillant les données de l'adresse IP dans un format numérique.
    char* endptr;
    for(int i = 0; i < NB_BYTES; i++){
        decimalAddress.decimalByte[i] = strtol(address.charBytes[i], &endptr, 10);  // Conversion des octets sous forme de caractères de l'adresse IP  en format numérique
    }
    if(!address.charMask){
        decimalAddress.decimalMask = -1;
    } else {
        decimalAddress.decimalMask = strtol(address.charMask, &endptr, 10); // Conversion du masque sous forme de caractères si il existe de l'adresse IP  en format numérique
    }
    return decimalAddress;
}