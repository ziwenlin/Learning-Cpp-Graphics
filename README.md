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

Tools/Debugging:

- [ ] Game speed kunnen aanpassen met knoppen en/of slider.
- [ ] Optie maken om textures uit te zetten en dan kleuren gebruiken.

Bugs:

- [ ] Als FPS te laag is, kan de muis een snelle klik niet zien.

Interface:

- [ ] InteractionController om globale inputs op te vangen en af te handelen.

- [x] Class RoundedButton heeft pointer voor font.
- [x] Class RoundedStatusBar is klaar.
- [x] Class SmartTextureManager aanmaken

Gameplay:

- [x] Begin-scherm
- [x] Eind-scherm

Systeem:

- [ ] Assets laadsysteem
  - Dit systeem zoekt op basis van een input-string naar het gewenste bestand.
  - Wanneer er meerdere bestanden zijn met deze naam, gaat die ze allemaal inladen.
- [ ] Sounds afspeelsysteem
  - Zelfde laadsysteem als assets laadsysteem.

Sounds:

- [x] Punten verzamelen feedback
- [x] Game-over feedback
- [x] Acties/handelingen feedback
