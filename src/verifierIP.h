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
*  Nom du fichier :		verifierIP.h 										  *
*                                                                             *
******************************************************************************/

#ifndef _VERIFICATIONIP

#define _VERIFICATIONIP
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "constantes.h"
#include "verifierIP.h"
#include "extraireIP.h"

int existMask(char* address);
int isValidByte(char* object, int objectSize );
int isValidIpAddress(char *adress);
int isValidMask(char *mask);
int isValidFormat(char* address);

#endif