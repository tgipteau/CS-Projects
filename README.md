# Projets CS

Ce dépôt rassemble des projets d'informatique fondamentale écrits en C, et inspirés par mes lectures et recherches personnelles.

Chaque projet contient un énoncé, des contraintes, des questions de recherche auxquelles je réponds dans des notes, puis des critères de validation (tests, sanitizers, mesures de performance).

## Projets

| Projet | Sujet | Dépôt |
|---|---|---|
| Table de hachage | Adressage ouvert avec sondage linéaire, clés chaînes, valeurs de type `union` | [hashing_library](https://github.com/tgipteau/CS-Projects/tree/main/hashing_library) |

## Lectures / Ressources

- [MIT 6.006 Introduction to Algorithms](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-spring-2020/)

## Outils et conventions

- Compilation : `-Wall -Wextra -Wpedantic`.
- Tests exécutés avec `-fsanitize=address,undefined`.
- Mesures de performance faites sans sanitizers, avec `-O2`.
