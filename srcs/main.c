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
	game->ray.const_rad = M_PI / 48;
	game->ray.forward = 0;
	game->ray.backward = 0;
	game->ray.left = 0;
	game->ray.right = 0;
	game->ray.rot_left = 0;
	game->ray.rot_right = 0;
	return (0);
}

void	print_init_raycaster(t_game *game)
{
	printf("game->ray.pos_x: %f\n", game->ray.pos_x = game->playerPos.x + 0.5);
	printf("game->ray.pos_y: %f\n", game->ray.pos_y = game->playerPos.y + 0.5);
	printf("game->ray.dir_x: %f\n", game->ray.dir_x);
	printf("game->ray.dir_y: %f\n", game->ray.dir_y);
	printf("game->ray.plane_x: %f\n", game->ray.plane_x);
	printf("game->ray.plane_y: %f\n", game->ray.plane_y);
	printf("game->ray.step_size: %f\n", game->ray.step_size);
	printf("game->ray.const_rad: %f\n", game->ray.const_rad);
	printf("game->ray.forward: %d\n", game->ray.forward);
	printf("game->ray.back: %d\n", game->ray.backward);
	printf("game->ray.left: %d\n", game->ray.left);
	printf("game->ray.right: %d\n", game->ray.right);
	printf("game->ray.rot_left: %d\n", game->ray.rot_left);
	printf("game->ray.rot_right: %d\n", game->ray.rot_right);
	printf("\n");
}

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

	printf("radians: %f\n", radians);
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->ray.dir_x;
	game->ray.dir_x = game->ray.dir_x * cos(radians) - game->ray.dir_y * sin(radians);
	game->ray.dir_y = old_dir_x * sin(radians) + game->ray.dir_y * cos(radians);
	old_plane_x = game->ray.plane_x;
	printf("\nold_plane_x: %f\n", old_plane_x);
	game->ray.plane_x = game->ray.plane_x * cos(radians) - game->ray.plane_y * sin(radians);
	game->ray.plane_y = old_plane_x * sin(radians) + game->ray.plane_y * cos(radians);
	return (0);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void frame_callback(void *arg)
{
	t_game *game;
	game = (t_game *)arg;
	draw_bg(game);
	check_keypress(game);
	init_raycaster(game);
	print_init_raycaster(game);
	spawn_dir(game);
	print_init_raycaster(game);
	printf("\n\n\n");
}

int start_game(t_game *game)
{
	// mlx_loop_hook(game->mlx.mlx, frame_callback, game);
	// mlx_loop(game->mlx.mlx);

	frame_callback(game);
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
