/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 08:47:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/09 12:57:33 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parsing.h"

/*check if surrounded by walls*/
int	flood_fill_check(int x, int y, t_mlx *mlx)
{
	if (x < 0 || x >= mlx->longest_width || y < 0 || y >= mlx->n_lines)
		return (0);
	if (mlx->cpy_map[y][x] == '1')
		return (0);
	if (mlx->cpy_map[y][x] == 'x')
		return (0);
	if ((x + 1 < mlx->longest_width && mlx->cpy_map[y][x + 1] == ' ')
		|| (x - 1 >= 0 && mlx->cpy_map[y][x - 1] == ' ') || (y + 1
		< mlx->n_lines && mlx->cpy_map[y + 1][x] == ' ') || (y - 1
		>= 0 && mlx->cpy_map[y - 1][x] == ' '))
		if (mlx->cpy_map[y][x] == '0')
			return (error_msg_ret("Map not surrounded by walls.", 1));
	if (x == 0 || y == 0 || y == mlx->n_lines - 1
		|| x == mlx->longest_width - 1)
		return (error_msg_ret("Map not surrounded by walls.", 1));
	mlx->cpy_map[y][x] = 'x';
	if (flood_fill_check(x - 1, y, mlx) == 1)
		return (1);
	if (flood_fill_check(x, y - 1, mlx) == 1)
		return (1);
	if (flood_fill_check(x + 1, y, mlx) == 1)
		return (1);
	if (flood_fill_check(x, y + 1, mlx) == 1)
		return (1);
	return (0);
}

int	copy_map(t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < mlx->n_lines)
	{
		x = 0;
		mlx->len = (int)ft_strlen(mlx->map[y]);
		mlx->cpy_map[y] = ft_calloc(1, mlx->len * sizeof(char) + 1);
		if (!mlx->cpy_map[y])
			return (1);
		while (x < mlx->len)
		{
			mlx->cpy_map[y][x] = mlx->map[y][x];
			x++;
		}
		y++;
	}
	return (0);
}

int	checkmap(t_mlx *mlx)
{
	mlx->cpy_map = ft_calloc(1, sizeof(char *) * (mlx->n_lines + 1));
	if (!mlx->cpy_map)
		return (1);
	if (copy_map(mlx) == 1)
		return (1);
	if (flood_fill_check(mlx->s_posX, mlx->s_posY, mlx) == 1)
	{
		free_map(mlx->cpy_map, mlx);
		return (1);
	}
	free_map(mlx->cpy_map, mlx);
	return (0);
}
