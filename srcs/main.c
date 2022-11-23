/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 10:34:24 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/23 13:05:49 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"


// I deviate from the subject in the order of the cardinal directions (NESW).
// I think the subject's order (NSEW) is only a source of confusion.

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

void	init_player_angle(t_game *game)
{
	if (game->mapdata.player_cardinaldir == 'N')
	{
		// game->gamedata.player_radians = degrees_to_radians(0);
		game->gamedata.player_radians = 0;
	}
	else if (game->mapdata.player_cardinaldir == 'E')
	{
		// game->gamedata.player_radians = degrees_to_radians(90);
		game->gamedata.player_radians = 90;
	}
	else if (game->mapdata.player_cardinaldir == 'S')
	{
		// game->gamedata.player_radians = degrees_to_radians(180);
		game->gamedata.player_radians = 180;
	}
	else if (game->mapdata.player_cardinaldir == 'W')
	{
		// game->gamedata.player_radians = degrees_to_radians(270);
		game->gamedata.player_radians = 270;
	}
}

#include <math.h>

/*
arc tangent = inverse tangent = atan
tangent to degrees? arc tangent
*/

void	render_col(t_game *game, int col)
{
	float	tangens;

	tangens = atanf((col - (game->mlx_pack.mlx->width / 2)) / (game->mlx_pack.mlx->width / 2)) + game->gamedata.player_radians;
	(void)game;
	(void)col;
	(void)tangens;
	// printf("%f\n", tangens);
}





void	key_check(t_game *game)
{
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_ESCAPE))
		exit(1);
}


void	frame_callback(void *arg)
{
	t_game	*game;
	int		col;

	game = (t_game *)arg;
	col = 0;
	key_check(game);
	game->gamedata.player_radians = degrees_to_radians(game->gamedata.player_radians);
	while (col < game->mlx_pack.mlx->width) // width is determined by mlx itself, based on your RES_X and RES_Y
	{
		render_col(game, col);
		col++;
	}
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

int	init_game_config(t_game *game)
{
	game->gamedata.fov = (80 * M_PI / 180);
	game->gamedata.ray_len = 40;
	return (0);
}

int start_game(t_game *game)
{
	mlx_loop_hook(game->mlx_pack.mlx, frame_callback, game);
	mlx_loop(game->mlx_pack.mlx);
	return (0);
}

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
	init_player_angle(&game);
	init_mlx(&game);
	init_game_config(&game);
	start_game(&game);
	// debug_print_2darray(game.mapdata.map);
	map_free(game.mapdata.map, &game);
	// system ("leaks cub3D");
	return (0);
}
