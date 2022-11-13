/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 10:34:24 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/13 15:49:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/parsing.h"

// map_free()
// Frees  the char **map stored in the mlx struct.
void	map_free(char **map, t_mlx *mlx)
{
	mlx->map_row = 0;
	while (mlx->map_row < mlx->n_lines)
	{
		free (map[mlx->map_row]);
		mlx->map_row++;
	}
	free(map);
}

// bzero zet autom error en taken ook op 0.
//init_mlx(&mlx);

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc == 2)
	{
		mlx.map_filename = argv[1];
		if (map_parse(&mlx) == 1)
		{
			// system ("leaks cub3D");
			return (1);
		}
		//debug_print_map(&mlx);
		debug_highlight_player(&mlx);
	}
	else
	{
		return (error_msg_ret("Incorrect number of arguments.", 1));
	}
	map_free(mlx.map, &mlx);
	// system ("leaks cub3D");
	return (0);
}
