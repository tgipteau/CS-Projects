# Table de hachage à adressage ouvert

## Énoncé

Écrire une table de hachage à clés chaînes (la table possède ses clés, c'est-à-dire qu'elle en fait une copie) et à valeurs de type `union` :

```c
typedef union {
    intptr_t  i;
    uintptr_t u;
    void     *p;
    char     *s;
} hm_value;
```

La table utilise l'**adressage ouvert** avec **sondage linéaire**.

## Contraintes

- Type opaque, noms préfixés, aucune variable globale.
- Échec d'allocation signalé par un code de retour.
- Opérations : création, destruction, insertion/mise à jour, lecture, suppression, nombre d'éléments.
- Redimensionnement automatique selon le facteur de charge.
- La suppression ne doit jamais rendre une clé existante introuvable.
- Aucune bibliothèque externe, aucun code recopié d'une implémentation existante. Lire des articles et des cours est permis et encouragé.

## Questions de recherche

Consigner les réponses dans un fichier `NOTES.md`.

1. Pourquoi choisit-on souvent une capacité égale à une puissance de deux, et comment calcule-t-on alors l'indice sans modulo ?
2. Qu'est-ce que le regroupement primaire (*primary clustering*), et pourquoi les performances du sondage linéaire se dégradent-elles quand le facteur de charge augmente ?
3. Comment supprimer dans un adressage ouvert sans casser les recherches ? Comparer au moins deux techniques et leurs coûts.
4. Quel est le coût amorti d'une insertion avec redimensionnement par doublement ? Le justifier.
5. Quelles propriétés exige-t-on d'une bonne fonction de hachage pour une table ? Implémenter FNV-1a, puis une seconde fonction au choix, et les comparer.
6. Qu'est-ce qu'une attaque par collisions (*hash flooding*), et quelle parade les langages modernes emploient-ils ?

## Critères de validation

- **Test différentiel** : suite de tests aléatoires (plusieurs centaines de milliers d'opérations) comparant la table à une structure de référence naïve écrite pour l'occasion (par exemple un tableau trié). La graine du générateur aléatoire est affichée afin de rejouer un échec.
- Zéro erreur et zéro fuite sous les sanitizers.
- **Benchmark** : 1 million d'insertions puis de lectures, pour des seuils de charge de 0,5, 0,7 et 0,9. Mesurer le temps (`clock_gettime(CLOCK_MONOTONIC)`) ainsi que la longueur moyenne et maximale des séquences de sondage. Commenter les résultats dans `NOTES.md`.

## Livrables

`hashmap.h`, `hashmap.c`, `test.c`, `bench.c`, `Makefile`, `NOTES.md`.

## Méthode conseillée

1. Écrire d'abord une première version simple, avec peu de tests.
2. Lire les sources pour répondre à chaque question de recherche et consigner les réponses dans `NOTES.md`.
3. Reprendre le code pour corriger ce que les lectures révèlent, puis ajouter le test différentiel et le benchmark.

## Pistes de lecture

- MIT 6.006 : séances sur les tableaux dynamiques (coût amorti) et sur le hachage.
- Sedgewick et Wayne, *Algorithms*, section sur le sondage linéaire.
- CLRS, chapitre sur les tables de hachage.
- Articles sur le *linear probing* et le *Robin Hood hashing*.

