/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variables.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 13:50:36 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/14 15:36:27 by dkramer       ########   odam.nl         */
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

int	get_one_variable(t_mlx *mlx, char *line)
{
	//1 check for matching first characters skipping spaces ft_split
		//2 skip new lines
		//3 check if have all elements before map
	char	**split_line;
	char	**split_color;

	split_color = NULL;
	split_line = ft_split(line, ' ');
	if (!ft_strncmp("NO", split_line[0], 2))
	{
		if (mlx->NO)
			return (error_msg_ret("Double variable in map.", 1));
		mlx->NO= split_line[1];
	}
	else if (!ft_strncmp("SO", split_line[0], 2))
	{
		if (mlx->SO)
			return (error_msg_ret("Double variable in map.", 1));
		mlx->SO = split_line[1];
	}
	else if (!ft_strncmp("WE", split_line[0], 2))
	{
		if (mlx->WE)
			return (error_msg_ret("Double variable in map.", 1));
		mlx->WE = split_line[1];
	}
	else if (!ft_strncmp("EA", split_line[0], 2))
	{
		if (mlx->EA)
			return (error_msg_ret("Double variable in map.", 1));
		mlx->EA = split_line[1];
	}
	else if (!ft_strncmp("F", split_line[0], 2))
	{
		if (mlx->fcolor)
			return (error_msg_ret("Double variable in map.", 1));
		split_color = ft_split(split_line[1], ',');
		mlx->fcolor = ft_atoi(split_color[0]) << 24 | ft_atoi(split_color[1]) << 16 | ft_atoi(split_color[2]) << 8 | 0xff;
		free_split(split_color);
	}
	else if (!ft_strncmp("C", split_line[0], 2))
	{
		if (mlx->ccolor)
			return (error_msg_ret("Double variable in map.", 1));
		split_color = ft_split(split_line[1], ',');
		mlx->ccolor = ft_atoi(split_color[0]) << 24 | ft_atoi(split_color[1]) << 16 | ft_atoi(split_color[2]) << 8 | 0xff;
		free_split(split_color);
	}
	else
	{
		printf("%s\n", split_line[1]);
		if (!ft_strrchr("01NESW ", split_line[0][0]))
			return (error_msg_ret("Unknown variable in map.", 1));
		return (1);
	}
	free (split_line[0]);
	printf("%s\n", split_line[1]);
	free (split_line);
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
            if (mlx->fcolor && mlx->ccolor && mlx->NO && mlx->SO && mlx->WE && mlx->EA)
                break ;
            if (get_one_variable(mlx, line) == 1)
                return (1);
        }
		if (line)
			free (line);
		mlx->n_till_map++;
	}
	close (mlx->fd);
	if (!mlx->fcolor || !mlx->ccolor || !mlx->NO || !mlx->SO || !mlx->WE || !mlx->EA)
		return (error_msg_ret("Variable in map is missing.", 1));
    printf("%d\n", mlx->n_till_map);
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
}