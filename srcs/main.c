/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 10:34:24 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/15 15:30:27 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/parsing.h"



int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_parse	parse;

	if (argc == 2)
	{
		mlx.map_filename = argv[1];
		if (map_parse(&mlx, &parse) == 1)
		{
			system ("leaks cub3D");
			return (1);
		}
		//debug_print_map(&mlx);
		// debug_highlight_player(&mlx);
	}
	else
	{
		return (error_msg_ret("Incorrect number of arguments.", 1));
	}
	map_free(parse.map, &mlx);
	system ("leaks cub3D");
	return (0);
}
