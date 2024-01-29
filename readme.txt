=========================================================================
Copyright 2023 MINI PROJET LANGAGE C, GROUPE C, INC. All Rights Reserved.
=========================================================================

Dépot git : 


Mini Projet C Package:
----------------------
Ce package propose une application executable permettant de catégoriser une adresse IP ainsi que d'en extraire l'addresse réseau et l'adresse Host.
L'objectif de cette application est de faciliter la recherche d'informations sur les adresses IP.
L'utilisateur doit tout simplement renseigner une adresse IP qui sera :
	- vérifiée à travers un ensemble de fonction afin de savoir si son format est valide dans : verifierIP.c
	- découpée en ensemble d'informations relatives à l'adresse (octets, masque) à travers une fonctions d'extraction dans : extraireIP.c
	- convertie en valeur numérique à l'aide d'une fonction principale dans : format.c
	- analysée à l'aide d'un groupement de fonction permettant de décoder l'adresse IP et de calculer @réseau et @hôte dans : extraireIP.c

Par la suite l'application affichera ces informations sur la console et les enregistrera dans un fichier "enregistrements.txt" à l'aide d'un groupement
de fonctions dans : afficherIP.c


Systemes d'Exploitations supportés:
----------------------------------
GNU/Linux


Instructions liées à l'utilisation du package:
----------------------------------------------
1. 	Ouvrez votre terminal à l'emplacement du readme.
2. 	Lancez la commande make afin de construire le fichier executable
3. 	Si vous voulez lancer l'application, toujours dans votre terminal tapez l'instruction : ./main
4.	si vous voulez supprimer l'ensemble des fichiers produits par la commande make tapez la commande : make clean


Instructions liées à l'utilisation de l'application:
----------------------------------------------------
1. 	Ne lancez l'application qu'à partir de votre terminal avec les instructions indiquées ci-dessus 
	autrement vous ne pourrez pas voir le résultat de votre recherche d'informations sur votre terminal
	Toutefois vous pourrez toujours y accéder dans le fichier enregistrements.txt
2. 	Une fois l'application main lancée, suivez les instructions indiquées sur votre terminal.
3.	Chaque recherche sera enregistrée dans le fichier enregistrements.txt

