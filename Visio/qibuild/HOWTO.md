NAO_SLAM
========

Cross-compilation NAOQI
-----------------------

1. Récupérer les toolchains :  
Créer dans ce dossier un lien symbolique [path_to_sdk] vers la SDK
    * `naoqi-sdk-X.X.X-linux64` (pour une utilisation en local)
    * `linux64-nao-atom-cross-toolchain-X.X.X` (pour une vraie cross-compilation)

2. Compilation :  
    * Créer un dossier `./src/[projet]/build` dans le projet en cours
    * Y ouvrir une console
    * `cmake -DCMAKE_TOOLCHAIN_FILE=[path_to_sdk]/toolchain-pc.cmake ..`
    * `make`
    * `sudo make install`
    * `export LD_LIBRARY_PATH=[path_to_sdk]/lib/`
    * Exécuter le fichier créé dans `/usr/local/bin/`