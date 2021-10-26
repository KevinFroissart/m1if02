J'ai eu le temps de finir le TP, et de vérifier l'utilisation de la mémoire à
l'aide  de `valgrind`. J'ai également pu implémenter l'arithmétique des
circulateurs (avancement ET recul).

En revanche, je ne me suis pas attardé sur les indices négatifs dans la
Séquence: ayant utilisé le type `size_t` dès le début du TP, les indices
que j'utilise sont automatiquement convertis en unsigned long par le compilateur
(gcc sous Linux). Je n'ai donc pas pris le temps de faire la conversion à sa
"vraie" valeur négative (si tant est qu'elle existe). Je ne me suis donc
uniquement assuré que l'indice en question était bien compris entre 0 et la
capacité maximale de la séquence (toutefois, ayant traité cette opération
via l'opérateur modulo %, l'indice résultant ne correspond pas au modulo de
l'indice négatif, puisque le décalage d'un `unsigned long` est une puissance
de 2, alors que le modulo est la capacité de la séquence).


!!!! HOW-TO !!!

Pour compiler les programmes, il suffit de se placer dans le dossier d'une
partie du TP et d'exécuter la commande `make` : un exécutable `main` est alors
créé.

La commande `make clean` permet de nettoyer le dossier source en supprimant les
fichiers objet (.o), les fichiers valgrind (vgcore.*) et les exécutables.
