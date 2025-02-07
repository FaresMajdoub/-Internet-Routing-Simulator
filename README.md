# Internet Routing Simulator

## 📌 Description
Ce projet est une simulation du routage dans Internet à l'aide de **graphes pondérés orientés**.  
Il permet de modéliser un réseau de routeurs et d'implémenter des algorithmes d'optimisation du **plus court chemin**.  
Les performances des différentes méthodes sont analysées, avec une attention particulière aux points d'articulation et à la connectivité du réseau.

## 🚀 Fonctionnalités
- **Modélisation d’un réseau IP** sous forme de graphe pondéré.
- **Chargement des données** à partir d'un fichier texte contenant la topologie du réseau.
- **Implémentation et analyse des algorithmes** :
  - **Dijkstra** pour déterminer le plus court chemin.
  - **Détection des points d’articulation** pour identifier les routeurs critiques.
  - **Vérification de la connectivité globale du réseau**.
  - **Exploration d’autres algorithmes** de plus court chemin.
- **Tests unitaires avec Google Test** pour valider les implémentations.

## 🏗️ Structure du projet
```
📂 **src/** - Code source  
  ├── `Routeur.h` / `Routeur.cpp` (Gestion des routeurs)  
  ├── `Reseau.h` / `Reseau.cpp` (Implémentation du réseau)  
  ├── `Graphe.h` / `Graphe.hpp` (Implémentation du graphe)  
  ├── `main.cpp` (Programme principal)  
  ├── `tests/` (Tests unitaires Google Test)  
  ├── `CMakeLists.txt` (Compilation)  
  └── `docs/` (Documentation Doxygen)  
```

### Exécution de la simulation
```sh
./simulateur ../scenarios/reseau.txt
```
### Exécution des tests unitaires
```sh
./tests/test_reseau
```

## 📊 Exemples de Simulation
### ⚡ Plus court chemin (Dijkstra)
```plaintext
Routeur d'origine : Québec (port-theud)
Routeur destination : New York
Chemin trouvé : Québec → Montréal → New York
Temps total : 25ms
```
### ⚡ Vérification de la connectivité
```plaintext
Le réseau est fortement connexe : ✅ OUI
```
### ⚡ Points d’articulation (Routeurs critiques)
```plaintext
Routeurs critiques détectés : Montréal, Ottawa
```

## ✍️ Auteurs
**Fares Majdoub** - Université Laval, GLO-2100/IFT-2008  

## 📜 Licence
Sous licence **MIT**.

