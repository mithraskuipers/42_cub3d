/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 17:17:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/15 20:46:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_env	*env;

	if (check_input(argc, argv))
		return (1);	
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (1);

	env->map = ft_calloc(1, sizeof(t_map));
	int fd = open(argv[1], O_RDONLY);	
	get_map_dim(env, fd, 0, 0);

	//printf("%d\n", env->map->ntiles_rows);
	/*
	if (read_map(argv[1], env))
		return (1);
	*/

	return (0);
}
