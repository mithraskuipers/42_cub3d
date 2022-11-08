/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 14:53:55 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/08 16:12:17 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"


/*


*/
void	returnft(t_mlx *mlx)
{
	mlx->error = 1;
	return ;
}

/*


*/
void	free_map(char **map, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < mlx->nr_of_lines)
	{
		free (map[i]);
		i++;
	}
	free(map);
}


/*
- Checks number of arguments, else trigger error and return 1.
- Saved map filename in mlx.map_file char *
- Parse the map using map_parse().
- If reaches end of main(), then free the map.
- map_parse() is now the most important function.

*/
int		main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.error = 0;
	// mlx.taken = 0;
	if (argc == 2)
	{
		mlx.map_file = argv[1];
		if (map_parse(&mlx) == 1)
		{
			system ("leaks cub3D");
			return (1);
		}
	}
	else
	{
		printf("Error\nIncorrect amount of arguments");
		return (1);
	}
	free_map(mlx.map, &mlx);
	system ("leaks cub3D");
    return (0);
}