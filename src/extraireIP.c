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
*  Nom du fichier :     extraireIP.c                                          *
*                                                                             *
******************************************************************************/

#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "structures.h"
#include "puissance.h"
#include "verifierIP.h"
#include "extraireIP.h"

/*
Fonction d'extraction d'un masque d'une adresse IP
Prend en entrée une adresse IP sous format de chaine de caractères
Renvoie le masque de l'adresse IP sous format de chaine de caractères
*/
char* getMask(char* address){
    char* mask = strchr(address, '/');
    mask ++;
    return mask;
}

/*
>>> fonction générale de la partie : EXTRAIRE LES CHAMPS
Fonction d'extraction des informations d'une adresse IP.
Prend en entrée une adresse IP sous format de chaine de caractères ainsi qu'un point de reprise assurant la validité de l'adresse IP.
Extrait chaque octet ainsi que le masque s'il existe de l'adresse IP pour stocker ces informations sous format de chaines de caractères dans la structure adéquate.
Renvoie la structure stockant ces informations.
*/
StringAddress extractFields(char* address, jmp_buf ptRep){

    // Gestion des exceptions si l'adresse renseignée est invalide
    if(!isValidFormat(address)){
        longjmp( ptRep, INVALID_ADDRESS);
    }

    StringAddress stringAddress;            // Structure accueillant les données extraites de la chaine de caractère étant l'adresse IP
    int byteSize;                           // Entier stockant le nombre de caractère de l'octet en cours d'extraction
    char *ptr = address;                    // Pointeur mémorisant la chaine de caractères initiales étant l'adresse IP
    char *occurrence = strchr(ptr, '.');    // Pointeur permettant la délimitation des octets et du masque s'il existe de la chaine de caractères étant l'adresse IP durant l'extraction des données

    //Extraction des 3 premiers octets
    for(int i = 0; i < 3; i++){
        byteSize = strlen(ptr) - strlen(occurrence);
        stringAddress.charBytes[i] = malloc((byteSize + 1) * sizeof(char));
        strncpy(stringAddress.charBytes[i], ptr, byteSize);
        stringAddress.charBytes[i][byteSize] = '\0';
        ptr = occurrence + 1;
        occurrence = strchr(ptr, '.');
    }

    //Gestion du masque
    if(existMask(address)){
        byteSize = strlen(ptr) - strlen(strchr(ptr, '/'));
        stringAddress.charMask = malloc((strlen(getMask(address))) * sizeof(char));
        strcpy(stringAddress.charMask, getMask(address));
    } else {
        byteSize = strlen(ptr);
        stringAddress.charMask = NULL;
    }

    //Extraction du dernier octet
    stringAddress.charBytes[3] = malloc((byteSize) * sizeof(char));
    strncpy(stringAddress.charBytes[3], ptr, byteSize);
    stringAddress.charBytes[3][byteSize] = '\0';
    return stringAddress;
}

/*
>>> partie 1 de fonction générale de la partie : DECODER IP
Fonction d'identificationde la classe d'une adresse IP.
Prend en entrée un entier représentant le premier octet d'une adresse IP ainsi qu'un point de reprise assurant que l'octet renseigné est valide.
Renvoie en sortie sous format de caractère la classe de l'adresse IP
*/
char getAddressClass(int byte, jmp_buf jump){
    // Gestion de l'exception assurant la validité de l'octet renseigné
    if(byte < 0 || byte > 255){
        longjmp(jump, INVALID_BYTE);
    }
    if(byte < 128){
        return 'A';
    }
    if(byte < 192){
        return 'B';
    }
    if (byte < 224){
        return 'C';
    }
    if (byte < 240){
        return 'D';
    }
    return 'E';
}

/*
>>> partie 2 de fonction générale de la partie : DECODER IP
Fonction d'identificationde du type d'une adresse IP.
Prend en entrée une adresse IP stockée dans une structure de données regroupant au format numérique la partie adresse et la partie masque de l'adresse IP
Renvoie en sortie sous forme de chaine de caractères le type de l'adresse IP
*/
char* getAdressType(DecimalAddress adress){
    // Déclaration des variables récupérant la valeur des octets de l'adresse IP.
    int firstByte = adress.decimalByte[0];
    int secondByte = adress.decimalByte[1];
    int thirdByte = adress.decimalByte[2];
    int lastByte = adress.decimalByte[3];

    //  Déclaration de la variable stockant sous forme de chaine de caractères le type de l'adresse
    char* type = "public";

    // Structure de controle identifiant le type de l'adresse IP renseignée
    switch(firstByte){
    case 0:
        type = "private";
        break;
    case 10:
        type = "private";
        break;
    case 100:
        if(secondByte > 63 && secondByte < 128){
            type = "public : Carrier-grade NAT";
        }
        break;
    case 127:
        type = "private : localhost";
        break;
    case 169:
        if (secondByte == 254){
            type = "private : APIPA";
        }
        break;
    case 172:
        if(secondByte > 15 && secondByte < 32){
            type = "private";
        }
        break;
    case 192:
        switch(secondByte){
        case 0:
            switch(thirdByte){
            case 0:
                type = "private for IETF";
                break;
            case 2:
                type = "private for TEST-NET-1";
                break;
            }
            break;
        case 88:
            if(thirdByte == 99){
                type = "public for 6to4 anycast";
            }
            break;
        case 168:
            type = "private";
            break;
        }
        break;
    case 198:
        if(secondByte > 17 && secondByte < 20){
            type = "performance test";
        }
        if(secondByte == 51 && thirdByte == 100){
            type = "private for TEST-NET-2";
        }
        break;
    case 203:
        if(secondByte == 0 && thirdByte == 113){
            type = "private for TEST-NET-3";
        }
        break;
    }
    if(firstByte > 223 && firstByte < 240){
        type = "multicast";
    }
    if(firstByte > 239){
        if(lastByte == 255){
            type = "broadcast";
        } else {
            type = "private";
        }
    } 
    return type;
}

