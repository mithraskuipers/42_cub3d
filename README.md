# 42_cub3d

## Introduction

Welcome to our Cub3d project! Dagmar Kramer and myself worked together as a team to create a simple 3D game using raycasting techniques. Our game is inspired by the classic Wolfenstein 3D, and we've added some fun features to make it our own.

In this project, we've used the C programming language and the miniLibX graphics library to build the game from scratch.

We're excited to share our project with you. Please feel free to explore the code and leave us any feedback you have.

## Raycasting and the Math Behind it

The Cub3d game utilizes raycasting techniques to create a 3D effect in a 2D environment. Raycasting involves simulating the behavior of light rays to render a 3D scene from a 2D map. To achieve this, several mathematical calculations are involved. Here's a brief overview of the math used in our raycaster:

1. Trigonometry: Trigonometric functions such as sine and cosine are essential for determining the angles at which rays are cast. These angles are used to calculate the ray direction and perform various calculations during raycasting.

2. Line Intersection: The raycaster traces rays from the player's position to the walls of the game world. To determine where a ray intersects with a wall, we use line intersection formulas. These formulas involve vector operations and algebraic equations.

3. Distance Calculation: To render the walls correctly, we need to calculate the distance between the player and the wall intersection point. This calculation is based on the Pythagorean theorem or other distance formulas.

4. Texture Mapping: In order to apply textures to the walls, we map the 2D textures onto the 3D walls based on the intersection points. This process involves converting the 3D coordinates to texture coordinates using mathematical transformations.

During the development of Cub3d, we extensively applied these mathematical concepts to achieve accurate rendering, depth perception, and movement within the game.

## Compilation

To compile the Cub3d game, follow these steps:
1. Run `make` command in the project directory.

## Usage

To run the Cub3d game, follow these steps:
1. Execute the command `./cub3D maps/codam.cub` in the project directory. You can also use another map file instead of `maps/codam.cub`.
2. Use the WASD keys and arrow keys to move and look around in the game.

![Screen Shot 2023-01-14 at 3 37 39 PM](https://user-images.githubusercontent.com/79095814/212477358-d4b33ea9-66c3-479d-aec5-e4385a7c9c44.png)
![Screen Shot 2023-01-14 at 3 38 18 PM](https://user-images.githubusercontent.com/79095814/212477363-3b07859a-2a26-4e1c-9ba7-849fe023bc39.png)
![Screen Shot 2023-01-14 at 3 38 32 PM](https://user-images.githubusercontent.com/79095814/212477364-bfd9816b-71a2-44fe-b8da-1f656718b38d.png)
