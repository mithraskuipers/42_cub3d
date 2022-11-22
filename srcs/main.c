/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 10:34:24 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/18 08:57:44 by mikuiper      ########   odam.nl         */
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

void	init_player_angle(t_game *game, t_mapdata *mapdata)
{
	if (game->player_orientation == 'N')
	{
		mapdata->player_direction = 0;
		// mapdata->player_direction = degrees_to_radians(0);
	}
	else if (game->player_orientation == 'E')
	{
		mapdata->player_direction = 90;
		// mapdata->player_direction = degrees_to_radians(90);
	}
	else if (game->player_orientation == 'S')
	{
		mapdata->player_direction = 180;
		// mapdata->player_direction = degrees_to_radians(180);
	}
	else if (game->player_orientation == 'W')
	{
		mapdata->player_direction = 270;
		// mapdata->player_direction = degrees_to_radians(270);
	}
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
		return (error_msg_ret("Incorrect number of arguments.", 1));
	game.map_filename = argv[1];
	if ((map_parse(&game, &game.mapdata)) || (init_textures(&game, &game.mapdata)))
		return (1);
	init_player_angle(&game, &game.mapdata);
	debug_print_2darray(game.mapdata.map);
	//map_free(game.mapdata.map, &game);
	game.mlx_own.mlx = mlx_init(RES_X, RES_Y, "cub3D", true);
	if (!game.mlx_own.mlx)
		return (1);
	game.mlx_own.mlx_image = mlx_new_image(game.mlx_own.mlx, RES_X, RES_Y);
	if (!game.mlx_own.mlx_image || (mlx_image_to_window(game.mlx_own.mlx, game.mlx_own.mlx_image, 0, 0) < 0))
		return (1);
	mlx_close_hook(game.mlx_own.mlx, complete_exit, game);
	mlx_loop_hook(game.mlx_own.mlx, frame_callback, game);
	mlx_loop(game.mlx_own.mlx);
	return (0);
}
