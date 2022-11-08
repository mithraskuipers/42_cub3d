#include "../headers/parsing.h"

/*check if surrounded by walls*/
int	flood_fill_check(int x, int y, t_mlx *mlx)
{
	if (x < 0 || x >= (int)ft_strlen(mlx->cpy_map[y]) || y < 0 || y >= mlx->n_lines)
	{
		// printf("Error\n map not surrounded by walls");
		// returnft(mlx);
		return (0);
	}

	if (mlx->cpy_map[y][x] == '1')
		return (0);
	if (mlx->cpy_map[y][x] == 'x')
		return (0);
	if (x == 0 || y == 0 || y == mlx->n_lines - 1 ||
	x == (int)ft_strlen(mlx->cpy_map[y]) - 1)
	{
		// data->map.valid_map = 1;
		printf("Error\n map not surrounded by walls");
		returnft(mlx);
		return (1);
	}
	mlx->cpy_map[y][x] = 'x';
	// return (0);
	// if (x - 1 >= 0 && x + 1 < mlx->longest_width && y - 1 >= 0 && y + 1 < mlx->n_lines)
	// {
	if (flood_fill_check(x - 1, y, mlx) == 1)
		return (1);
	if (flood_fill_check(x, y - 1, mlx) == 1)
		return (1);
	if (flood_fill_check(x + 1, y, mlx) == 1)
		return (1);
	if (flood_fill_check(x, y + 1, mlx) == 1)
		return (1);
	// }
	return (0);
}

void	copy_map(t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < mlx->n_lines)
	{
		x = 0;
		mlx->len = (int)ft_strlen(mlx->map[y]);
		mlx->cpy_map[y] = ft_calloc(1, mlx->len * sizeof(char) + 1);
		while (x < mlx->len)
		{
			mlx->cpy_map[y][x] = mlx->map[y][x];
			x++;
		}
		// printf("%s\n", mlx->cpy_map[y]);
		y++;
	}
}

/*check if map is rectangular*/
void	checkmap(t_mlx *mlx)
{
	mlx->cpy_map = ft_calloc(1, sizeof(char *) * (mlx->n_lines + 1));
	if (!mlx->cpy_map)
		return (returnft(mlx));
	copy_map(mlx);
	if (flood_fill_check(mlx->s_posX, mlx->s_posY, mlx) == 1)
	{
		free_map(mlx->cpy_map, mlx);
		return (returnft(mlx));
	}
	free_map(mlx->cpy_map, mlx);
}
