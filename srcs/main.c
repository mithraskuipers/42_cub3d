#include "./../includes/cub3d.h"

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

/******************************************************************************/
/* frames                                                                     */
/******************************************************************************/

void frame_callback(void *arg)
{
	t_game *game;
	game = (t_game *)arg;
	// draw_bg(game);
	check_keypress(game);
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
/* mlx                                                                        */
/******************************************************************************/

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
/* raycaster                                                                  */
/******************************************************************************/

int	spawn_dir(t_game *game)
{
	double	radians;

	radians = 0;
	if (game->mapdata.spawn_cardinaldir == 'N')
		radians = 0;
	else if (game->mapdata.spawn_cardinaldir == 'E')
		radians = M_PI / 2;
	else if (game->mapdata.spawn_cardinaldir == 'S')
		radians = M_PI;
	else if (game->mapdata.spawn_cardinaldir == 'W')
		radians = 1.5 * M_PI;
	game->gamedata.radians = radians;
	return (0);
}

int	rotate(t_game *game, double radians)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->ray.dir.x;
	game->ray.dir.x = game->ray.dir.x * cos(radians) - game->ray.dir.y * sin(radians);
	game->ray.dir.y = old_dir_x * sin(radians) + game->ray.dir.y * cos(radians);
	old_plane_x = game->ray.plane.x;
	game->ray.plane.x = game->ray.plane.x * cos(radians) - game->ray.plane.y * sin(radians);
	game->ray.plane.y = old_plane_x * sin(radians) + game->ray.plane.y * cos(radians);
	return (0);
}

/*
	- Calculate x-coordinate in camera space
	- Calculate ray position and direction
	- Save which box of the map we're in
*/
void	set_ray_pos(t_game *game, int col)
{
	game->ray.cameraX = (float)(2 * col) / (float)(RES_X - 1);
	game->ray.dir.x = game->ray.dir.x + game->ray.plane.x * game->ray.cameraX;
	game->ray.dir.y = game->ray.dir.y + game->ray.plane.y * game->ray.cameraX;
	game->ray.map_x = (int)game->ray.playerPos.x;
	game->ray.map_y = (int)game->ray.playerPos.y;
}


/*
	- Calculate length of ray from one x or y-side to next x or y-side
	- Calculate step and initial sideDist
*/
void	get_ratios(t_ray *ray)
{
	ray->deltaDist.y = fabs(1 / ray->dir.x);
	ray->deltaDist.x = fabs(1 / ray->dir.y);
	ray->hit = 0;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (ray->playerPos.x - ray->map_x) * ray->deltaDist.y;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (ray->map_x + 1.0 - ray->playerPos.x) * ray->deltaDist.y;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (ray->playerPos.y - ray->map_y) * ray->deltaDist.x;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (ray->map_y + 1.0 - ray->playerPos.y) * ray->deltaDist.x;
	}
}

void	dbg_print_ray_data(t_game *game, int col)
{
	printf("\n");
	printf("raycol# %d:\tray.cameraX: \t\t%f\n", col, game->ray.cameraX);
	printf("raycol# %d:\tray.dir: \t\t%f\t%f\n", col, game->ray.dir.x, game->ray.dir.y);
	printf("raycol# %d:\tray.plane: \t\t%f\t%f\n", col, game->ray.plane.x, game->ray.plane.y);
	printf("raycol# %d:\tray.sideDist: \t\t%f\t%f\n", col, game->ray.sideDist.x, game->ray.sideDist.y);
	printf("raycol# %d:\tray.map: \t\t%d\t\t%d\n", col, game->ray.map_x, game->ray.map_y);
}

/*
	- Jump to next map square in x-direction OR in y-direction
	- Check if ray has hit a wall
*/

void	perform_dda(t_game *game)
{
	while (game->ray.hit == 0)
	{
		// printf("running dda\n");
		if (game->ray.sideDist.x < game->ray.sideDist.y)
		{
			game->ray.sideDist.x += game->ray.deltaDist.y;
			// game->ray.map_x += game->ray.step.x;
			game->ray.map_x = (int)game->ray.map_x + (int)game->ray.step.x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sideDist.y += game->ray.deltaDist.x;
			// game->ray.map_y += game->ray.step.y;
			game->ray.map_y = (int)game->ray.map_y + (int)game->ray.step.y;
			game->ray.side = 1;
		}
		// game->ray.hit = 1;
		printf("ray.map_x: %c\n", game->ray.map_x);
		printf("ray.map_y: %c\n", game->ray.map_y);
		// if (game->mapdata.map[game->ray.map_x][game->ray.map_y] == '1')
		// 	game->ray.hit = 1;
	}
}

int	draw_img(t_game *game)
{
	int	col;

	draw_bg(game);
	col = 0;
	while (col < RES_X)
	{
		set_ray_pos(game, col);
		dbg_print_ray_data(game, col);
		get_ratios(&(game->ray));
		perform_dda(game);
		col++;
	}
	return (0);
}

int	init_raycaster(t_game *game)
{
	game->ray.playerPos.x = 1; // game->posX + 1;
	game->ray.playerPos.y = 1; // game->posY + 1;
	game->ray.dir.x = -1;
	game->ray.dir.y = 0;
	game->ray.plane.x = 0;
	game->ray.plane.y = .66;
	game->ray.move.l = 0;
	game->ray.move.r = 0;
	game->ray.rot.l = 0;
	game->ray.rot.r = 0;
	return (0);
}

/******************************************************************************/
/* start game                                                                 */
/******************************************************************************/

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
	init_raycaster(&game);
	spawn_dir(&game);
	rotate(&game, game.gamedata.radians);
	draw_img(&game);


	//start_game(&game);
	//map_free(game.mapdata.map, &game);
	return (0);
}
