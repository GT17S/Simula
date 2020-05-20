# Simula

Simulateur de protocole TCP/IP ayant pour but la manipulation des réseau, offrant un outil pédagogique au enseignements de réseau dans le secondaire et le supérieur.

Il est réalisé dans le cadre de l'UE projet en L3 informatique à l'Université de Versailles Saint-Quentin en Yvelines, encadré par Mme Leila Kloul.

## Installation
### Pré-requis
Pour assurer le bon fonctionnement du simulateur et permettre la compilation statique du code, un certain nombre d'outils et  de bibliothèques doivent être présents sur la machine:

Pour obtenir le projet il suffit de le cloner avec la commande:
` git clone https://github.com/Groupe-TCP-IP/Simula.git/ `

### Linux
* Compilateur GCC : >=8.2
* Boost: >= 1.65
* QT5 : >=5.14
* CMake: >=3.15

#### Commande bash:
 `sudo apt install build-essential
cmake libboost-all-dev libfontconfig doxygen git
 `
#### Installer QT5:
`wget http://download.qt.io/official_releases/qt/5.14/5.14.0/qt-opensource-linux-x64-5.14.0.run `
`chmod +x qt-opensource-linux-x64-5.14.0.run`
`./qt-opensource-linux-x64-5.14.0.run
`

## Compilation
Une fois dans le répertoire racine du projet (simula/), vous devez initialiser CMake avec le script de compilation fournis dans l'archive.

Entrez les commandes suivantes à la racine du projet:
`cmake -G "Unix Makefiles"` lance le moteur de compilation 


`make -j2` compile sur deux fils d'exécution

`make run` exécute le programme depuis le répertoire source


D'autres commandes sont disponibles telles que:

`make doc` qui génére la documentation du projet en appelant Doxygen 

`firefox doc/html/index.html &` permet d'afficher la documentation dans le navigateur firefox

`make clean` qui vide les fichiers de cache de CMake 

`make install` qui copie le binaire crée dans le répertoire prédéfini

## Utilisation

Une fois le code correctement compilé et exécuté l'utilisateur se retrouve devant l'interface principale depuis laquelle il peut commencer à manipuler un réseaux soit à partir de rien, soit en important des fichiers de configuration.

###Sauvegarde 
Lors de la sauvegarde de la topologie ou d'un export vers un fichier PNG, DOT et XML, les fichiers sont générés dans le même répertoire que l'éxécutable.





## Contribution
Seuls les membres de l'organisation pouvant actuellement prendre part à se projet et le maintenir.

Cependant une fois la date de dépôt dépassée, une pull request pertinente et correctement formulée sera toujours la bienvenue.
 

## License
Avant la remise du projet au responsable de l'UE, la licence de ce projet n'est pas encore définie et sera peut être amenée à changer.