/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:17 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 11:31:23 by dkramer       ########   odam.nl         */
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
	return (msg_err_exit(str, 1));
}

int	cleanupCharDP(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (0);
}

int	cleanup_everything(t_game *game)
{
	cleanupCharDP(game->mapdata.map);
	cleanupCharDP(game->cpy_map);
	if (game->textures[NORTH] != NULL)
		mlx_delete_texture(game->textures[NORTH]);
	if (game->textures[EAST] != NULL)
		mlx_delete_texture(game->textures[EAST]);
	if (game->textures[SOUTH] != NULL)
		mlx_delete_texture(game->textures[SOUTH]);
	if (game->textures[WEST] != NULL)
		mlx_delete_texture(game->textures[WEST]);
	free(game->mapdata.paths[NORTH]);
	free(game->mapdata.paths[EAST]);
	free(game->mapdata.paths[SOUTH]);
	free(game->mapdata.paths[WEST]);
	return (1);
}
