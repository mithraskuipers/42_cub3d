#include "./../includes/cub3d.h"

/*
arc tangent = inverse tangent = atan
tangent to degrees? arc tangent
*/

void	set_direction_vector(t_game *game)
{
	(void)game;
	/*
	if (game->mapdata.spawn_cardinaldir == 'N')
	{
		game->gamedata.dir_x = 0;
		game->gamedata.dir_y = -1;
		// game->gamedata.player_radians = degrees_to_radians(0);
		// game->gamedata.player_radians = 0;
	}
	else if (game->mapdata.spawn_cardinaldir == 'E')
	{
		game->gamedata.dir_x = 1;
		game->gamedata.dir_y = 0;
		// game->gamedata.player_radians = degrees_to_radians(90);
		// game->gamedata.player_radians = 90;
	}
	else if (game->mapdata.spawn_cardinaldir == 'S')
	{
		game->gamedata.dir_x = 0;
		game->gamedata.dir_y = 1;
		// game->gamedata.player_radians = degrees_to_radians(180);
		// game->gamedata.player_radians = 180;
	}
	else if (game->mapdata.spawn_cardinaldir == 'W')
	{
		game->gamedata.dir_x = -1;
		game->gamedata.dir_y = 0;
		// game->gamedata.player_radians = degrees_to_radians(270);
		// game->gamedata.player_radians = 270;
	}
	*/
}

void	set_camera_plane(t_game *game)
{
	if (game->mapdata.spawn_cardinaldir == 'N')
	{
		// game->gamedata.plane_x = -0.66;
		// game->gamedata.plane_y = 0;
		// game->gamedata.player_radians = degrees_to_radians(0);
		// game->gamedata.player_radians = 0;
	}
	else if (game->mapdata.spawn_cardinaldir == 'E')
	{
		// game->gamedata.plane_x = 0;
		// game->gamedata.plane_y = -0.66;
		// game->gamedata.player_radians = degrees_to_radians(90);
		// game->gamedata.player_radians = 90;
	}
	else if (game->mapdata.spawn_cardinaldir == 'S')
	{
		// game->gamedata.plane_x = 0.66;
		// game->gamedata.plane_y = 0;
		// game->gamedata.player_radians = degrees_to_radians(180);
		// game->gamedata.player_radians = 180;
	}
	else if (game->mapdata.spawn_cardinaldir == 'W')
	{
		// game->gamedata.plane_x = 0;
		// game->gamedata.plane_y = 0.66;
		// game->gamedata.player_radians = degrees_to_radians(270);
		// game->gamedata.player_radians = 270;
	}
}

/******************************************************************************/
/* notes                                                                      */
/******************************************************************************/

/*
- direction vector (= vector)
	"dir"
	Simply the direction to which the player looks.
	It is a line.

- player position (= vector)
	"pos"
	Simply a single point in the map.
	It is a point in front of the "camera plane".

- camera plane (= vector)
	"plane"
	Not really a plane, but a line.
	Is always perpendicular to the "direction vector".
	It is the horizontal line you would reach if you look straight ahead.
	It represents the computer screen. The 2D window of your game (e.g. 480x360)
	By definition (?) you always touch exactly the center of the camera plane.

- ray:
	A line that starts at the player position and goes through the "camera plane".

- ray direction (= vector):
	"rayDir"
	The x and y components are used by the DDA algorithm.
	"direction vector" + part of the "camera plane"
	Here, part of the "camera plane" is expressed in terms of proportion of the
	camera plane length, and is the distance between A and B, where..
	A: Where the direction vector crosses the camera plane (i.e. its center)
	B: Where the ray vector crosses the camera plane
	
	Example:
	                    part of camera plane
	                    (about 1/3 of right half of camera plane)
	                              |
	                              |    intersection around 1/3 of camera plane
	                            | |   /
	                            | V  /
	camera plane -> ------------|---/-------- <- ray vector intersects direction vector
	                            |  /
	        direction vector -> | / <- ray vector
	                            |/
	                            P <- player position vector

	e.g. The ray of interest crosses the camera plane about 1/3 of the camera
	plane's vector, assuming you would start at the camera plane's center.
	The ray direction would then be computed as follows:
	ray of interest = ("direction vector" + (1/3 * "camera plane vector"))

- field of vision (fov)
	Refers to the observable world. It is often expressed in degrees.
	The higher the fov, the more of the world is visible.

	Some insights regardins fov:
	- If the direction vector and the camera plane (measured from its center) have
	the same length, then the fov is always 90 degrees.

	- If the direction vector is much longer than the camera plane (measured from
	its center), then the fov is much narrower than 90 degrees.

	- If the direction vector is much shorter than the camera plane (measured from
	its center), then the fov is much wider than 90 degrees. The max width is
	a theoretical 180 degrees.

- rotation
	If the player rotates, then the camera plane also has to rotate.
	This makes sense, because it is the camera plane that represents your
	computer screen. You want the computer screen to depict images depending
	on where your player is looking at.

	If the player is rotated, you need to rotate the camera plane vector.
	You can rotate a vector by multiplying the vector with the "rotation matrix"

- rotation matrix
	[cos(a) -sin(a)]
	[sin(a)  cos(a)]

	Todo: Add explanations and actual usage example.
*/



