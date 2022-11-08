#include "../headers/parsing.h"

/*check if surrounded by walls*/
int	flood_fill_check(int x, int y, t_mlx *mlx)
{
	if (x < 0 || x >= (int)ft_strlen(mlx->cpy_map[y]) || y < 0 || y >= mlx->nr_of_lines)
	{
		// printf("Error\n map not surrounded by walls");
		// returnft(mlx);
		return (0);
	}

	if (mlx->cpy_map[y][x] == '1')
		return (0);
	if (mlx->cpy_map[y][x] == 'x')
		return (0);
	if (x == 0 || y == 0 || y == mlx->nr_of_lines - 1 ||
	x == (int)ft_strlen(mlx->cpy_map[y]) - 1)
	{
		// data->map.valid_map = 1;
		printf("Error\n map not surrounded by walls");
		returnft(mlx);
		return (1);
	}
	mlx->cpy_map[y][x] = 'x';
	// return (0);
	// if (x - 1 >= 0 && x + 1 < mlx->longest_width && y - 1 >= 0 && y + 1 < mlx->nr_of_lines)
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

/*check if map is rectangular*/
void	checkmap(t_mlx *mlx)
{
	mlx->cpy_map = ft_calloc(1, sizeof(char *) * (mlx->nr_of_lines + 1));
	if (!mlx->cpy_map)
		return (returnft(mlx));
	copy_map(mlx);
	if (flood_fill_check(mlx->s_posX, mlx->s_posY, mlx) == 1)
		return (returnft(mlx));
	free_map(mlx->cpy_map, mlx);
}
