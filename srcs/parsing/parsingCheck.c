/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingCheck.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:02 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 11:43:50 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	check_player_count(t_game *game)
{
	if (game->player_count != 1)
		msg_err_exit("Your map contains more than 1 player \
spawning position.", 1);
}

int	map_check_ext(t_game *game)
{
	if (!ft_strrchr(game->mapdata.mapPath, '.') || \
	ft_strncmp(ft_strrchr(game->mapdata.mapPath, '.'), ".cub", 5))
		return (msg_err_exit("Please provide a map with .cub extension.", 1));
	return (0);
}
