# So Long

## Description

This project is a small 2D game designed to improve computer graphics skills. It involves working with textures, sprites, and basic gameplay elements. The objective is to create a game using the MiniLibX library, focusing on window management, event handling, colors, textures, and more.


## Screenshot
![map02 preview](./solong/public/map02.png)

## Game Rules

- The player's objective is to collect all the collectibles on the map and then escape by choosing the shortest route.
- Use the W, A, S, and D keys to move the main character.
- Movement is restricted to four directions: up, down, left, and right.
- The player cannot move through walls.
- The current number of movements must be displayed in the shell after each move.
- The game should be viewed in a 2D perspective (top-down or profile).
- The game does not need to be real-time.
- The theme and world of the game can be customized.

## Graphic Management

- The program displays the game's visuals in a window.
- Window management should be smooth, allowing seamless switching, minimizing, and other operations.
- Pressing the ESC key should close the window and exit the program cleanly.
- Clicking on the window's cross button should also close the window and exit the program cleanly.
- The use of images provided by the MiniLibX library is mandatory.

## Map Construction

- The map consists of three components: walls, collectibles, and free space.
- The map is represented by the following characters:
  - '0' for an empty space,
  - '1' for a wall,
  - 'C' for a collectible,
  - 'E' for the map exit,
  - 'P' for the player's starting position.
- The map must contain at least one exit, one collectible, and one starting position to be considered valid.
- Duplicate characters for the exit or starting position should display an error message.
- The map must be rectangular in shape.
- The map must be enclosed/surrounded by walls; otherwise, the program returns an error.
- A valid path must exist within the map.
- The program should be capable of parsing any valid map format, and if any misconfiguration is encountered, it should exit cleanly and return an "Error\n" message followed by an explicit error description of your choice.


Sample of `valid` map
``` bash
11111111
10000011
100P1C11
1E000011
11111111
```

## Usage Example

To run the game with a sample map, use the following command:

```
./so_long maps/map02.ber
```

