#include "../headers/parsing.h"

/*check if surrounded by walls*/
void	wallchecker(t_mlx *mlx)
{
	// if (mlx->map[i][0] != '1' 
	int	i;
// 	int	a;
// 	int	last_one;

// 	a = 0;
	i = 0;
	mlx->longest_width = 0;
// 	last_one = 0;
	while (i < mlx->nr_of_lines)
	{
		mlx->len = (int)ft_strlen(mlx->map[i]);
		if (mlx->len > mlx->longest_width)
			mlx->longest_width = mlx->len;
// 		if (mlx->map[i][0] != '1' || mlx->map[i][mlx->len - 1] != '1'
// 		|| (previous_len != 0 && previous_len < mlx->len && last_one != 0 && mlx->map[i][last_one + 1] != '1')
// 		|| (last_one != 0 && previous_len > mlx->len && mlx->map[i][last_one - 1] != '1'))
// 		{
// 			printf("%s", "Error\n map not surrounded be walls");
// 			return (returnft(mlx));
// 		}
// 		a = mlx->len;
// 		while (mlx->map[i][a - 1] == '1')
// 		{
// 			last_one = a - 1;
// 			a--;
// 		}
		printf("%d len\n", mlx->len);

		i++;
	}
	printf("%d longest width\n", mlx->longest_width);
	// a = 0;
	// mlx->len =  (int)ft_strlen(mlx->map[0]);
	// while (a < mlx->len)
	// {
	// 	if (mlx->map[0][a] != '1')
	// 	{
	// 		printf("%s", "Error\n map not surrounded be walls");
	// 		return (returnft(mlx));
	// 	}
	// 	a++;
	// }
	// a = 0;
	// mlx->len =  (int)ft_strlen(mlx->map[mlx->nr_of_lines - 1]);
	// while (a < mlx->len)
	// {
	// 	if (mlx->map[mlx->nr_of_lines - 1][a] != '1')
	// 	{
	// 		printf("%s", "Error\n map not surrounded be walls");
	// 		return (returnft(mlx));
	// 	}
	// 	a++;
	// }
}


void	get_longest_width(t_mlx *mlx)
{
	int	i;

	i = 0;
	mlx->longest_width = 0;
	while (i < mlx->nr_of_lines)
	{
		mlx->len = (int)ft_strlen(mlx->map[i]);
		if (mlx->len > mlx->longest_width)
			mlx->longest_width = mlx->len;
		i++;
	}
}

// void	get_longest_height(t_mlx *mlx)
// {
// 	int	i;

// 	i = 0;
// 	mlx->longest_width = 0;
// 	while ()
// 	{
// 		mlx->len = (int)ft_strlen(mlx->map[i]);
// 		if (mlx->len > mlx->longest_width)
// 			mlx->longest_width = mlx->len;
// 		i++;
// 	}
// }

void	copy_map(t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < mlx->nr_of_lines)
	{
		x = 0;
		mlx->len = (int)ft_strlen(mlx->map[y]);
		mlx->cpy_map[y] = ft_calloc(1, mlx->len * sizeof(char) + 1);
		while (x < mlx->len)
		{
			mlx->cpy_map[y][x] = mlx->map[y][x];
			x++;
		}
		printf("%s\n", mlx->cpy_map[y]);
		y++;
	}
}

int	valid_check(int x, int y, t_mlx *mlx)
{
	// if (row < 1 || row > mlx->longest_height)
	// 	return (1);
	// if (column < 1 || column > mlx->longest_width)
	// 	return (1);
	// if (mlx->map[i][a]) != 'x' || 
	if (x < 0 && x >= mlx->longest_width && y < 0 && y >= mlx->nr_of_lines)
		return (1);
	printf("x %d\n", x);
	printf("y %d\n", y);

	if (mlx->cpy_map[y][x] == 'x')
		return (0);
	// if (mlx->cpy_map[y][x] == '1')
	// 	return (1);
	if (mlx->cpy_map[y][x] == '0' && (x == 0 || y == 0 || x == mlx->longest_width - 1 || y == mlx->nr_of_lines - 1))
		return (1);
	mlx->cpy_map[y][x] = 'x';
	return (0);
}

int	flood_fill_check(int x, int y, t_mlx *mlx)
{
	if (valid_check(x, y, mlx) == 1)
	{
		printf("Error\n map not surrounded by walls");
		returnft(mlx);
		return (1);
	}
	// if (x - 1 >= 0 && x + 1 < mlx->longest_width && y - 1 >= 0 && y + 1 < mlx->nr_of_lines)
	// {
	flood_fill_check(x - 1, y, mlx);
	flood_fill_check(x, y - 1, mlx);
	flood_fill_check(x + 1, y, mlx);
	flood_fill_check(x, y + 1, mlx);
	// }
	return (0);
}

/*check if map is rectangular*/
void	checkmap(t_mlx *mlx)
{
	// int x = 3;
	// int y = 3;

	mlx->cpy_map = ft_calloc(1, sizeof(char *) * (mlx->nr_of_lines + 1));
	if (!mlx->cpy_map)
		return (returnft(mlx));
	get_longest_width(mlx);
	copy_map(mlx);
	flood_fill_check(mlx->s_posX, mlx->s_posY, mlx);
	// wallchecker(mlx, x, y);
	// free (mlx->cpy_map);
	free_map(mlx->cpy_map, mlx);
	// north_southwallchecker(mlx);
}
