/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N° de Sujet : 		2                                                     *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé :    		Analyse adresse IP                                    *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 :    	BERNARD-NICOD Vivien                                  *
*                                                                             *
*  Nom-prénom2 :    	GOUJON Maël                                           *
*                                                                             *
*  Nom-prénom3 :    	HOFFLER Marie-Ange                                    *
*                                                                             *
*  Nom-prénom4 :    	KOH Youchen                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier :		afficherIP.h 										  *
*                                                                             *
******************************************************************************/

#ifndef _AFFICHERIP

#define _AFFICHERIP
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constantes.h"
#include "structures.h"
#include "extraireIP.h"
#include "format.h"

void printType(DecimalAddress address, jmp_buf jump);
void printAddresses(DecimalAddress address, jmp_buf jump);
void printAddressInformations(char* address, jmp_buf ptRep);

#endif