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
/*                                                                            */
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

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void frame_callback(void *arg)
{
	t_game *game;
	game = (t_game *)arg;
	draw_bg(game);
	check_keypress(game);
}

int start_game(t_game *game)
{
	mlx_loop_hook(game->mlx.mlx, frame_callback, game);
	mlx_loop(game->mlx.mlx);
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
	start_game(&game);
	//map_free(game.mapdata.map, &game);
	return (0);
}
