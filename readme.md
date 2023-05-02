L3_I-ProjetOs

Présentation :

Voici le Projet final de l’UE système d’exploitation L3-Informatique à Cergy Paris Université.
Ce projet à pour but d’implémenter un logiciel de simulation de tournoi sportif (football). En effet, le nombre des équipes est fixé dès le départ, chaque match est exécuté avec un processus et à chaque fois on a deux équipes gagnantes dans le premier tour, elle passent au deuxième tour. deux matchs du même tour peuvent sans problème être simultanés grace au mecanisme de synchronisation.

- Récupérer les données des équipes dans un fichier d’entrée
- Vérifier que le nombre d’équipes est une puissance de 2
- génération aléatoire des équipes pour simuler les matchs entre eux deux à deux 
- Utilisation des threads pour gérer le dérouler des tournois tour par tour 
- Récupération des équipes gagnantes pour les faire jouer au prochain tour 


Ce code a été réalisé par Omar CHAKER, cylia BELKACEMI , feriel MALEK le 3 Avril 2023.

- Une documentation réalisée avec Doxygen est disponible dans le répertoire Projet/html

- Le rapport est disponible aussi dans le dossier Projet dans les formats .odt et .pdf

- Le code source est disponible dans le dossier `src`.

Composition du projet :
	

- data: contient les fichiers de configuration squads_test.csv et squads.txt qui contiennent les équpes avec leurs noms et leurs informations.

- Un fichier Makefile qui permet de compiler le code facilement et permet de générer les fichiers objet.


- Un fichier header.h qui contient les différentes structures qu’on utilise dans les fonctions.

-alloc_init.c : initalisation des équipes, l’allocation mémoire d’un tableau d ‘équipe, afficher le tebleau d’équipes et la libétation de ce dernier, la libération d’un tableau match et initialisation de la structure tabEquipes.

- In_out.c : transforme un fichier csv en tableau de structures d'équipes. Esuite lit son contenu avec la fonction fopen.

- utility.c : permet d'extraire des informations d'un fichier texte et d'une chaîne de caractères.
 La fonction "conf_extract" permet d'extraire des informations de configuration à partir d'un fichier texte et de les stocker dans des variables passées en paramètres.
  La fonction "strextract" permet d'extraire une sous-chaîne d'une chaîne de caractères en spécifiant un caractère de début et un caractère de fin.
   
   La fonction rand_generate_squads prend en entrée le nombre d'équipes à générer et une structure TabEquipes qui contient toutes les équipes disponibles. Elle génère un tableau aléatoire d'équipes en utilisant la fonction rand().
   La fonction estExisteEquipe vérifie si une équipe donnée existe dans un tableau d'équipes TabEquipes en parcourant le tableau à la recherche de l'ID de l'équipe donnée.



   La fonction initTabEquipes initialise une structure TabEquipes en allouant de la mémoire pour stocker un certain nombre d'équipes. 
   
   la fonction estVideTabEquipes vérifie si une structure TabEquipes est vide ou non, en comparant le nombre d'équipes qu'elle contient avec 0.
   
 - simulation.c : ce fichier gère le nombre d’équipes en lice, vérifie bien qu’on a un nombre de puissance de 2, puis simule les matchs entre les équipes deux à deux ensuite un simule des tours et pour chaque tour récupère les gagnants et les fais jouer pour le prochain tour jusqu’à ce qu’il reste que une équipe gagnante à la fin.

 - main.c : exécution du programme 
   

Utilisation : On se positionne dans le répertoire du projet : 


- Pour compiler le code on tape la commande make pour générer tous les fichiers objets et puis on exécute avec ./nom_du_programme

- L’utilisateur peut au début saisir manuellement le nombre d’équipes qu’il veut faire jouer. 

- Si on veut générer la documentation via la ligne de commande on tape la commande make doc .