/*
>>> fonction générale de la partie : CALCULER @RESEAU / @HOTE
Fonction d'identification de de la partie host et réseau d'une adresse IP
Prend en entrée une adresse IP stockée dans une structure de données regroupant au format numérique la partie adresse et la partie masque de l'adresse IP
Prend en entrée un point de reprise assurant la validité des données de l'adresse IP stockée.
Renvoie en sortie une structure de données stockant sous forme numerique la partie réseau, la partie host et un boolean indiquant l'existance de la partie réseau de l'adresse IP.
*/
Addresses getAddresses(DecimalAddress address, jmp_buf jump){
    // Structure accueillant les informations relatives à l'adresse IP
    Addresses addresses;                        

    // Entiers stockant la valeur initiale des octets et étant mis à jour pour renseigner la partie réseau et la partie host de l'adresse IP.
    int firstByte = address.decimalByte[0]; 
    int secondByte = address.decimalByte[1];
    int thirdByte = address.decimalByte[2];
    int lastByte = address.decimalByte[3];

    // Actualisation initiale de l'existance d'une partie réseau (par défaut)
    addresses.existNet = 1;

    // Gestion du cas ou le masque n'a pas été renseigné dans la structure indiqué en entrée.
    if(address.decimalMask == -1){
        switch (getAddressClass(address.decimalByte[0], jump)){
        case 'A':
            secondByte = 0;
            thirdByte = 0;
            lastByte = 0;
            break;
        case 'B':
            thirdByte = 0;
            lastByte = 0;
            break;
        case 'C':
            lastByte = 0;
            break;
        case 'E':
            firstByte = 0;
            secondByte = 0;
            thirdByte = 0;
            lastByte = 0;
            addresses.existNet = 0;
            break;
        }
    } 
    // Gestion du cas ou le masque a été renseigné
    else 
    {
        int nbFullByte = address.decimalMask / NB_BITS; // Variable stockant le nombre d'octets etant completement alloués à la partie réseau
        int nbBits = address.decimalMask % NB_BITS;     // Variable stockant le nombre de bits du dernier octet alloué à la partie réseau étant alloués à la partie réseau
        int indexByteMiddle = -1;                       // Variable stockant la position de l'octet étant coupé en 2 (un certain nombre de bits pour la partie réseau et le reste pour la partie host)
        
        // Actualisation des valeurs des octets pour la partie réseau étant vides
        switch(nbFullByte){
        case 0:
            secondByte = 0;
            thirdByte = 0;
            lastByte = 0;
            break;
        case 1:
            thirdByte = 0;
            lastByte = 0;
            break;
        case 2:
            lastByte = 0;
            break;
        }

        // Actualisation de l'octet de transistion (entre partie réseau et partie host)
        // Gestion du cas ou l'octet est divisé en 2 parties
        if (nbBits != 0){
            int decode = powint(2,(NB_BITS - nbBits));      // Variable stockant la valeur de calcul du nouvel octet pour la partie réseau
            indexByteMiddle = nbFullByte;                   // Variable stockant la position de l'octet à modifier
            
            // Calcul de la nouvelle valeur de l'octet pour la partie réseau
            switch(indexByteMiddle){
            case 0:
                firstByte = (firstByte / decode) * decode;
                break;
            case 1:
                secondByte = (secondByte / decode) * decode;
                break;
            case 2:
                thirdByte = (thirdByte / decode) * decode;
                break;
            case 3:
                lastByte = (lastByte / decode) * decode;         
                break;
            }
        }
        // Gestion du cas ou l'octet ne comporte que des bits host
        else
        {
            switch (nbFullByte){
            case 0:
                firstByte = 0;
                break;
            case 1:
                secondByte = 0;
                break;
            case 2:
                thirdByte = 0;
                break;
            case 3:
                lastByte = 0;       
                break;
            }
        }
    }

    // Attribution des nouvelles valeurs d'octets pour la partie Réseau
    addresses.netAddress[0] = firstByte;
    addresses.netAddress[1] = secondByte;
    addresses.netAddress[2] = thirdByte;
    addresses.netAddress[3] = lastByte;

    // Calcul et attribution des nouvelles valeurs d'octets pour la partie Host
    for(int i = 0; i < NB_BYTES; i++){
        addresses.hostAddress[i] = address.decimalByte[i] - addresses.netAddress[i];
    }
    return addresses;
}