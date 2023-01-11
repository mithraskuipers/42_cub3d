/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dagmarkramer <dagmarkramer@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:38 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 16:13:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int	game_init(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		msg_err_exit("Error: No file or more than 1 file specified.\n", 1);
	init_game(game);
	init_mapdata(&game->mapdata, argv);
	game->screen_width = GAME_WIDTH;
	game->screen_height = GAME_HEIGHT;
	return (0);
}

void	check_char(t_game *game, char **map)
{
	int	j;
	int	i;
	int	len;

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

int	game_parsing(t_game *game)
{
	char	*line;

	line = NULL;
	map_check_ext(game);
	if (get_map_cfg(game, line, &game->mapdata) == 1)
		msg_err_exit("Your map is configured incorrectly.", 1);
	map_open(game);
	get_map_file_dims(game, line);
	map_mem_allocator(game, &game->mapdata.map);
	map_mem_allocator(game, &game->cpy_map);
	map_open(game);
	map_read(game, line);
	game->heightMap = game->mapFileDims.y - game->whenMapMazeStart + 1;
	if (game->has_player == 0)
		msg_err_exit("Your map contains no player spawning point.", 1);
	check_char(game, game->mapdata.map);
	map_floodfill(game, game->player.x, game->player.y);
	check_player_count(game);
	return (0);
}

int	game_execute(t_game *game)
{
	init_pov_dir(game, game->mapdata.map[game->player.y][game->player.x]);
	init_pov_plane(game, game->mapdata.map[game->player.y][game->player.x]);
	init_player_pos(game);
	init_mlx(game);
	init_textures(game);
	if (!game->mlx42)
		msg_err_exit("MLX failed.", EXIT_FAILURE);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game_init(&game, argc, argv);
	if (game_parsing(&game))
		return (cleanup_everything(&game));
	if (game_execute(&game))
		return (cleanup_everything(&game));
	mlx_loop_hook(game.mlx42, &frame_callback, &game);
	mlx_loop(game.mlx42);
	mlx_terminate(game.mlx42);
	cleanup_everything(&game);
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

/******************************************************************************/
/* notes                                                                      */
/******************************************************************************/

/*
- game->pov.dir: direction vector_xy (= vector_xy)
	Simply the direction to which the player looks.
	It is a line.

- game->pov.pos: player position (= vector_xy)
	Simply a single point in the map.
	It is a point in front of the "camera plane".

- camera plane (= vector_xy)
	game->pov.plane
	Not really a plane, but a line.
	Is always perpendicular to the "direction vector_xy".
	It is the horizontal line you would reach if you look straight ahead.
	It represents the computer screen. The 2D window of your game (eg. 480x360)
	By definition (?) you always touch exactly the center of the camera plane.

- ray:
	Line that starts at the player position and goes through the "camera plane".

- ray direction (= vector_xy):
	game->ray.dir
	The x and y components are used by the DDA algorithm.
	"direction vector_xy" + part of the "camera plane"
	Here, part of the "camera plane" is expressed in terms of proportion of the
	camera plane length, and is the distance between A and B, where..
	A: Where the direction vector_xy crosses the camera plane (i.e. its center)
	B: Where the ray vector_xy crosses the camera plane

	Example:
	                    part of camera plane
	                    (about 1/3 of right half of camera plane)
	                              |
	                              |    intersection around 1/3 of camera plane
	                            | |   /
	                            | V  /
	camera plane -> ------------|---/-------- <- ray vector_xy intersects
	                            |  /             direction vector_xy
	     direction vector_xy -> | / <- ray vector_xy
	                            |/
	                            P <- player position vector_xy

	eg. The ray of interest crosses the camera plane about 1/3 of the camera
	plane's vector_xy, assuming you would start at the camera plane's center.
	The ray direction would then be computed as follows:
	ray of interest = ("direction vector_xy" + (1/3 * "camera plane vector_xy"))

- field of vision (fov)
	Refers to the observable world. It is often expressed in degrees.
	The higher the fov, the more of the world is visible.

	Some insights regardins fov:
	- If the direction vector_xy and the camera plane (measured from its center)
	have the same length, then the fov is always 90 degrees.

	- If the direction vector_xy is much longer than the camera plane (measured
	from its center), then the fov is much narrower than 90 degrees.

	- If the direction vector_xy is much shorter than the camera plane (measured
	from its center), then the fov is much wider than 90 degrees. The max width
	is a theoretical 180 degrees.

- rotation
	If the player rotates, then the camera plane also has to rotate.
	This makes sense, because it is the camera plane that represents your
	computer screen. You want the computer screen to depict images depending
	on where your player is looking at.

	If the player is rotated, you need to rotate the camera plane vector_xy.
	You can rotate a vector_xy by multiplying the vector_xy with the "rotation 
	matrix"
	
	rotation matrix
	[cos(a) -sin(a)]
	[sin(a)  cos(a)]
*/