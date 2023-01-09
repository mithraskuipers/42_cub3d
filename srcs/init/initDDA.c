/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initDDA.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:05:27 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/09 10:39:09 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	initPovDir(t_game *game, int cardinalDirection)
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

void	initPovPlane(t_game *game, int cardinalDirection)
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
initPlayerPos() offsets the player position, preventing the player from spawning
inside a wall.
*/

void	initPlayerPos(t_game *game)
{
	game->pov.pos.x = game->player.x + 0.5;
	game->pov.pos.y = game->player.y + 0.5;
}
