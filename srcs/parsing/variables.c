/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variables.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 13:50:36 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/15 13:51:53 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parsing.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free (split[i]);
		i++;
	}
	free (split);
}

int	get_colors(t_mlx *mlx, char	**split_line)
{
	char	**split_color;

	if ((!ft_strncmp("C", split_line[0], 1) && mlx->ccolor)
		|| (!ft_strncmp("F", split_line[0], 1) && mlx->fcolor))
	{
		free_split(split_line);
		return (error_msg_ret("Double variable in map.", 1));
	}
	split_color = ft_split(split_line[1], ',');
	if (!split_color[0] || !split_color[1] || !split_color[2])
	{
		free_split(split_color);
		free_split(split_line);
		return (error_msg_ret("Wrong format variable in map.", 1));
	}
	if (!ft_strncmp("F", split_line[0], 1))
	{
		mlx->fcolor = ft_atoi(split_color[0]) << 24 | ft_atoi(split_color[1])
			<< 16 | ft_atoi(split_color[2]) << 8 | 0xff;
		free_split(split_color);
	}
	if (!ft_strncmp("C", split_line[0], 1))
	{
		mlx->ccolor = ft_atoi(split_color[0]) << 24 | ft_atoi(split_color[1])
			<< 16 | ft_atoi(split_color[2]) << 8 | 0xff;
		free_split(split_color);
	}
	return (0);
}

int	get_one_variable(t_mlx *mlx, char *line)
{
	char	**split_line;
	
	split_line = ft_split(line, ' ');
	if (!ft_strncmp("NO", split_line[0], 2) || !ft_strncmp("SO", split_line[0], 2) || !ft_strncmp("WE", split_line[0], 2) || !ft_strncmp("EA", split_line[0], 2) || !ft_strncmp("F", split_line[0], 1) || !ft_strncmp("C", split_line[0], 1))
	{
		if (!split_line[1])
		{
			free_split(split_line);
			return (error_msg_ret("Wrong format variable in map.", 1));
		}
	}
	if (!ft_strncmp("NO", split_line[0], 2))
	{
		if (mlx->NO)
		{
			free_split(split_line);
			return (error_msg_ret("Double variable in map.", 1));
		}
		mlx->NO = split_line[1];
	}
	else if (!ft_strncmp("SO", split_line[0], 2))
	{
		if (mlx->SO)
		{
			free_split(split_line);
			return (error_msg_ret("Double variable in map.", 1));
		}
		mlx->SO = split_line[1];
	}
	else if (!ft_strncmp("WE", split_line[0], 2))
	{
		if (mlx->WE)
		{
			free_split(split_line);
			return (error_msg_ret("Double variable in map.", 1));
		}
		mlx->WE = split_line[1];
	}
	else if (!ft_strncmp("EA", split_line[0], 2))
	{
		if (mlx->EA)
		{
			free_split(split_line);
			return (error_msg_ret("Double variable in map.", 1));
		}
		mlx->EA = split_line[1];
	}
	else if (!ft_strncmp("F", split_line[0], 1) || !ft_strncmp("C", split_line[0], 1))
	{
		if (get_colors(mlx, split_line) == 1)
			return (1);
	}
	else
	{
		if (split_line[1] && (ft_strncmp("C", split_line[0], 2) || ft_strncmp("F", split_line[0], 2) || ft_strncmp("EA", split_line[0], 2) || ft_strncmp("WE", split_line[0], 2) || ft_strncmp("SO", split_line[0], 2) || ft_strncmp("NO", split_line[0], 2)))
		{
			free_split(split_line);
			return (error_msg_ret("Unknown variable in map.", 1));
		}
		if (ft_strrchr("01NESW ", split_line[0][0]))
			mlx->stop = 1;
	}
	free_split(split_line);
	return (0);
}


int	get_variables(t_mlx *mlx, char *line)
{
	mlx->n_till_map = 0;
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
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
				break;
			}
			if (get_one_variable(mlx, line) == 1)
			{
				free (line);
				return (1);
			}
        }
		if (line)
			free (line);
		mlx->n_till_map++;
	}
	close (mlx->fd);
	if (!mlx->fcolor || !mlx->ccolor || !mlx->NO || !mlx->SO || !mlx->WE || !mlx->EA)
		return (error_msg_ret("Variable in map is missing.", 1));
	return (0);
}

void	init_map_variables(t_mlx *mlx)
{
	mlx->fcolor = 0;
	mlx->ccolor = 0;
	mlx->NO = NULL;
	mlx->SO = NULL;
	mlx->EA = NULL;
	mlx->WE = NULL;
	mlx->stop = 0;
}