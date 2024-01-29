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
*  Nom du fichier :     puissances.c                                          *
*                                                                             *
******************************************************************************/

#include "puissance.h"

/*
Fonction de calcul d'une puissance modifiée
Prend en entrée deux entier pour la calcul de la puissance
Renvoie un entier résultant du calcul : base puissance exposant
*/
int powint(int base, int exposant){
    int result = 1;
    if (exposant < 0){
        for(int i=1; i < -exposant; i++){
            result = result * base;
        }
        result = 1/result;
    }
    if (exposant > 0){
        for(int i=1; i < exposant; i++){
            result = result * base;
        }
    }
    return result;
}