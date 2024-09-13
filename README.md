# Crusher-League-Board-Game

**Description**
League Crusher is a simple, console-based tile-matching game where players need to swap adjacent tiles to create lines of three or more matching tiles. The objective is to score as many points as possible by clearing tiles. The game board is generated randomly using a seed value provided by the player, and follows classic Candy Crush-style mechanics.

**League Crusher** is a simple, console-based tile-matching game where players need to swap adjacent tiles to create lines of three or more matching tiles. The objective is to score as many points as possible by clearing tiles. The game board is generated randomly using a seed value provided by the player, and follows classic Candy Crush-style mechanics.

**Features**

- **Tile Matching and Elimination:** Swap tiles to create lines of three or more matching tiles and eliminate them to score points.
- **Random Board Generation:** Generates a game board with random tiles based on a user-provided seed value.
- **Score Calculation:** Automatically calculates and displays the score after each move.
- **Game Over Detection:** Automatically ends the game when no valid moves are left.
- **Backtracking Algorithm:** Uses a backtracking algorithm to ensure no pre-existing matches when the board is generated.

**How to Play**
- Set Up the Game:
  Enter the board size, the maximum number of tile types (colors), and a seed for generating random numbers when prompted.
- Make Moves:
  Enter the coordinates of the source and target tiles to swap them. A valid move will result in eliminating tiles and scoring points.
- End Game:
  The game will automatically end when no valid moves are left. Your total score will be displayed at the end.

**Game Mechanics**
- Board Generation: The board is initialized as an N x N grid with random tile types, ensuring no pre-existing matches using backtracking.
- Movement Validation: Only valid swaps between adjacent tiles are allowed.
- Score Calculation: Points are awarded based on the number of tiles cleared in each move.
- Game Over Condition: The game ends when there are no more valid moves left on the board.
