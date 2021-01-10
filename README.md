Battleships
---

# Pre-game

## Compilation
- The binary can be compiled by running `make` or `mkdir bin && g++ lib/*.cpp src/main.cpp -o bin/battleships.out` (or `.exe` if on Windows[^1]) from the project root

## Using preset boards (optional)
- Preset boards are to be defined at `./res/presetBoard1.txt` and `./res/presetBoard2.txt` in plaintext format (see example [^preset])
- Upon loading the preset board is validated (right amount of each ship type, presence of collisions, etc)
- If a preset file is invalid or missing the player is prompted to create a board using the Board builder

## Running
- The game is started by running `./bin/battleships.out` (or `.exe` if on Windows[^1]) from the project root

# In-game

## Board builder
- The board builder is used for interactively creating a valid board
- You can add new ships, edit already placed ships, reset the whole board and commit the newly created valid board

## Gameplay
- Players take turns attacking each other
- Each turn, before attacking, the player can ask to see their own board
- When a player sinks all of their opponent's ships they win and game is terminated

[^preset]: Example for preset board file
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
    - Four    ships of length 2
    - Three   ships of length 3
    - Two     ships of length 4
    - One     ship  of length 6

[^1]: If on Windows, please use the `Git Bash` terminal because, by default, `cmd` doesn't support ANSI and extended ASCII characters
