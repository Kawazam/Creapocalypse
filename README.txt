# Creapocalypse by Kawazam (Mathieu GARSAULT)

Voici mon rendu, malheureusement incomplet, du projet Creapocalypse. Les raisons de ce rendu incomplet sont principalement le manque de temps pour le réaliser, même si j'ai pu travailler dessus quelques heures par jours, mon travaille me prenait énormément de temps et m'a empêché de le finaliser comme je le souhaitais.

## Fonctionnalités exploitables :

- Affichage d'une map en vue du dessus en tiles et caméra fluide :
	- la mise en place de la map est réalisée dans la classe Map (Map.h & Map.cpp).
	- l'affichage de la map se fait dans le GameManager.cpp à la ligne 106.
	- le mouvement de la caméra se fait dans le GameManager.cpp dans la fonction MoveCamera() à la ligne 241 (elle est appelée dans GameManager::Update() à la ligne 90 lorsqu'elle est amenée à se déplacer).
- La classe fonctionnelle Entity (Entity.h & Entity.cpp).
- Les classes Alien, Farmer et Tower dérivées de Entity (fichiers .h & .cpp portant le même nom).
- Les tirs des aliens et des tourelles sont instanciés dans une list dans ShotSystem.cpp à la ligne 30.
- Les Aliens sont également instanciés dans une list dans GameManager.cpp à la ligne 288.
- Les Aliens :
	- Les aliens ont plusieurs types, un Tank (plus lent mais plus résistant) et un Runner (plus rapide mais plus faible), chacun est créé à partir de AlienFactory.cpp aux lignes 36 et 46.
	- Un alien apparaît lorsque la touche Espace est pressée (GameManager.cpp ligne 153)
	- Lorsqu'un alien apparaît, son type est déterminé aléatoirement (AlienFactory.cpp ligne 56) ainsi que sa position de départ (GameManager.cpp lignes 264 à 284)
	- Lorsqu'un alien se trouve à porté du centre de la carte, il commence à tirer droit devant lui avec un délai entre chaque tir (Alien.cpp ligne 29)
- Les Tourelles :
	- Les tourelles ont plusieurs types, Short Range, Long Range, Missile et Wall, chacune d'elle sont une classe enfant de la classe Tower.
	- La sélection du type de tourelle se fait avec les touches 1, 2, 3, 4 du clavier (GameManager.cpp lignes 156 à 171)
	- L'apparition d'une tourelle se fait avec un clic droit de la souris (GameManager.cpp ligne 216) et prend comme position d'apparition la position de la souris
- Les fonctions Shoot() de Farmer et Move() de Tower ont été override à partir de Entity, empêchant de les utiliser par inadvertance (Farmer.h ligne 13 et Tower.h ligne 13)

## Fonctionnalités prévus à l'avenir :

Beaucoup d'ajouts sont prévu comme la mise en place d'une IA pour les aliens, modifiant leurs direction pour s'attaquer aux bâtiments ou aux tourelles sur leur chemin.

Les fonctionnalités de tirs n'ont pas été aboutis, aucune collision ne s'execute et donc il n'y a pas de modification de point de vie.

Aucun bâtiment n'est pour le moment apparent, ni sur la carte, ni dans le code.

Le Fermier n'apparait pas et son déplacement n'est pas finalisé.

Les tourelles ne tirent pas lorsqu'un alien se trouve à proximité (et ça je sais pas pourquoi).