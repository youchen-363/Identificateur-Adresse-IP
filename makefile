# Dossiers séparant les fichiers objets et les fichiers source
SRC_DIR := ./src
OBJ_DIR := ./obj

# Création de la variable $(SRC_FILES) stockant l'ensemble des fichiers .c du dossier \src
# Utilisation de la fonction wildcard qui renvoie la liste des fichiers correspondant à un motif donné
# ici le motif donné est : les fichiers de type .c (/*.c) contenus dans la variable $(SRC_DIR) soit le dossier src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)


# Création de la variable $(OBJ_FILES) qui est utilisée pour stocker la liste des fichiers objets à partir de la variable $(SRC_FILES)
# La variable est construite en utilisant la fonction patsubst
# patsubst fonctionne ainsi : patsubst <motif>, <remplacement>, <texte>
# <motif> représente les occurences à remplacer
# <texte> représente le texte dans lequel nous cherchons les occurences <motif>
# <remplacement> représente la valeur de remplacement de l'occurence <motif>
# Ici, on utilise la variable SRC_FILES comme texte à traiter soit l'ensemble des fichiers .c
# $(SRC_DIR)/%.c représente le motif, où % est un caractère générique qui correspondra à tous les fichiers .c dans le dossier SRC_DIR
# $(OBJ_DIR)/%.o représente le remplacement, où % correspondra au même nom de fichier mais avec l'extension .o dans le dossier OBJ_DIR
# Concretement, patsubst permet d'attribuer à la variable $(OBJ_FILES) la liste des fichiers .o à partir de la liste des fichiers .c en 
# cherchant dans la liste $(SRC_FILES) les fichiers .c existant dans le repertoire src ($(SRC_DIR)) et en les remplaçant par leur version objet contenue dans
# le repertoire obj ($(OBJ_DIR))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Cible par défaut lorsque l'on ne renseigne rien
all: main

# Cible pour l'exécutable
# Crée le fichier executable main en compilant l'ensemble de fichiers objets contenus dans la variable $(OBJ_FILES)
main: $(OBJ_FILES)
	gcc -o main $(OBJ_FILES)

# Règle générique pour la compilation des fichiers objets à partir des fichiers source : 
# pour chaque fichier compris dans le dossier source $(SRC_DIR) créer le fichier objet associé dans le dossier objet $(OBJ_DIR)
# $< représente le fichier source en cours
# $@ représente l'instruction avant les ':' , soit l'objet à créer en cours
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -o $@ -c $<


# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ_DIR)/*.o main