// void	ray_helper(t_game *game, double cameraX)
// {
// 	game->ray->rayDirX = game->gamedata-> + vector->plane.x * cameraX;
// }

// t_ray	ray_cast(t_vector vector, char **map, double cameraX)
// {
// 	t_ray	ray;
// 	int		is_hit;

// 	is_hit = 0;
// 	ray_helper(vector, &ray, cameraX);
// }


// cameraX: The x coordinate on the camera plane.
int	draw_game(t_game *game)
{
	int		col;
	double	cameraX;

	(void)game;
	col = 0;
	while (col < RES_X)
	{
		//x-coordinate in camera space
		cameraX = 2 * col / (double)RES_X - 1;
		printf("%f\n", cameraX);
		// todo
		// game->ray = ray = ray_cast(&game->state, game->map_info.map, cameraX);
		// cast ray
		// draw wall
		col++;
	}
	return (0);
}

/******************************************************************************/
/* keys                                                                       */
/******************************************************************************/

int	check_keypress(t_game *game)
{
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_pack.mlx);
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_UP))
	{
		printf("You pressed: UP ARROW KEY\n");
		mlx_close_window(game->mlx_pack.mlx);
	}
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_DOWN))
	{
		printf("You pressed: DOWN ARROW KEY\n");
		mlx_close_window(game->mlx_pack.mlx);
	}
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_LEFT))
	{
		printf("You pressed: LEFT ARROW KEY\n");
		mlx_close_window(game->mlx_pack.mlx);
	}
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_RIGHT))
	{
		printf("You pressed: RIGHT ARROW KEY\n");
		mlx_close_window(game->mlx_pack.mlx);
	}
	return (0);
}

/******************************************************************************/
/* draw                                                                       */
/******************************************************************************/

int	draw_bg(t_game *game)
{
	unsigned int	i;

	i = 0;
	while (i < RES_X * RES_Y)
	{
		if (i < RES_X * (RES_Y / 2)) // upper half
			mlx_put_pixel(game->mlx_pack.image, i, 0, game->mapdata.ccolor);
		else if (i >= RES_X * (RES_Y / 2)) // lower half
			mlx_put_pixel(game->mlx_pack.image, i, 0, game->mapdata.fcolor);
		i++;
	}
	return (0);
}

/******************************************************************************/
/* frames                                                                     */
/******************************************************************************/

void frame_callback(void *arg)
{
	t_game *game;
	game = (t_game *)arg;
	draw_bg(game);
	draw_game(game);
	check_keypress(game);
}

/******************************************************************************/
/* mlx                                                                        */
/******************************************************************************/

int	init_textures(t_game *game, t_mapdata *mapdata)
{
	game->gamedata.textures[0] = mlx_load_png(mapdata->NO);
	if (!game->gamedata.textures[0])
		return (error_msg_ret("Failed to load NO map texture.", 1));
	game->gamedata.textures[1] = mlx_load_png(mapdata->EA);
	if (!game->gamedata.textures[1])
		return (error_msg_ret("Failed to load EA map texture.", 1));
	game->gamedata.textures[2] = mlx_load_png(mapdata->SO);
	if (!game->gamedata.textures[2])
		return (error_msg_ret("Failed to load SO map texture.", 1));
	game->gamedata.textures[3] = mlx_load_png(mapdata->WE);
	if (!game->gamedata.textures[3])
		return (error_msg_ret("Failed to load WE map texture.", 1));
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx_pack.mlx = mlx_init(RES_X, RES_Y, "cub3D", true);
	if (!game->mlx_pack.mlx)
		return (error_msg_ret("MLX initialization failed.", 1));
	game->mlx_pack.image = mlx_new_image(game->mlx_pack.mlx, RES_X, RES_Y);
	if (!(game->mlx_pack.image))
		return (error_msg_ret("MLX new image creation failed.", 1));
	mlx_set_cursor_mode(game->mlx_pack.mlx, MLX_MOUSE_HIDDEN);
	if (mlx_image_to_window(game->mlx_pack.mlx, game->mlx_pack.image, 0, 0) < 0)
		return (error_msg_ret("MLX image to window failed.", 1));
	return (0);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

int	init_game_config(t_game *game)
{
	(void)game;
	return (0);
}

int start_game(t_game *game)
{
	mlx_loop_hook(game->mlx_pack.mlx, frame_callback, game);
	mlx_loop(game->mlx_pack.mlx);
	return (0);
}

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
		return (error_msg_ret("Incorrect number of arguments.", 1));
	game.map_filename = argv[1];
	if (map_parse(&game, &game.mapdata))
		return (1);
	if (init_textures(&game, &game.mapdata))
		return (1);
	init_mlx(&game);
	init_game_config(&game);
	start_game(&game);
	map_free(game.mapdata.map, &game);
	return (0);
}
