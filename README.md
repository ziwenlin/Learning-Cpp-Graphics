# Programmeren van Graphics in C++

Welkom in mijn avontuur van het leren van Graphics in C++.

## Setup

Dit project maakt gebruik van CMake.

## Structuur van bestanden en mappen

| Map     | Beschrijving               |
|---------|----------------------------|
| build   | Compiler bestanden         |
| include | Header (.h) bestanden      |
| src     | Source (.cpp) bestanden    |
| tests   | Unit test (.cpp) bestanden |

## Projectplanning

Debugging:

- Game speed kunnen aanpassen met knoppen en/of slider.
- Optie maken om textures uit te zetten en dan kleuren gebruiken.

Interface:

- RoundedStatusBar afmaken.
- RoundedButton heeft pointer font nodig.
  - Dit is om de class niet gelijk alles hoeft te initialiseren.
- InteractionController om globale inputs op te vangen en af te handelen.

Gameplay:

- Geluid afspelen
  - Punten verzamelen feedback
  - Game-over feedback
  - Acties/handelingen feedback
- Begin-scherm
- Eind-scherm
