/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variables.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 13:50:36 by dkramer       #+#    #+#                 */
/*   Updated: 2022/12/07 08:30:35 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	free_split(char **split, bool skip, int index)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (skip == false)
			free (split[i]);
		else if (skip == true && i != index)
			free (split[i]);
		i++;
	}
	free (split);
}

int	free_all_and_error(char	**split_line, char *str)
{
	free_split(split_line, false, 0);
	return (errorMsgRet(str, 1));
}

int	get_colors(char	**split_line, t_mapdata *mapdata)
{
	char	**split_color;

	if ((!ft_strncmp("C", split_line[0], 1) && mapdata->ccolor)
		|| (!ft_strncmp("F", split_line[0], 1) && mapdata->fcolor))
		return (free_all_and_error(split_line, "Double variable in map."));
	split_color = ft_split(split_line[1], ',');
	if (!split_color[0] || !split_color[1] || !split_color[2])
	{
		free_split(split_color, false, 0);
		return (free_all_and_error(split_line, "Wrong format variable."));
	}
	if (!ft_strncmp("F", split_line[0], 1))
		mapdata->fcolor = ft_atoi(split_color[0]) << 24
			| ft_atoi(split_color[1]) << 16
			| ft_atoi(split_color[2]) << 8 | 0xff;
	if (!ft_strncmp("C", split_line[0], 1))
		mapdata->ccolor = ft_atoi(split_color[0]) << 24
			| ft_atoi(split_color[1])
			<< 16 | ft_atoi(split_color[2]) << 8 | 0xff;
	free_split(split_color, false, 0);
	free_split(split_line, false, 0);
	return (0);
}

int	get_other_cases(char **split_line, t_mapdata *mapdata, t_game *game)
{
	if (!ft_strncmp("F", split_line[0], 1)
		|| !ft_strncmp("C", split_line[0], 1))
	{
		if (get_colors(split_line, mapdata) == 1)
			return (1);
		return (0);
	}
	else if (ft_strrchr("01 ", split_line[0][0]))
	{
		game->stop = 1;
		return (free_split(split_line, false, 0), 0);
	}
	else if (split_line[1])
		return (free_all_and_error(split_line, "Unknown variable in map."));
	return (0);
}

int	get_one_variable(t_game *game, char *line, t_mapdata *mapdata)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if ((!ft_strncmp("NO", split_line[0], 2) || !ft_strncmp("SO", split_line[0],
				2) || !ft_strncmp("WE", split_line[0], 2) || !ft_strncmp("EA",
				split_line[0], 2) || !ft_strncmp("F", split_line[0], 1)
			|| !ft_strncmp("C", split_line[0], 1)) && !split_line[1])
		return (free_all_and_error(split_line, "Wrong format variable."));
	if ((mapdata->NO && !ft_strncmp("NO", split_line[0], 2)) || (mapdata->SO
			&& !ft_strncmp("SO", split_line[0], 2)) || (mapdata->EA
			&& !ft_strncmp("EA", split_line[0], 2)) || (mapdata->WE
			&& !ft_strncmp("WE", split_line[0], 2)))
		return (free_all_and_error(split_line, "Double variable in map."));
	if (!ft_strncmp("NO", split_line[0], 2))
		mapdata->NO = split_line[1];
	else if (!ft_strncmp("SO", split_line[0], 2))
		mapdata->SO = split_line[1];
	else if (!ft_strncmp("WE", split_line[0], 2))
		mapdata->WE = split_line[1];
	else if (!ft_strncmp("EA", split_line[0], 2))
		mapdata->EA = split_line[1];
	else
		return (get_other_cases(split_line, mapdata, game));
	free_split(split_line, true, 1);
	return (0);
}

int	loop_through_lines(t_game *game, char *line, t_mapdata *mapdata)
{
	while (game->gnl_ret)
	{
		game->gnl_ret = get_next_line(game->fd, &line);
		if (game->gnl_ret == -1)
			return (1);
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			if (game->stop == 1)
			{
				free (line);
				break ;
			}
			if (get_one_variable(game, line, mapdata) == 1)
				return (free (line), 1);
		}
		if (line)
			free (line);
		if (!game->stop)
			game->n_till_map++;
	}
	return (0);
}

int	get_variables(t_game *game, char *line, t_mapdata *mapdata)
{
	game->fd = open(game->map_filename, O_RDONLY);
	if (game->fd == -1)
		return (1);
	if (loop_through_lines(game, line, mapdata) == 1)
		return (1);
	close (game->fd);
	if (!mapdata->fcolor || !mapdata->ccolor || !mapdata->NO || !mapdata->SO
		|| !mapdata->WE || !mapdata->EA)
		return (errorMsgRet("Variable in map is missing.", 1));
	return (0);
}

void	init_map_variables(t_game *game, t_mapdata *mapdata)
{
	mapdata->fcolor = 0;
	mapdata->ccolor = 0;
	mapdata->NO = NULL;
	mapdata->SO = NULL;
	mapdata->EA = NULL;
	mapdata->WE = NULL;
	game->stop = 0;
	game->n_till_map = 0;
}
