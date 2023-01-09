/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingCheck.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:02 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/09 11:00:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	checkPlayerCount(t_game *game)
{
	if (game->player_count != 1)
		msgErrExit("Your map contains more than 1 player spawning position.\n", 1);
}

int	mapCheckExt(t_game *game)
{
	if (!ft_strrchr(game->mapdata.mapPath, '.') || \
	ft_strncmp(ft_strrchr(game->mapdata.mapPath, '.'), ".cub", 5))
		return (msgErrExit("Please provide a map with .cub extension.", 1));
	return (0);
}
