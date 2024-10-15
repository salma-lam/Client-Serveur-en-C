# Communication Client-Serveur en C

## Description

Ce mini projet consiste en le développement d'un système client-serveur en C. Le système permet à un client de demander la liste des fichiers et dossiers présents dans le répertoire courant d'un serveur et d'afficher cette liste à l'écran.

## Fonctionnalités

- **Serveur** : 
  - Écoute les requêtes entrantes sur un port spécifié.
  - Traite les requêtes en accédant au système de fichiers.
  - Renvoie la liste des fichiers et dossiers au client.

- **Client** : 
  - Établit une connexion avec le serveur.
  - Envoie une requête pour la liste des fichiers.
  - Reçoit et affiche la liste des fichiers à l'utilisateur.

## Technologies Utilisées

- Langage : C
- Sockets réseau pour la communication bidirectionnelle
- Manipulation des répertoires et des fichiers

## Installation

1. Clonez le dépôt :

    ```bash
    git clone https://github.com/salma-lam/Client-Serveur-en-C.git
    cd Client-Serveur-en-C

2. Compilez les fichiers source :
   ```bash
   gcc -o serveur serveur.c
   gcc -o client client.c
   ./serveur
   ./client
