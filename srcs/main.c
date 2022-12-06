#include "./../includes/cub3d.h"

/******************************************************************************/
/* keys                                                                       */
/******************************************************************************/

int	check_keypress(t_game *game)
{
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx.mlx);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_UP))
	{
		printf("You pressed: UP ARROW KEY\n");
		mlx_close_window(game->mlx.mlx);
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_DOWN))
	{
		printf("You pressed: DOWN ARROW KEY\n");
		mlx_close_window(game->mlx.mlx);
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_LEFT))
	{
		printf("You pressed: LEFT ARROW KEY\n");
		mlx_close_window(game->mlx.mlx);
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_RIGHT))
	{
		printf("You pressed: RIGHT ARROW KEY\n");
		mlx_close_window(game->mlx.mlx);
	}
	return (0);
}

/******************************************************************************/
/* textures                                                                   */
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

/******************************************************************************/
/* init                                                                       */
/******************************************************************************/

int	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init(RES_X, RES_Y, "cub3D", true);
	if (!game->mlx.mlx)
		return (error_msg_ret("MLX initialization failed.", 1));
	game->mlx.img = mlx_new_image(game->mlx.mlx, RES_X, RES_Y);
	if (!(game->mlx.img))
		return (error_msg_ret("MLX new image creation failed.", 1));
	mlx_set_cursor_mode(game->mlx.mlx, MLX_MOUSE_HIDDEN);
	if (mlx_image_to_window(game->mlx.mlx, game->mlx.img, 0, 0) < 0)
		return (error_msg_ret("MLX image to window failed.", 1));
	return (0);
}

/*
Init at specific values. Will be adjusted by cardinal direction spawn char.
The ratio between the length of the direction and the camera plane determinates
the FOV, here the direction vector is a bit longer than the camera plane, so the
FOV will be smaller than 90° (more precisely, the FOV is 2 * atan(0.66/1.0)=66°,
which is perfect for a first person shooter game).
dir_x and dir_y are setup in accordance with lodev
*/

int	init_raycaster(t_game *game)
{
	game->ray.pos_x = game->playerPos.x + 0.5;
	game->ray.pos_y = game->playerPos.y + 0.5;

	// initialize ray directions
	game->ray.dir_x = -1;
	game->ray.dir_y = 0;
	game->ray.plane_x = 0;
	game->ray.plane_y = 0.66;
	game->ray.step_size = 0.1;
	game->ray.rot_speed = M_PI / 60;
	game->ray.forward = 0;
	game->ray.backward = 0;
	game->ray.left = 0;
	game->ray.right = 0;
	game->ray.rot_left = 0;
	game->ray.rot_right = 0;
	return (0);
}

/******************************************************************************/
/* debug                                                                      */
/******************************************************************************/

void	debugInitRaycaster(t_game *game)
{
	printf("game->ray.pos_x: %f\n", game->ray.pos_x = game->playerPos.x + 0.5);
	printf("game->ray.pos_y: %f\n", game->ray.pos_y = game->playerPos.y + 0.5);
	printf("game->ray.dir_x: %f\n", game->ray.dir_x);
	printf("game->ray.dir_y: %f\n", game->ray.dir_y);
	printf("game->ray.plane_x: %f\n", game->ray.plane_x);
	printf("game->ray.plane_y: %f\n", game->ray.plane_y);
	printf("game->ray.step_size: %f\n", game->ray.step_size);
	printf("game->ray.rot_speed: %f\n", game->ray.rot_speed);
	printf("game->ray.forward: %d\n", game->ray.forward);
	printf("game->ray.back: %d\n", game->ray.backward);
	printf("game->ray.left: %d\n", game->ray.left);
	printf("game->ray.right: %d\n", game->ray.right);
	printf("game->ray.rot_left: %d\n", game->ray.rot_left);
	printf("game->ray.rot_right: %d\n", game->ray.rot_right);
	printf("game->ray.camera_x: %f\n", game->ray.camera_x);
	printf("game->ray.ray_dir_x: %f\n", game->ray.ray_dir_x);
	printf("game->ray.ray_dir_y: %f\n", game->ray.ray_dir_y);
	printf("game->ray.map_x: %d\n", game->ray.map_x);
	printf("game->ray.map_y: %d\n", game->ray.map_y);
	printf("game->ray.delta_dist_x: %f\n", game->ray.delta_dist_x);
	printf("game->ray.delta_dist_y: %f\n", game->ray.delta_dist_y);
	printf("game->ray.side_dist_x: %f\n", game->ray.side_dist_x);
	printf("game->ray.side_dist_y: %f\n", game->ray.side_dist_y);
	printf("\n");
}

