/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 10:34:24 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/12 21:16:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/parsing.h"

// free_map()
// Frees  the char **map stored in the mlx struct.
void	free_map(char **map, t_mlx *mlx)
{
	mlx->i = 0;
	while (mlx->i < mlx->n_lines)
	{
		free (map[mlx->i]);
		mlx->i++;
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
	}
	else
	{
		return (error_msg_ret("Incorrect number of arguments.", 1));
	}
	free_map(mlx.map, &mlx);
	// system ("leaks cub3D");
	return (0);
}
