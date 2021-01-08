# Battleships
---

# Instructions:

## Using preset boards
- Preset boards are to be defined at `./res/presetBoard1.txt` and `./res/presetBoard2.txt` in plaintext format (see example [^example])
- Upon loading the preset board is validated whether it has the right amount of every shit type, if it has any collisions, etc
- If a preset file is missing or is invalid for a certain player that player is prompted to create a board using the Board builder

## Board builder
- The board builder is used for interactively creating a valid board.
- You can add new ships, edit already placed ships, reset the whole board and commit the newly created valid board

## Gameplay
- Players take turns attacking each other
- Each turn, before attacking, the player can ask to see their own board


[^example]: Example for preset board file
```
1 0 0 0 0 0 1 1 1 0
1 0 0 0 0 0 0 0 0 0
1 0 1 1 1 0 1 0 1 0
0 0 0 0 0 0 1 0 1 0
1 0 0 0 1 0 1 0 1 0
1 0 1 0 1 0 1 0 1 0
0 0 1 0 0 0 0 0 0 0
0 0 0 0 1 1 1 1 1 1
0 1 0 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0 0
```
