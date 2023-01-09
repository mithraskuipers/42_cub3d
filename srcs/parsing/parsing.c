/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:02 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/09 10:58:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	get_other_cases(char **split_line, t_mapdata *mapdata, t_game *game)
{
	if (!ft_strncmp("F", split_line[0], 1) || !ft_strncmp("C", split_line[0], 1))
	{
		if (parseColorsLine(split_line, mapdata) == 1)
			return (1);
		return (0);
	}
	else if (ft_strrchr("01 ", split_line[0][0]))
	{
		game->stop = 1;
		return (freeSplit(split_line, false, 0), 0);
	}
	else if (split_line[1])
		return (free_all_and_error(split_line, "Unknown variable in map."));
	return (0);
}

int	getMapConfigVar(t_game *game, char *line, t_mapdata *mapdata)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if ((!ft_strncmp("NO", split_line[0], 2) || !ft_strncmp("SO", split_line[0],
				2) || !ft_strncmp("WE", split_line[0], 2) || !ft_strncmp("EA",
				split_line[0], 2) || !ft_strncmp("F", split_line[0], 1)
			|| !ft_strncmp("C", split_line[0], 1)) && !split_line[1])
		return (free_all_and_error(split_line, "Wrong format variable."));
	if ((mapdata->paths[NORTH] && !ft_strncmp("NO", split_line[0], 2)) || (mapdata->paths[SOUTH]
			&& !ft_strncmp("SO", split_line[0], 2)) || (mapdata->paths[EAST]
			&& !ft_strncmp("EA", split_line[0], 2)) || (mapdata->paths[WEST]
			&& !ft_strncmp("WE", split_line[0], 2)))
		return (free_all_and_error(split_line, "Double variable in map."));
	if (!ft_strncmp("NO", split_line[0], 2))
		mapdata->paths[NORTH] = split_line[1];
	else if (!ft_strncmp("SO", split_line[0], 2))
		mapdata->paths[SOUTH] = split_line[1];
	else if (!ft_strncmp("WE", split_line[0], 2))
		mapdata->paths[WEST] = split_line[1];
	else if (!ft_strncmp("EA", split_line[0], 2))
		mapdata->paths[EAST] = split_line[1];
	else
		return (get_other_cases(split_line, mapdata, game));
	freeSplit(split_line, true, 1);
	return (0);
}

int	loop_through_lines(t_game *game, char *line, t_mapdata *mapdata)
{
	while (game->gnl_ret)
	{
		game->gnl_ret = get_next_line(game->mapdata.mapFd, &line);
		if (game->gnl_ret == -1)
			return (1);
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			if (game->stop == 1)
			{
				free (line);
				break ;
			}
			if (getMapConfigVar(game, line, mapdata) == 1)
				return (free (line), 1);
		}
		if (line)
			free (line);
		if (!game->stop)
			game->whenMapMazeStart++;
	}
	return (0);
}

int	getMapCfg(t_game *game, char *line, t_mapdata *mapdata)
{
	game->mapdata.mapFd = open(game->mapdata.mapPath, O_RDONLY);
	if (game->mapdata.mapFd == -1)
		return (1);
	if (loop_through_lines(game, line, mapdata) == 1)
		return (1);
	close (game->mapdata.mapFd);
	if (!mapdata->paths[NORTH] || !mapdata->paths[EAST] || \
	!mapdata->paths[SOUTH] || !mapdata->paths[WEST] || \
	!mapdata->floorRGB || !mapdata->ceilingRGB)
		return (msgErrExit("Variable in map is missing.", 1));
	return (0);
}

int	mapOpen(t_game *game)
{
	game->mapdata.mapFd = open(game->mapdata.mapPath, O_RDONLY);
	if (game->mapdata.mapFd < 0)
		msgErrExit("Failed to run open() on the provided map.", 1);
	return (0);
}

int	isCharInString(char c, char *s)
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

void	mapFloodfill(t_game *game, int x, int y)
{
	int curChar;

	curChar = game->cpy_map[y][x];
	if (curChar != 'N' && curChar != 'E' && curChar != 'S' && curChar != 'W'
	&& curChar != '1' && curChar != '0')
		msgErrExit("Your map contains errors.", 1);
	if (game->cpy_map[y][x] == '0')
	{
		game->cpy_map[y][x] = '1';
		mapFloodfill(game, x, y - 1);
		mapFloodfill(game, x, y + 1);
		mapFloodfill(game, x - 1, y);
		mapFloodfill(game, x + 1, y);
	}
	if (isCharInString(game->cpy_map[y][x], "NESW"))
	{
		game->player_count++;
		game->cpy_map[y][x] = '1';
		mapFloodfill(game, x, y - 1);
		mapFloodfill(game, x, y + 1);
		mapFloodfill(game, x - 1, y);
		mapFloodfill(game, x + 1, y);
	}
	if (game->cpy_map[y][x] == '1')
		return ;
}
