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
*  Nom du fichier :		extraireIP.h 										  *
*                                                                             *
******************************************************************************/

#ifndef _EXTRACTIONIP

#define _EXTRACTIONIP
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "structures.h"
#include "puissance.h"
#include "verifierIP.h"
#include "extraireIP.h"

char* getMask(char* address);
StringAddress extractFields(char* address, jmp_buf ptRep);
char getAddressClass(int byte, jmp_buf jump);
char* getAdressType(DecimalAddress adress);
Addresses getAddresses(DecimalAddress address, jmp_buf jump);

#endif