void	debugSpawnRadians(t_game *game)
{
	printf("\nspawnRadians: %f\n\n", game->spawnRadians);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

int	spawnDegrees(t_game *game)
{
	int	degrees;

	degrees = 0;
	if (game->mapdata.spawn_cardinaldir == 'N')
		degrees = 0;
	else if (game->mapdata.spawn_cardinaldir == 'E')
		degrees = 90;
	else if (game->mapdata.spawn_cardinaldir == 'S')
		degrees = 180;
	else if (game->mapdata.spawn_cardinaldir == 'W')
		degrees = 270;
	return (degrees);
}

void	updateRayData(t_game *game)
{
	double	dir_x_tmp;
	double	plane_x_tmp;

	dir_x_tmp = game->ray.dir_x;
	game->ray.dir_x = game->ray.dir_x * cos(game->spawnRadians) - game->ray.dir_y * sin(game->spawnRadians);
	game->ray.dir_y = dir_x_tmp * sin(game->spawnRadians) + game->ray.dir_y * cos(game->spawnRadians);
	plane_x_tmp = game->ray.plane_x;
	game->ray.plane_x = game->ray.plane_x * cos(game->spawnRadians) - game->ray.plane_y * sin(game->spawnRadians);
	game->ray.plane_y = plane_x_tmp * sin(game->spawnRadians) + game->ray.plane_y * cos(game->spawnRadians);
}

/*
Calculate the x-coordinate in camera space
Calculate ray direction (ray_dir_x, ray_dir_y)
Save the player coordinates
*/

void	setRayPos(t_game *game, int x)
{
	game->ray.camera_x = 2 * x / (double)RES_X - 1;
	game->ray.ray_dir_x = game->ray.dir_x + game->ray.plane_x * game->ray.camera_x;
	game->ray.ray_dir_y = game->ray.dir_y + game->ray.plane_y * game->ray.camera_x;
	game->ray.map_x = (int)game->ray.pos_x;
	game->ray.map_y = (int)game->ray.pos_y;
}

/*
Compute the distance a ray has from one xside or yside to the next xside or yside.
Calculate step and initial sideDist
*/

void	setRayLen(t_ray *ray)
{
	ray->delta_dist_y = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_x = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_y;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_y;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_x;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_x;
	}
}

int	renderFrame(t_game *game)
{
	int	col;

	col = 0;
	while (col < RES_X)
	{
		sleep(1);
		setRayPos(game, col);
		game->ray.hit = 0;
		setRayLen(&(game->ray));
		debugInitRaycaster(game);	
		printf("col: %d\n", col);
		// prepare for Digital Differential Analysis (see lodev)
		col++;
	}
	return (0);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void frame_callback(void *arg)
{
	t_game *game;
	game = (t_game *)arg;
	renderBackground(game);
	check_keypress(game);
	init_raycaster(game);
	debugInitRaycaster(game);
	game->spawnRadians = degreesToRadians(spawnDegrees(game));
	debugSpawnRadians(game);
	updateRayData(game);
	debugInitRaycaster(game);
	renderFrame(game);
	printf("\n\n");
}

int start_game(t_game *game)
{
	mlx_loop_hook(game->mlx.mlx, frame_callback, game);
	mlx_loop(game->mlx.mlx);

	//frame_callback(game);
	return (0);
}

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg_ret("Incorrect number of arguments.", 1));
	game.map_filename = argv[1];
	if (map_parse(&game, &game.mapdata))
		return (1);
	if (init_textures(&game, &game.mapdata))
		return (1);
	init_mlx(&game);
	start_game(&game);
	//map_free(game.mapdata.map, &game);
	return (0);
}
