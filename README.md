# Graphics in C++

Welkom in mijn avontuur bij het leren van Graphics programming in C++.

## Setup

Dit project maakt gebruik van CMake. Alle benodigde bestanden zijn daar gedefineerd.

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
- [ ] Vogel springt te hoog bij de eerste sprong.
  - Dit komt door delta time. Deze verandert met meer dan factor 2 bij de start.
- [x] Game-over eindscherm triggert niet bij death.
  - Dit kwam door het niet goed afhandelen van keyboard-events.

Interface:

- [ ] Scoreboard
  - Punten bijhouden ergens op het scherm.
  - Highscore daaronder ook tonen.
- [ ] Keyboard indicatie
  - Als je een long press actie uitvoert, is het handig om te zien hoe lang je deze moet indrukken.
  - [x] Toon deze ergens onder het scherm.
  - [ ] Elke key krijgt zijn eigen indicatie. Deze worden op elkaar gestapeld.
- [ ] Begin-scherm
  - [x] Een keer klikken met de muis moet het spel starten.
  - [ ] Toevoegen van achtergrond achter de titel en de instructie.
    - Note: Flappy bird moet nog naast de achtergrond te zien zijn.
    - Als dat niet lukt moet de vogel op een andere plek komen.
- [ ] Eind-scherm
  - [ ] Knoppen moeten even groot zijn.
  - [ ] Functionaliteit van 'resurrect'-knop toevoegen.
    - Deze scherm moet met de game-state communiceren om verder te mogen gaan.
    - Eerst bedenken hoe de communicatie moet gaan verlopen.
  - [x] Spatiebalk ingedrukt houden, leidt je naar het hoofdmenu.

Gameplay:

- [x] Springen met spatiebalk.
- [x] Springen met muis.

Systeem:

- [ ] Screen layer systeem
  - Dit systeem zorgt voor het afhandelen van schermlagen.
  - Elke class hoeft niet zijn bij te houden welke dat die de voorgrond staat.
- [ ] User interface builder
  - Zorgt voor het plaatsen en behouden van UI-elementen in een grid.
  - Nu is alles hardcoded geplaatst met variabele meetstaven, dat is niet zo makkelijk te onderhouden.
- [ ] Animatie systeem
  - Gescripte verplaatsing van objecten na een event.
  - Keuzes: lineaire en/of smooth transitie.
- [ ] Interaction controller
  - Opvangen van globale inputs en de inputs in de class afhandelen.
- [x] Assets laadsysteem
  - Dit systeem zoekt op basis van een input-string naar het gewenste bestand.
  - Wanneer er meerdere bestanden zijn met deze naam, gaat die ze allemaal inladen.
- [x] Sounds afspeelsysteem
  - Zelfde laadsysteem als assets laadsysteem.

Sounds:

- [x] Punten verzamelen feedback
- [x] Game-over feedback
- [x] Acties/handelingen feedback
