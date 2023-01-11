/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dagmarkramer <dagmarkramer@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:02 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 16:31:47 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	get_all_cases(char **split_line, t_mapdata *mapdata)
{
	if (!ft_strncmp("NO", split_line[0], 2))
		mapdata->paths[NORTH] = split_line[1];
	else if (!ft_strncmp("SO", split_line[0], 2))
		mapdata->paths[SOUTH] = split_line[1];
	else if (!ft_strncmp("WE", split_line[0], 2))
		mapdata->paths[WEST] = split_line[1];
	else if (!ft_strncmp("EA", split_line[0], 2))
		mapdata->paths[EAST] = split_line[1];
	else if (!ft_strncmp("F", split_line[0], 1) || !ft_strncmp("C",
			split_line[0], 1))
	{
		if (parse_colors_line(split_line, mapdata) == 1)
			return (1);
		return (0);
	}
	else if (split_line[1])
		return (free_all_and_error(split_line, "Unknown variable in map."));
	free_split(split_line, true, 1);
	return (0);
}

int	get_map_config_var(t_game *game, char *line, t_mapdata *mapdata)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
		msg_err_exit("Malloc fail", 1);
	if (!split_line[0])
		return (free_split(split_line, false, 0), 0);
	if (ft_strrchr("01 ", split_line[0][0]))
	{
		game->stop = 1;
		return (free_split(split_line, false, 0), 0);
	}
	if ((ft_strncmp("NO", split_line[0], 2) && ft_strncmp("SO", split_line[0],
				2) && ft_strncmp("WE", split_line[0], 2) && ft_strncmp("EA",
				split_line[0], 2) && ft_strncmp("F", split_line[0], 1)
			&& ft_strncmp("C", split_line[0], 1)) || !split_line[1])
		return (free_all_and_error(split_line, "Wrong format variable."));
	if (check_dup(split_line, mapdata) == 1)
		return (free_all_and_error(split_line, "Double variable in map."));
	else
		return (get_all_cases(split_line, mapdata));
	return (0);
}

int	loop_through_lines(t_game *game, char *line, t_mapdata *mapdata)
{
	while (game->gnl_ret)
	{
		game->gnl_ret = get_next_line(game->mapdata.map_fd, &line);
		if (game->gnl_ret == -1)
			return (1);
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			if (game->stop == 1)
			{
				free (line);
				break ;
			}
			if (get_map_config_var(game, line, mapdata) == 1)
				return (free (line), 1);
		}
		if (line)
			free (line);
		if (!game->stop)
			game->when_map_start++;
	}
	return (0);
}

int	get_map_cfg(t_game *game, char *line, t_mapdata *mapdata)
{
	game->mapdata.map_fd = open(game->mapdata.map_path, O_RDONLY);
	if (game->mapdata.map_fd == -1)
		return (1);
	if (loop_through_lines(game, line, mapdata) == 1)
		return (1);
	close (game->mapdata.map_fd);
	if (!mapdata->paths[NORTH] || !mapdata->paths[EAST] || \
	!mapdata->paths[SOUTH] || !mapdata->paths[WEST] || \
	mapdata->floor_rgb[0] == -1 || mapdata->ceiling_rgb[0] == -1)
		return (msg_err_exit("Variable in map is missing.", 1));
	return (0);
}

int	map_open(t_game *game)
{
	game->mapdata.map_fd = open(game->mapdata.map_path, O_RDONLY);
	if (game->mapdata.map_fd < 0)
		msg_err_exit("Failed to run open() on the provided map.", 1);
	return (0);
}
