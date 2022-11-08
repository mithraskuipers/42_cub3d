/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:53:55 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/08 18:11:11 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


/*
Hoi Dagmar, voel je vrij om zelf overal je eigen Codam header toe te voegen.
Norminette decorator kleurde iets teveel code rood dus ik heb tijdelijk hier 
en daar mijn Codam header geplaatst. 
*/

#include "headers/parsing.h"

// TODO
void	returnft(t_mlx *mlx)
{
	mlx->error = 1;
	return ;
}

// free_map()
// Frees  the char **map stored in the mlx struct.
void	free_map(char **map, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->n_lines)
	{
		free (map[i]);
		i++;
	}
	free(map);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.error = 0;
	// mlx.taken = 0;
	if (argc == 2)
	{
		mlx.map_file = argv[1];
		map_parse(&mlx);
		if (mlx.error == 1)
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
