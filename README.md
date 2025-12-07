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

Bugs:

- Mouse
  - Als FPS te laag is, kan de muis een snelle klik niet zien.

Interface:

- InteractionController om globale inputs op te vangen en af te handelen.

Gameplay:

- Begin-scherm
- Eind-scherm

Systeem:

- Assets
  - Een systeem die assets kan bijhouden.
- Sounds
  - De game class moet zelf bijhouden welke geluiden mag worden afgespeeld.

Voltooid:

- Class RoundedButton heeft pointer voor font.
- Class RoundedStatusBar is klaar.
- Class SmartTextureManager aanmaken

- Geluid afspelen
  - Punten verzamelen feedback
  - Game-over feedback
  - Acties/handelingen feedback
