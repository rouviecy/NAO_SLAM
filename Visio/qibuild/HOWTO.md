NAO_SLAM
========

Cross-compilation NAOQI
-----------------------

1. Récupérer les toolchains :  
Créer dans ce dossier un lien symbolique [path_to_sdk] vers la SDK
    * `naoqi-sdk-X.X.X-linux64` (pour une utilisation en local)
    * `linux64-nao-atom-cross-toolchain-X.X.X` (pour une vraie cross-compilation)

2. Compilation :  
    * Créer un répertoire `build/` dans le projet en cours (à côté de `CMakeList.txt`)
    * `cd build/`
    * `cmake -DCMAKE_TOOLCHAIN_FILE=[path_to_sdk]/toolchain-[pc/atom].cmake ..`
    * `make`
    * le fichier généré se trouve dans `build/sdk/bin/`
    * `export LD_LIBRARY_PATH=[path_to_sdk]/lib/` si librairies introuvables