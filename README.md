
# The Doge

The Doge is a 2D platformer game developed in C. The game features classic platforming mechanics where players navigate through levels, avoid obstacles, and collect items to progress.

## Features

- **2D Platformer Gameplay**: Jump, run, and dodge obstacles to complete levels.
- **Multiple Levels**: Each level presents unique challenges and designs.
- **Pixel Art Graphics**: Retro-style graphics that enhance the platforming experience.
- **Sound Effects**: Immersive sound effects that complement the gameplay.

## Installation

### Prerequisites

- C compiler (e.g., GCC)
- SDL2 library (for graphics and input handling)

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/titichayajojo/The-doge.git
   cd The-doge
   ```

2. Install SDL2:
   - On Ubuntu:
     ```bash
     sudo apt-get install libsdl2-dev
     ```
   - On MacOS (using Homebrew):
     ```bash
     brew install sdl2
     ```

3. Compile the game:
   ```bash
   gcc -o the_doge main.c -lSDL2
   ```

4. Run the game:
   ```bash
   ./the_doge
   ```

## Gameplay Instructions

- **Arrow Keys**: Move the character left or right.
- **Spacebar**: Jump.
- **Avoid Obstacles**: Navigate through the levels while avoiding traps and enemies.
- **Collect Items**: Pick up items to increase your score and progress.


## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

- SDL2 library for providing the necessary tools for game development.
- Classic 2D platformers that inspired the creation of this game.
