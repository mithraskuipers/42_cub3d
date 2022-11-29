
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

#include "./../includes/cub3d.h"

/*
arc tangent = inverse tangent = atan
tangent to degrees? arc tangent
*/

/*

				N

				1
				|
				|
				|
W	-1	--------0-------	1 E
				|
				|
				|
				-1
				S
*/

// void	ray_helper(t_game *game, double cameraX)
// {
// 	game->ray->rayDirX = game->gamedata. + vector->plane.x * cameraX;
// }

// t_ray	ray_cast(t_vector vector, char **map, double cameraX)
// {
// 	t_ray	ray;
// 	int		is_hit;

// 	is_hit = 0;
// 	ray_helper(vector, &ray, cameraX);
// }

/******************************************************************************/
/* Set direction vector on basis of spawn cardinal direction                  */
/******************************************************************************/

/*
Set initial direction vector
*/
void	set_dir(t_game *game)
{
	if (game->mapdata.spawn_cardinaldir == 'N')
	{
		game->gamedata.dir.x= 0;
		game->gamedata.dir.y = 1;
	}
	else if (game->mapdata.spawn_cardinaldir == 'E')
	{
		game->gamedata.dir.x = 1;
		game->gamedata.dir.y = 0;
	}
	else if (game->mapdata.spawn_cardinaldir == 'S')
	{
		game->gamedata.dir.x = 0;
		game->gamedata.dir.y = -1;
	}
	else if (game->mapdata.spawn_cardinaldir == 'W')
	{
		game->gamedata.dir.x = -1;
		game->gamedata.dir.y = 0;
	}
}

/*
Set camera plane on the basis of direction vector
*/
void	set_plane(t_game *game)
{
	if (game->gamedata.dir.x == 0)
	{
		if (game->gamedata.dir.y == 0)
		{
			game->gamedata.plane.x = 1;
		}
		else if (game->gamedata.dir.y == 1)
		{
			game->gamedata.plane.x = -1;
		}
		game->gamedata.plane.y = 0;
	}
	else if (game->gamedata.dir.x == 1)
	{
		if (game->gamedata.dir.y == 0)
		{
			game->gamedata.plane.y = 1;
		}
		else if (game->gamedata.dir.y == 1)
		{
			game->gamedata.plane.y = -1;
		}
		game->gamedata.plane.x = 0;
	}
	return ;
}

void	set_ray(t_game *game, t_ray *ray, double cameraX)
{
	ray->rayDirX = game->gamedata.dir.x + game->gamedata.plane.x * cameraX;
	ray->rayDirY = game->gamedata.dir.y + game->gamedata.plane.y * cameraX;
	ray->mapPos.x = (int)game->gamedata.pos.x;
	ray->mapPos.y = (int)game->gamedata.pos.y;
	// length of ray from one x or y-side to next x or y-side
	if (ray->rayDirX == 0)
		ray->deltaDist.x = 1e30;
	else
		ray->deltaDist.x = ft_abs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDist.y = 1e30;
	else
		ray->deltaDist.y = ft_abs(1 / ray->rayDirY);

	// calculate step and initial sideDist
	if (ray->rayDirX < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (game->gamedata.pos.x - (double)ray->mapPos.x) * ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = ((double)ray->mapPos.x + 1.0 - game->gamedata.pos.x) * ray->deltaDist.x;
	}
	if (ray->rayDirY < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (game->gamedata.pos.y - (double)ray->mapPos.y) * ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = ((double)ray->mapPos.y + 1.0 - game->gamedata.pos.y) * ray->deltaDist.y;
	}
	// perform DDA
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->mapPos.x += ray->step.x;
			ray->side = 0; // ???
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->mapPos.y += ray->step.y;
			ray->side = 1; // ???
		}
		// Check if ray has hit a wall
		// if (game->mapdata.map[ray->mapPos.x][ray->mapPos.y] > 0)
		// {
		// 	hit = 1;
		// }
		hit = 1;
	}
	return ;
}

# define WALL 1

t_ray	raycast(t_game *game, char **map, double cameraX)
{
	t_ray	ray;
	// int		hit;

	// hit = 0;
	set_ray(game, &ray, cameraX);
	// while (hit == 0)
	// {
	// 	if (ray.sideDist.x < ray.sideDist.y)
	// 		update_ray(&ray, X);
	// 	else if (ray.sideDist.x > ray.sideDist.y)
	// 		update_ray(&ray, Y);
	// 	else
	// 	{
	// 		update_ray(&ray, X);
	// 		update_ray(&ray, Y);
	// 	}
	// 	if (map[ray.map_y][ray.map_x] == WALL)
	// 		hit = 1;
	// }
	// set_perp_wall_dist(&ray, &state->pos);
	// return (ray);
	(void)game;
	(void)map;
	(void)cameraX;
	return (ray);
}

// cameraX: The x coordinate on the camera plane.
int	draw_game(t_game *game)
{
	int		col;
	double	cameraX;
	t_ray	ray;

	(void)game;
	col = 0;
	while (col < RES_X)
	{
		//x-coordinate in camera space
		cameraX = 2 * col / (double)RES_X - 1;
		ray = raycast(game, game->mapdata.map, cameraX);
		// if (ray.perp_wall_dist < STEP + 0.01)
		// 	return (FAIL);
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
