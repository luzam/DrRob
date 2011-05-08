READMEDr.Robotnik Mean Bean Machine Projet C++V 1.0Antoine Hoarau et Lucas Zamuner ROB4//////////////////////////////////////////////////1) Grandes lignes du projet
Nous avons tenté de reproduire le jeu SEGA Dr.Robotnik initialement prévu pour MégaDrive, en l’adaptant pour plus de joueurs Humains et AI.//////////////////////////////////////////////////2) Lancement du programme
* Sans arguments : le jeu se lance avec une résolution de 800*600 px.* Avec arguments SCREEN_W SCREEN_H : le jeu se lance en résolution personnalisée.* Avec arguments 0 0 : le jeu se lance en plein écran, à la résolution du bureau.//////////////////////////////////////////////////3) Lancement d’une partie 
* Sur l’écran d'accueil :   - Echap quitte le programme proprement.  - Entrée passe à l’écran suivant.
  - Dans les menus, backspace revient à l'écran d'avant.* Ecran choix du nombre de joueurs :  - Il faut jouer avec les touches gauche et droite pour augmenter ou diminuer le nombre de joueurs Humains ou AI (haut et bas)
* Ecran start et controls : 
  - Des commandes sont attribués par défaut pour 4 joueurs max(haut bas gauche droite pour joueur 1, zqsd pour 2 etc)
  - On peut bien entendu choisir ses commandes persos par le menu commandes.

* LE JEU : 
  - Le but set de faire perdre les adversaires en remplissant leur ligne du milieu de blobs.
  - Pour cela, il faut effectuer des enchainements de 4 blobs de même couleur min pour envoyer des pierres chez l'adversaire.
  - La touche ECHAP quitte le jeu courant et revient au menu principal.
//////////////////////////////////////////////////

4) Le programme en detail

On commence par instancier un jeu drRob, que l'on lance avec go.
Il crée une interface graphique qui d'abord charge le menu et qui le redimensionne aux dimensions de l'écran ( pas l'inverse).
On décide du nombre de joueurs humains, AI, des commandes etc.
On rentre alors dans la boucle infinie.
Une fois START lancé l'interface va faire tous les redimensionnements nécessaires :
* Chargement des images, redimensionnement par rapport à la résolution d'écran (fonctionne pour n joueurs)
* Calculs des positions des différents dashboards, des offsets pour la positions des éléments des joueurs..
Le jeu est alors lancé, on va donc faire une boucle sur le tableau de commande des joueurs, qui vont modifier la position ou le comportement du double blob courant.
Pour chaque dashbord on effectue un go : 
C'est un incrément de temps qui met à jour tout le moteur physique (tourner les pièces , combo, pièce qui tombe etc…)
On blit le tout et on reboucle.

Les Ai sont soit easy (random), soit hard (essaye de mettre des couleurs ensemble).
//////////////////////////////////////////////////

5) Les points intéressants

Tout d'abord, la détection des zones de plus de 4 blobs a été un vrai challenge, nous forçant a utiliser un algorithme complexe type k-means. Le moteur physique gérant les rotations, les combos etc aura aussi été assez complexe a mettre en oeuvre.
Concernant l'interface, nous lisions au début dans un fichier image redimensionné des parties de l'image. Il s'avéra que suite au redimensionnement, des pixels se décalaient, donnant un rendu assez moche (un pixel en trop ou manquant).
Nous avons donc repris du début le sprite, calculé la taille blob resizé qui tombe juste, puis alloué un vecteur de surfaces pour chaque blobs, de chaque couleur. Les résultats ont été bien meilleurs.
Par manque de temps, nous n'avons pas pu consacrer beaucoup de temps à l'IA, qui est néanmoins très intéressante.
Globalement, ce projet était un vrai défi, bien plus complexe que le tétris, et il nous aurait fallut quelques semaines en plus pour arriver à un résultat parfait.
//////////////////////////////////////////////////

6) Ce qui manque

* UN MAKEFILE : en effet, nous n'avons pas réussi à extraire un makefile du projet Codeblocks. Le projet compile très bien sous codeblocks Linux(Fac) et Windows(chez nous), mais cmake n'a pas fonctionné jusqu'au bout, car nous n'avons pas pu l'installer sur les pc de la fac(trop lourd).
* Le valgrind complet : nous avons essayé de libérer la mémoire au maximum, mais certainement des erreurs subsistent. Le ssh étant trop lent, nous n'avons pas pu gérer a distance (sur les pc de la fac) les problèmes de fuite mémoire.

//////////////////////////////////////////////////


