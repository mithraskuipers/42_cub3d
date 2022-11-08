#include "headers/parsing.h"

void	returnft(t_mlx *mlx)
{
	mlx->error = 1;
	return ;
}

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

int main(int argc, char **argv)
{
    t_mlx	mlx;

	mlx.error = 0;
	// mlx.taken = 0;
	if (argc == 2)
	{
		mlx.map_file = argv[1];
		mapparsing(&mlx);
		if (mlx.error == 1)
		{
			// system ("leaks cub3D");
			return (1);
		}
	}
	else
	{
		printf("Error\n incorrect amount of arguments");
		return (1);
	}
	free_map(mlx.map, &mlx);
	// system ("leaks cub3D");
    return (0);
}