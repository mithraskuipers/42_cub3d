/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 19:45:36 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/15 20:49:12 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	read_map(char *map_name, t_env *env)
{
	int	ret;
	int	row;
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		msg_err("Failed to read the map.", 1);
	}
	(void)row;
	(void)ret;
	(void)env;
	row = 0;
	env->map->map = malloc(sizeof(char *) * (env->map->ntiles_rows + 1));
	if (!(env->map->map))
		msg_err("Failed to allocate memory for the map.", 1);
	/*
	while (row < env->map->ntiles_rows)
	{
		ret = get_next_line(fd, &env->map->map[row]);
		if (ret < 0)
			msg_err("Failed to read the map.", 1);
		row++;
	}
	close(fd); */
	return (0);
}





/* 




int	read_map(char *map_name, t_env *env)
{
	int	fd;

	fd = open(map_name, O_RDONLY);
	env->map = ft_calloc(1, sizeof(t_map));
	if (get_next_line(fd, env->map->map) == -1)
		return (1);
	return (0);
}
 */