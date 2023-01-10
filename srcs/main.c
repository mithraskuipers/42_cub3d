/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:38 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/10 13:08:50 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int	gameInit(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		msgErrExit("Error: No file or more than 1 file specified.\n", 1);
	initGame(game);
	initMapdata(&game->mapdata, argv);
	game->screen_width = GAME_WIDTH;
	game->screen_height = GAME_HEIGHT;
	return (0);
}

void	checkChar(t_game *game, char **map)
{
	int	j;
	int	i;
	int len;

	j = 0;
	i = 0;
	while (j < game->heightMap)
	{
		i = 0;
		len = (int)ft_strlen(map[j]);						// Waarom typecasting?
		while (i < len)
		{
			if (!ft_strrchr("01NESW ", map[j][i]))
				msgErrExit("Wrong characters included.", 1);
			i++;
		}
		j++;
	}
}

int	gameParsing(t_game *game)
{
	mapCheckExt(game);
	char *line;
	line = NULL;
	if (getMapCfg(game, line, &game->mapdata) == 1)
		msgErrExit("Your map is configured incorrectly.", 1);
	mapOpen(game);
	getMapFileDims(game, line);
	mapMemAllocator(game, &game->mapdata.map);
	mapMemAllocator(game, &game->cpy_map);
	mapOpen(game);
	mapRead(game);
	checkChar(game, game->mapdata.map);
	mapFloodfill(game, game->player.x, game->player.y);
	checkPlayerCount(game);
	return (0);
}

int	gameExecute(t_game *game)
{
	initPovDir(game, game->mapdata.map[game->player.y][game->player.x]);
	initPovPlane(game, game->mapdata.map[game->player.y][game->player.x]);
	initPlayerPos(game);
	initMLX(game);
	initTextures(game);
	if (!game->mlx42)
		msgErrExit("MLX failed.", EXIT_FAILURE);
	return (0);
}

int main(int argc, char **argv)
{
	t_game game;

	gameInit(&game, argc, argv);
	if (gameParsing(&game))
		return(cleanupEverything(&game));
	if (gameExecute(&game))
		return(cleanupEverything(&game));
	mlx_loop_hook(game.mlx42, &frameCallback, &game);
	mlx_loop(game.mlx42);
	mlx_terminate(game.mlx42);
	cleanupEverything(&game);
	// system ("leaks cub3D");
	return (0);
}

/*
Important (variable) names and their meaning:
vector:
	Simply an x and y coordinate in our 2D space.

game->pov->pos.x/pos.y (vector) (point):
	Refer to the player position in the map.
	The player position is a point in front of the camera plane.
game->pov->dir.x/dir.y (vector) (direction):
	Refer to the direction that the player is facing.
	The "length" of the direction does not matter. It serves only as a measure
	of "direction" when using the player position as reference.
game->pov->plane.x/plane.y (vector) (line):
	Refer to the camera plane of the player. So "plane" == "camera plane".
	Note: It is not truly a "plane" (= 3D), but rather a "line" (= 2D). 
	More concretely, the camera plane refers to the surface on the computer 
	screen. On the other hand, the dir.x/dir.y direction vector points "inside"
	the computer screen.
	The camera plane should always be perpendicular to the player direction.
	This means that when the player rotates, the camera plane also has to
	rotate. The corresponding rays will rotate automatically as well.
	The length (width) of the camera plane can be adjusted as you like.
	The player position is a point in front of the camera plane.
game->ray:
	In this game "rays" are send. 
	Rays always start at the player position and are sent to the camera plane.
	Remember that the camera plane is basically the computer screen. Here, we
	send rays toward the camera plane for each x-axis value on the camera plane.
	Also remember that the camera plane is dependent on the player direction,
	since the former is always perpendicular to the latter, crossing eachother
	by a 90 degrees angle.
fov (field of vision):
	The angle between the left-most ray and the right-most ray. You can imagine
	these lines to be diagonal lines starting at the player position, toward to
	first x-axis value and last x-axis value of the camera plane. 


TODO
rotation:
	game->dir.x/dir.y
Work in progress...:-)
pov (point of view) TODO
*/