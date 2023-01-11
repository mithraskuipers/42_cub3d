/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dagmarkramer <dagmarkramer@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:38 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 11:40:19 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int	gameInit(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		msg_err_exit("Error: No file or more than 1 file specified.\n", 1);
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
		len = (int)ft_strlen(map[j]);
		while (i < len)
		{
			if (!ft_strrchr("01NESW ", map[j][i]))
				msg_err_exit("Wrong characters included.", 1);
			i++;
		}
		j++;
	}
}

int	gameParsing(t_game *game)
{
	map_check_ext(game);
	char *line;
	line = NULL;
	if (get_map_cfg(game, line, &game->mapdata) == 1)
		msg_err_exit("Your map is configured incorrectly.", 1);
	map_open(game);
	get_map_file_dims(game, line);
	map_mem_allocator(game, &game->mapdata.map);
	map_mem_allocator(game, &game->cpy_map);
	map_open(game);
	map_read(game);
	checkChar(game, game->mapdata.map);
	map_floodfill(game, game->player.x, game->player.y);
	check_player_count(game);
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
		msg_err_exit("MLX failed.", EXIT_FAILURE);
	return (0);
}

int main(int argc, char **argv)
{
	t_game game;

	gameInit(&game, argc, argv);
	if (gameParsing(&game))
		return(cleanup_everything(&game));
	if (gameExecute(&game))
		return(cleanup_everything(&game));
	mlx_loop_hook(game.mlx42, &frameCallback, &game);
	mlx_loop(game.mlx42);
	mlx_terminate(game.mlx42);
	cleanup_everything(&game);
	system ("leaks cub3D");
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
	Rays always start at the player position and are sent in a direction for 
	every x-axis value on the camera plane.	
game->ray.map.x/game->ray.map.y:
    Current location of the ray. It can be used to check if a ray has hit a will.
fov (field of vision):
	The angle between the left-most ray and the right-most ray. You can imagine
	these lines to be diagonal lines starting at the player position, toward to
	first x-axis value and last x-axis value of the camera plane. 
*/
