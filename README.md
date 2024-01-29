# Mini Projet C Sujet2
Mini projet C réalisé par les étudiants :
- Bernard-Nicod Vivien
- Goujon Maël
- Höffler Marie-Ange
- Koh You Chen


# Introduction
Ce package propose une application executable permettant de catégoriser une adresse IP ainsi que d'en extraire l'addresse réseau et l'adresse Host.

L'objectif de cette application est de faciliter la recherche d'informations sur les adresses IP.


## Fonctionnalités
L'utilisateur doit tout simplement renseigner une adresse IP qui sera :

- Vérifiée à travers un ensemble de fonction afin de savoir si son format est valide dans : **verifierIP.c**

- Découpée en ensemble d'informations relatives à l'adresse (octets, masque) à travers une fonctions d'extraction dans : **extraireIP.c**

- Convertie en valeur numérique à l'aide d'une fonction principale dans : **format.c**

- Analysée à l'aide d'un groupement de fonction permettant de décoder l'adresse IP et de calculer @réseau et @hôte dans : **extraireIP.c**

Par la suite l'application affichera ces informations sur la console et les enregistrera dans un fichier "enregistrements.txt" à l'aide d'un groupement de fonctions dans : **afficherIP.c**

## Prérequis
Systemes d'Exploitations : GNU/Linux


## Instructions liées à l'utilisation du package
1. 	Ouvrez votre terminal à l'emplacement du readme.
2. 	Lancez la commande make afin de construire le fichier executable
3. 	Pour lancer l'application, dans votre terminal tapez l'instruction 
`./main`
4.	Pour supprimer l'ensemble des fichiers produits par la commande make tapez la commande : `make clean`


## Instructions liées à l'utilisation de l'application:

1. 	Ne lancez l'application qu'à partir de votre terminal avec les instructions indiquées ci-dessus autrement vous ne pourrez pas voir le résultat de votre recherche d'informations sur votre terminal. Toutefois vous pourrez toujours y accéder dans le fichier
`enregistrements.txt`

2. 	Une fois l'application main lancée, suivez les instructions indiquées sur votre terminal

3.	Chaque recherche sera enregistrée dans le fichier :
`enregistrements.txt`


## License
Ce projet est sous licence MIT. Vous êtes libre de copier, modifier et distribuer ce code. Consultez le fichier **LICENSE** pour plus de détails.
