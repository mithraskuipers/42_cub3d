/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 08:47:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/18 20:40:03 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*check if surrounded by walls*/
int	map_floodfill(int x, int y, t_game *game)
{
	if ((x < 0) || (x >= game->longest_width) || (y < 0) || (y >= game->n_rows))
		return (0);
	if (game->cpy_map[y][x] == '1')
		return (0);
	if (game->cpy_map[y][x] == 'x')
		return (0);
	if ((x + 1 < game->longest_width && game->cpy_map[y][x + 1] == ' ')
		|| (x - 1 >= 0 && game->cpy_map[y][x - 1] == ' ') || (y + 1
		< game->n_rows && game->cpy_map[y + 1][x] == ' ') || (y - 1
		>= 0 && game->cpy_map[y - 1][x] == ' '))
		if (game->cpy_map[y][x] == '0')
			return (error_msg_ret("Map not surrounded by walls.", 1));
	if (x == 0 || y == 0 || y == game->n_rows - 1
		|| x == game->longest_width - 1)
		return (error_msg_ret("Map not surrounded by walls.", 1));
	game->cpy_map[y][x] = 'x';
	if (map_floodfill(x - 1, y, game) == 1)
		return (1);
	if (map_floodfill(x, y - 1, game) == 1)
		return (1);
	if (map_floodfill(x + 1, y, game) == 1)
		return (1);
	if (map_floodfill(x, y + 1, game) == 1)
		return (1);
	return (0);
}

int	map_copy(t_game *game, t_mapdata *mapdata)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->n_rows)
	{
		x = 0;
		game->len = (int)ft_strlen(mapdata->map[y]);
		game->cpy_map[y] = ft_calloc(1, game->len * sizeof(char) + 1);
		if (!game->cpy_map[y])
			return (1);
		while (x < game->len)
		{
			game->cpy_map[y][x] = mapdata->map[y][x];
			x++;
		}
		y++;
	}
	return (0);
}

int	map_check(t_game *game, t_mapdata *mapdata)
{
	game->cpy_map = ft_calloc(1, sizeof(char *) * (game->n_rows + 1));
	if (!game->cpy_map)
		return (1);
	if (map_copy(game, mapdata) == 1)
		return (1);
	if (map_floodfill(game->s_posX, game->s_posY, game) == 1)
	{
		map_free(game->cpy_map, game);
		return (1);
	}
	// TODO: Add check if player position is in the map at all
	// Also check if there is only 1 player in the game, not more / less than 1
	map_free(game->cpy_map, game);
	return (0);
}
