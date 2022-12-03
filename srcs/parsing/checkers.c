/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkuipers <mkuipers@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 08:47:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/12/03 10:28:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*check if surrounded by walls*/
int	map_floodfill(int x, int y, t_game *game)
{
	if ((x < 0) || (x >= game->map_widest) || (y < 0) || (y >= game->n_rows))
		return (0);
	if (game->map_tmp[y][x] == '1')
		return (0);
	if (game->map_tmp[y][x] == 'x')
		return (0);
	if ((x + 1 < game->map_widest && game->map_tmp[y][x + 1] == ' ')
		|| (x - 1 >= 0 && game->map_tmp[y][x - 1] == ' ') || (y + 1
		< game->n_rows && game->map_tmp[y + 1][x] == ' ') || (y - 1
		>= 0 && game->map_tmp[y - 1][x] == ' '))
		if (game->map_tmp[y][x] == '0')
			return (error_msg_ret("Map not surrounded by walls.", 1));
	if (x == 0 || y == 0 || y == game->n_rows - 1
		|| x == game->map_widest - 1)
		return (error_msg_ret("Map not surrounded by walls.", 1));
	game->map_tmp[y][x] = 'x';
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
		game->map_tmp[y] = ft_calloc(1, game->len * sizeof(char) + 1);
		if (!game->map_tmp[y])
			return (1);
		while (x < game->len)
		{
			game->map_tmp[y][x] = mapdata->map[y][x];
			x++;
		}
		y++;
	}
	return (0);
}

int	map_check(t_game *game, t_mapdata *mapdata)
{
	game->map_tmp = ft_calloc(1, sizeof(char *) * (game->n_rows + 1));
	if (!game->map_tmp)
		return (1);
	if (map_copy(game, mapdata) == 1)
		return (1);
	if (map_floodfill(game->playerSpawnX, game->playerSpawnY, game) == 1)
	{
		map_free(game->map_tmp, game);
		return (1);
	}
	// TODO: Add check if player position is in the map at all
	// Also check if there is only 1 player in the game, not more / less than 1
	map_free(game->map_tmp, game);
	return (0);
}
