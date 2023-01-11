/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastWhichWall.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:54:25 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 14:56:12 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*
which_wall_was_hit() computes which wall was hit.
*/

void	which_wall_was_hit1(t_game *game)
{	
	if ((game->ray.dir.x >= 0) && (game->ray.dir.y < 0))
	{
		if (game->ray.wallSide == SIDE_VERT)
			game->ray.wall_direction = 'N';
		else if (game->ray.wallSide == SIDE_HORI)
			game->ray.wall_direction = 'E';
	}
	else if ((game->ray.dir.x >= 0) && (game->ray.dir.y >= 0))
	{
		if (game->ray.wallSide == SIDE_VERT)
			game->ray.wall_direction = 'S';
		else if (game->ray.wallSide == SIDE_HORI)
			game->ray.wall_direction = 'E';
	}
}

void	which_wall_was_hit2(t_game *game)
{	
	if ((game->ray.dir.x < 0) && (game->ray.dir.y >= 0))
	{
		if (game->ray.wallSide == SIDE_VERT)
			game->ray.wall_direction = 'S';
		else if (game->ray.wallSide == SIDE_HORI)
			game->ray.wall_direction = 'W';
	}
	if ((game->ray.dir.x < 0) && (game->ray.dir.y < 0))
	{
		if (game->ray.wallSide == SIDE_VERT)
			game->ray.wall_direction = 'N';
		else if (game->ray.wallSide == SIDE_HORI)
			game->ray.wall_direction = 'W';
	}
}
