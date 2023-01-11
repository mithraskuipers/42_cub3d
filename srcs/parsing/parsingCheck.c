/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingCheck.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:02 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 17:01:00 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	check_player_count(t_game *game)
{
	if (game->player_count != 1)
		msg_err_exit("Your map contains more than 1 player \
		spawning position.", 1);
}

int	map_check_ext(t_game *game)
{
	if (!ft_strrchr(game->mapdata.map_path, '.') || \
	ft_strncmp(ft_strrchr(game->mapdata.map_path, '.'), ".cub", 5))
		return (msg_err_exit("Please provide a map with .cub extension.", 1));
	return (0);
}

int	check_dup(char **split_line, t_mapdata *mapdata)
{
	if ((mapdata->paths[NORTH] && !ft_strncmp("NO", split_line[0], 2))
		|| (mapdata->paths[SOUTH] && !ft_strncmp("SO", split_line[0], 2))
		|| (mapdata->paths[EAST] && !ft_strncmp("EA", split_line[0], 2))
		|| (mapdata->paths[WEST] && !ft_strncmp("WE", split_line[0], 2)))
		return (1);
	return (0);
}

int	is_char_in_string(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

int	map_floodfill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->width_map || y < 0 || y >= game->height_map)
		return (0);
	if (game->cpy_map[y][x] == '1' || game->cpy_map[y][x] == 'x')
		return (0);
	if (is_char_in_string(game->cpy_map[y][x], "NESW"))
		game->player_count++;
	if ((x + 1 < game->width_map && game->cpy_map[y][x + 1] == ' ')
		|| (x - 1 >= 0 && game->cpy_map[y][x - 1] == ' ') || (y + 1
		< game->height_map && game->cpy_map[y + 1][x] == ' ') || (y - 1
		>= 0 && game->cpy_map[y - 1][x] == ' '))
		if (game->cpy_map[y][x] == '0')
			return (msg_err_exit("Player can walk walk out of map.", 1));
	if (x == 0 || y == 0 || y == game->height_map - 1
		|| x == game->width_map - 1)
		return (msg_err_exit("Player can walk walk out of map.", 1));
	game->cpy_map[y][x] = 'x';
	if (map_floodfill(game, x - 1, y) == 1)
		return (1);
	if (map_floodfill(game, x, y - 1) == 1)
		return (1);
	if (map_floodfill(game, x + 1, y) == 1)
		return (1);
	if (map_floodfill(game, x, y + 1) == 1)
		return (1);
	return (0);
}
