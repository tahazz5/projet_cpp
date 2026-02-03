# projet_cpp

Moteur d'échecs en C++ avec interface console et interface Qt optionnelle.

## Fonctionnalités
- Génération de coups pseudo-légaux (moteur de base).
- IA simple (minimax + évaluation matérielle).
- Interface console interactive.
- Interface Qt (optionnelle) avec affichage du plateau et saisie de coups.

## Compilation (console)
```bash
make -C src clean
make -C src
```

## Compilation (Qt optionnel)
Le build Qt est activé avec `USE_QT_GUI=1` et nécessite Qt installé.
Exemple (adaptez les flags Qt à votre installation) :
```bash
make -C src clean
make -C src USE_QT_GUI=1 \
  QT_CXXFLAGS="$(pkg-config --cflags Qt5Widgets)" \
  QT_LDFLAGS="$(pkg-config --libs Qt5Widgets)"
```

## Lancer
```bash
./src/test_poo
```

## Utilisation (console)
- Entrez un coup au format `e2e4` (ou `e7e8q` pour promotion).
- `help` pour l'aide, `quit` pour quitter.

## Notes
L'interface Qt est optionnelle : si Qt n'est pas installé, le binaire par défaut
utilise l'interface console.
