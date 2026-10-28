# Projets CS

Ce dépôt rassemble des projets d'informatique fondamentale écrits en C. Ils m'ont été suggérés par Claude (Anthropic) d'après mes lectures et le cours MIT 6.006 (*Introduction to Algorithms*), avec pour objectif d'apprendre l'algorithmique et les structures de données en les implémentant moi-même.

Chaque projet suit la même démarche : un énoncé, des contraintes, des questions de recherche auxquelles je réponds dans des notes, puis des critères de validation (tests, sanitizers, mesures de performance).

## Projets

| Projet | Sujet | Dépôt |
|---|---|---|
| Table de hachage | Adressage ouvert avec sondage linéaire, clés chaînes, valeurs de type `union` | [hashing_library]([https://github.com/tgipteau/CS-projects/hashing_table](https://github.com/tgipteau/CS-Projects/tree/main/hashing_library)) |

## Outils et conventions

- Compilation : `-Wall -Wextra -Wpedantic`.
- Tests exécutés avec `-fsanitize=address,undefined`.
- Mesures de performance faites sans sanitizers, avec `-O2`.
