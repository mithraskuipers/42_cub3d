/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initDDA.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:05:27 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 14:35:04 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	init_pov_dir(t_game *game, int cardinalDirection)
{
	if (cardinalDirection == 'N')
	{
		game->pov.dir.x = 0;
		game->pov.dir.y = -1;
	}
	else if (cardinalDirection == 'E')
	{
		game->pov.dir.x = 1;
		game->pov.dir.y = 0;
	}
	else if (cardinalDirection == 'S')
	{
		game->pov.dir.x = 0;
		game->pov.dir.y = 1;
	}
	else if (cardinalDirection == 'W')
	{
		game->pov.dir.x = -1;
		game->pov.dir.y = 0;
	}
}

void	init_pov_plane(t_game *game, int cardinalDirection)
{
	if (cardinalDirection == 'N')
	{
		game->pov.plane.x = -1;
		game->pov.plane.y = 0;
	}
	else if (cardinalDirection == 'E')
	{
		game->pov.plane.x = 0;
		game->pov.plane.y = -1;
	}
	else if (cardinalDirection == 'S')
	{
		game->pov.plane.x = 1;
		game->pov.plane.y = 0;
	}
	else if (cardinalDirection == 'W')
	{
		game->pov.plane.x = 0;
		game->pov.plane.y = 1;
	}
}

/*
init_player_pos() offsets the player position. It is required to prevent the game
from glitching when the player spawning position is next to a wall.
*/

void	init_player_pos(t_game *game)
{
	game->pov.pos.x = game->player.x + 0.5;
	game->pov.pos.y = game->player.y + 0.5;
}
