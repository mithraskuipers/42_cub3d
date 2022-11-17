/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 10:34:24 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/17 14:33:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/parsing.h"




int	init_textures(t_mlx *mlx, t_parse *parse)
{
	printf("%s\n", parse->NO);
	printf("%s\n", parse->EA);
	printf("%s\n", parse->SO);
	printf("%s\n", parse->WE);
	printf("%d\n", parse->ccolor);
	mlx->gamedata.textures[0] = mlx_load_png(parse->NO);
	if (!mlx->gamedata.textures[0])
		error_msg_ret("Failed to load NO map texture.", 1);
	mlx->gamedata.textures[1] = mlx_load_png(parse->EA);
	if (!mlx->gamedata.textures[1])
		error_msg_ret("Failed to load EA map texture.", 1);
	mlx->gamedata.textures[2] = mlx_load_png(parse->SO);
	if (!mlx->gamedata.textures[2])
		error_msg_ret("Failed to load SO map texture.", 1);
	mlx->gamedata.textures[3] = mlx_load_png(parse->WE);
	if (!mlx->gamedata.textures[3])
		error_msg_ret("Failed to load WE map texture.", 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_parse	parse;

	if (argc != 2)
		return (error_msg_ret("Incorrect number of arguments.", 1));
	mlx.map_filename = argv[1];
	if ((map_parse(&mlx, &parse)) || (init_textures(&mlx, &parse)))
		return (1);

	if (mlx.player_orientation == 'N') // 0 degrees
		parse.player_direction = 2 * PI;
	else if (mlx.player_orientation == 'E') // 90 degrees
		parse.player_direction = PI * 2;
	else if (mlx.player_orientation == 'S') // 180 degrees
		parse.player_direction = 1.5 * PI;
	else if (mlx.player_orientation == 'W') // 270 degrees
		parse.player_direction = 2 * PI;
	// printf("%u", mlx.gamedata.ceiling_rgb);
	printf("%f\n", parse.player_direction);
	map_free(parse.map, &mlx);
	return (0);
}
