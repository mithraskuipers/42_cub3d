/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 08:47:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/18 08:56:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parsing.h"

/*check if surrounded by walls*/
int	map_floodfill(int x, int y, t_game *mlx)
{
	if ((x < 0) || (x >= mlx->longest_width) || (y < 0) || (y >= mlx->n_rows))
		return (0);
	if (mlx->cpy_map[y][x] == '1')
		return (0);
	if (mlx->cpy_map[y][x] == 'x')
		return (0);
	if ((x + 1 < mlx->longest_width && mlx->cpy_map[y][x + 1] == ' ')
		|| (x - 1 >= 0 && mlx->cpy_map[y][x - 1] == ' ') || (y + 1
		< mlx->n_rows && mlx->cpy_map[y + 1][x] == ' ') || (y - 1
		>= 0 && mlx->cpy_map[y - 1][x] == ' '))
		if (mlx->cpy_map[y][x] == '0')
			return (error_msg_ret("Map not surrounded by walls.", 1));
	if (x == 0 || y == 0 || y == mlx->n_rows - 1
		|| x == mlx->longest_width - 1)
		return (error_msg_ret("Map not surrounded by walls.", 1));
	mlx->cpy_map[y][x] = 'x';
	if (map_floodfill(x - 1, y, mlx) == 1)
		return (1);
	if (map_floodfill(x, y - 1, mlx) == 1)
		return (1);
	if (map_floodfill(x + 1, y, mlx) == 1)
		return (1);
	if (map_floodfill(x, y + 1, mlx) == 1)
		return (1);
	return (0);
}

int	map_copy(t_game *mlx, t_parse *parse)
{
	int	y;
	int	x;

	y = 0;
	while (y < mlx->n_rows)
	{
		x = 0;
		mlx->len = (int)ft_strlen(parse->map[y]);
		mlx->cpy_map[y] = ft_calloc(1, mlx->len * sizeof(char) + 1);
		if (!mlx->cpy_map[y])
			return (1);
		while (x < mlx->len)
		{
			mlx->cpy_map[y][x] = parse->map[y][x];
			x++;
		}
		y++;
	}
	return (0);
}

int	map_check(t_game *mlx, t_parse *parse)
{
	mlx->cpy_map = ft_calloc(1, sizeof(char *) * (mlx->n_rows + 1));
	if (!mlx->cpy_map)
		return (1);
	if (map_copy(mlx, parse) == 1)
		return (1);
	if (map_floodfill(mlx->s_posX, mlx->s_posY, mlx) == 1)
	{
		map_free(mlx->cpy_map, mlx);
		return (1);
	}
	// TODO: Add check if player position is in the map at all
	// Also check if there is only 1 player in the game, not more / less than 1
	map_free(mlx->cpy_map, mlx);
	return (0);
}
