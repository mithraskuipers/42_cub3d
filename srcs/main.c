/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 10:34:24 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/16 09:19:12 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/parsing.h"

typedef struct s_gamedata
{
	mlx_texture_t	*textures[4];
}				t_gamedata;

int	init_textures(t_parse *parse)
{
	printf("%s\n", parse->NO);
	printf("%s\n", parse->EA);
	printf("%s\n", parse->SO);
	printf("%s\n", parse->WE);
	t_gamedata	*gamedata;
	gamedata = ft_calloc(1, sizeof(t_gamedata));
	gamedata->textures[0] = mlx_load_png(parse->NO);
	gamedata->textures[1] = mlx_load_png(parse->EA);
	gamedata->textures[2] = mlx_load_png(parse->SO);
	gamedata->textures[3] = mlx_load_png(parse->WE);

	return (0);
}



int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_parse	parse;

	if (argc == 2)
	{
		mlx.map_filename = argv[1];
		if (map_parse(&mlx, &parse) == 1)
			return (1);
		// Ik zit hier even te experimenteren
		init_textures(&parse);

	}
	else
	{
		return (error_msg_ret("Incorrect number of arguments.", 1));
	}
	map_free(parse.map, &mlx);
	// system ("leaks cub3D");
	return (0);
}
