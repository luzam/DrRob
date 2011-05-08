READMEDr.Robotnik Mean Bean Machine Projet C++V 1.0Antoine Hoarau et Lucas Zamuner ROB4//////////////////////////////////////////////////1) Grandes lignes du projet
Nous avons tent� de reproduire le jeu SEGA Dr.Robotnik initialement pr�vu pour M�gaDrive, en l�adaptant pour plus de joueurs Humains et AI.//////////////////////////////////////////////////2) Lancement du programme
* Sans arguments : le jeu se lance avec une r�solution de 800*600 px.* Avec arguments SCREEN_W SCREEN_H : le jeu se lance en r�solution personnalis�e.* Avec arguments 0 0 : le jeu se lance en plein �cran, � la r�solution du bureau.//////////////////////////////////////////////////3) Lancement d�une partie 
* Sur lՎcran d'accueil :   - Echap quitte le programme proprement.  - Entr�e passe � lՎcran suivant.
  - Dans les menus, backspace revient � l'�cran d'avant.* Ecran choix du nombre de joueurs :  - Il faut jouer avec les touches gauche et droite pour augmenter ou diminuer le nombre de joueurs Humains ou AI (haut et bas)
* Ecran start et controls : 
  - Des commandes sont attribu�s par d�faut pour 4 joueurs max(haut bas gauche droite pour joueur 1, zqsd pour 2 etc)
  - On peut bien entendu choisir ses commandes persos par le menu commandes.

* LE JEU : 
  - Le but set de faire perdre les adversaires en remplissant leur ligne du milieu de blobs.
  - Pour cela, il faut effectuer des enchainements de 4 blobs de m�me couleur min pour envoyer des pierres chez l'adversaire.
  - La touche ECHAP quitte le jeu courant et revient au menu principal.
//////////////////////////////////////////////////

4) Le programme en detail

On commence par instancier un jeu drRob, que l'on lance avec go.
Il cr�e une interface graphique qui d'abord charge le menu et qui le redimensionne aux dimensions de l'�cran ( pas l'inverse).
On d�cide du nombre de joueurs humains, AI, des commandes etc.
On rentre alors dans la boucle infinie.
Une fois START lanc� l'interface va faire tous les redimensionnements n�cessaires :
* Chargement des images, redimensionnement par rapport � la r�solution d'�cran (fonctionne pour n joueurs)
* Calculs des positions des diff�rents dashboards, des offsets pour la positions des �l�ments des joueurs..
Le jeu est alors lanc�, on va donc faire une boucle sur le tableau de commande des joueurs, qui vont modifier la position ou le comportement du double blob courant.
Pour chaque dashbord on effectue un go : 
C'est un incr�ment de temps qui met � jour tout le moteur physique (tourner les pi�ces , combo, pi�ce qui tombe etc�)
On blit le tout et on reboucle.

Les Ai sont soit easy (random), soit hard (essaye de mettre des couleurs ensemble).
//////////////////////////////////////////////////

5) Les points int�ressants

Tout d'abord, la d�tection des zones de plus de 4 blobs a �t� un vrai challenge, nous for�ant a utiliser un algorithme complexe type k-means. Le moteur physique g�rant les rotations, les combos etc aura aussi �t� assez complexe a mettre en oeuvre.
Concernant l'interface, nous lisions au d�but dans un fichier image redimensionn� des parties de l'image. Il s'av�ra que suite au redimensionnement, des pixels se d�calaient, donnant un rendu assez moche (un pixel en trop ou manquant).
Nous avons donc repris du d�but le sprite, calcul� la taille blob resiz� qui tombe juste, puis allou� un vecteur de surfaces pour chaque blobs, de chaque couleur. Les r�sultats ont �t� bien meilleurs.
Par manque de temps, nous n'avons pas pu consacrer beaucoup de temps � l'IA, qui est n�anmoins tr�s int�ressante.
Globalement, ce projet �tait un vrai d�fi, bien plus complexe que le t�tris, et il nous aurait fallut quelques semaines en plus pour arriver � un r�sultat parfait.
//////////////////////////////////////////////////

6) Ce qui manque

* UN MAKEFILE : en effet, nous n'avons pas r�ussi � extraire un makefile du projet Codeblocks. Le projet compile tr�s bien sous codeblocks Linux(Fac) et Windows(chez nous), mais cmake n'a pas fonctionn� jusqu'au bout, car nous n'avons pas pu l'installer sur les pc de la fac(trop lourd).
* Le valgrind complet : nous avons essay� de lib�rer la m�moire au maximum, mais certainement des erreurs subsistent. Le ssh �tant trop lent, nous n'avons pas pu g�rer a distance (sur les pc de la fac) les probl�mes de fuite m�moire.

//////////////////////////////////////////////////


