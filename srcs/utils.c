/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:17 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/08 22:12:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	msgErrExit(char *s, int exitCode)
{
	ft_putstr_fd("Error\n", 2);
	if (ft_strlen(s) != 0)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
	}
	exit (exitCode);
}

/*
Taken straight from the MLX readme file. It combines four individual channel
bytes into a single integer using bit-shifting.
*/

int getRGBA(int R, int G, int B, int A)
{
	return (R << 24 | G << 16 | B << 8 | A);
}

int	freeCharDP(char **ptr)
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

void	freeSplit(char **split, bool skip, int index)
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
	freeSplit(split_line, false, 0);
	return (msgErrExit(str, 1));
}

int	cleanupGame(t_game *game)
{
	freeCharDP(game->mapdata.map);
	freeCharDP(game->cpy_map);
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
