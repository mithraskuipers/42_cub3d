/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variables.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 13:50:36 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/18 08:56:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parsing.h"

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
	return (error_msg_ret(str, 1));
}

int	get_colors(char	**split_line, t_parse *parse)
{
	char	**split_color;

	if ((!ft_strncmp("C", split_line[0], 1) && parse->ccolor)
		|| (!ft_strncmp("F", split_line[0], 1) && parse->fcolor))
		return (free_all_and_error(split_line, "Double variable in map."));
	split_color = ft_split(split_line[1], ',');
	if (!split_color[0] || !split_color[1] || !split_color[2])
	{
		free_split(split_color, false, 0);
		return (free_all_and_error(split_line, "Wrong format variable."));
	}
	if (!ft_strncmp("F", split_line[0], 1))
		parse->fcolor = ft_atoi(split_color[0]) << 24 | ft_atoi(split_color[1])
			<< 16 | ft_atoi(split_color[2]) << 8 | 0xff;
	if (!ft_strncmp("C", split_line[0], 1))
		parse->ccolor = ft_atoi(split_color[0]) << 24 | ft_atoi(split_color[1])
			<< 16 | ft_atoi(split_color[2]) << 8 | 0xff;
	free_split(split_color, false, 0);
	free_split(split_line, false, 0);
	return (0);
}

int	get_other_cases(char **split_line, t_parse *parse, t_game *mlx)
{
	if (!ft_strncmp("F", split_line[0], 1)
		|| !ft_strncmp("C", split_line[0], 1))
	{
		if (get_colors(split_line, parse) == 1)
			return (1);
		return (0);
	}
	else if (ft_strrchr("01 ", split_line[0][0]))
	{
		free_split(split_line, false, 0);
		mlx->stop = 1;
		return (0);
	}
	else if (split_line[1])
		return (free_all_and_error(split_line, "Unknown variable in map."));
	return (0);
}

int	get_one_variable(t_game *mlx, char *line, t_parse *parse)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if ((!ft_strncmp("NO", split_line[0], 2) || !ft_strncmp("SO", split_line[0],
				2) || !ft_strncmp("WE", split_line[0], 2) || !ft_strncmp("EA",
				split_line[0], 2) || !ft_strncmp("F", split_line[0], 1)
			|| !ft_strncmp("C", split_line[0], 1)) && !split_line[1])
		return (free_all_and_error(split_line, "Wrong format variable."));
	if ((parse->NO && !ft_strncmp("NO", split_line[0], 2)) || (parse->SO
			&& !ft_strncmp("SO", split_line[0], 2)) || (parse->EA
			&& !ft_strncmp("EA", split_line[0], 2)) || (parse->WE
			&& !ft_strncmp("WE", split_line[0], 2)))
		return (free_all_and_error(split_line, "Double variable in map."));
	if (!ft_strncmp("NO", split_line[0], 2))
		parse->NO = split_line[1];
	else if (!ft_strncmp("SO", split_line[0], 2))
		parse->SO = split_line[1];
	else if (!ft_strncmp("WE", split_line[0], 2))
		parse->WE = split_line[1];
	else if (!ft_strncmp("EA", split_line[0], 2))
		parse->EA = split_line[1];
	else
		return (get_other_cases(split_line, parse, mlx));
	free_split(split_line, true, 1);
	return (0);
}

int	loop_through_lines(t_game *mlx, char *line, t_parse *parse)
{
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (1);
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			if (mlx->stop == 1)
			{
				free (line);
				break ;
			}
			if (get_one_variable(mlx, line, parse) == 1)
			{
				free (line);
				return (1);
			}
		}
		if (line)
			free (line);
		if (!mlx->stop)
			mlx->n_till_map++;
	}
	return (0);
}

int	get_variables(t_game *mlx, char *line, t_parse *parse)
{
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	if (loop_through_lines(mlx, line, parse) == 1)
		return (1);
	close (mlx->fd);
	if (!parse->fcolor || !parse->ccolor || !parse->NO || !parse->SO
		|| !parse->WE || !parse->EA)
		return (error_msg_ret("Variable in map is missing.", 1));
	return (0);
}

void	init_map_variables(t_game *mlx, t_parse *parse)
{
	parse->fcolor = 0;
	parse->ccolor = 0;
	parse->NO = NULL;
	parse->SO = NULL;
	parse->EA = NULL;
	parse->WE = NULL;
	mlx->stop = 0;
	mlx->n_till_map = 0;
}
