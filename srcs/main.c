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

#include "./../includes/parsing.h"


// I deviate from the subject in the order of the cardinal directions (NESW).
// I think the subject's order (NSEW) is only a source of confusion.

int	init_textures(t_game *mlx, t_parse *parse)
{
	mlx->gamedata.textures[0] = mlx_load_png(parse->NO);
	if (!mlx->gamedata.textures[0])
		return (error_msg_ret("Failed to load NO map texture.", 1));
	mlx->gamedata.textures[1] = mlx_load_png(parse->EA);
	if (!mlx->gamedata.textures[1])
		return (error_msg_ret("Failed to load EA map texture.", 1));
	mlx->gamedata.textures[2] = mlx_load_png(parse->SO);
	if (!mlx->gamedata.textures[2])
		return (error_msg_ret("Failed to load SO map texture.", 1));
	mlx->gamedata.textures[3] = mlx_load_png(parse->WE);
	if (!mlx->gamedata.textures[3])
		return (error_msg_ret("Failed to load WE map texture.", 1));
	return (0);
}

void	init_player_angle(t_game *mlx, t_parse *parse)
{
	if (mlx->player_orientation == 'N')
		parse->player_direction = degrees_to_radians(0);
	else if (mlx->player_orientation == 'E')
		parse->player_direction = degrees_to_radians(90);
	else if (mlx->player_orientation == 'S')
		parse->player_direction = degrees_to_radians(180);
	else if (mlx->player_orientation == 'W')
		parse->player_direction = degrees_to_radians(270);
}

int	main(int argc, char **argv)
{
	t_game	mlx;
	t_parse	parse;

	if (argc != 2)
		return (error_msg_ret("Incorrect number of arguments.", 1));
	mlx.map_filename = argv[1];
	if ((map_parse(&mlx, &parse)) || (init_textures(&mlx, &parse)))
		return (1);
	init_player_angle(&mlx, &parse);


	map_free(parse.map, &mlx);
	return (0);
}
