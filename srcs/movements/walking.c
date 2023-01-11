/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walking.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 14:32:53 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*
All functions below are similar to eachother in code and functionality.
Basically, the functions below prevent the player from walking out of bounds.
Per movement in either the U/D/L/R direction, it will check whether the movement
is allowed, and if so, it will update the player position accordingly Each of
the functions consist of two if statements, where the first one concerns
checking whether it is allowed to walk along the x-axis using the corresponding
walking key, and the second one whether it is allowed to walk along the y-axis.
With the defined preprocessor variable DIST, you can configure how much
distance there should be between the player and the wall.
*/

void	keyboard_walk_up(t_dvector *pos, t_dvector *dir, char **map,
		double moveSpeed)
{
	if (map[(int)(pos->y + DIST)][(int)(pos->x + dir->x * moveSpeed)] != '1'
		&& map[(int)(pos->y - DIST)][(int)(pos->x + dir->x * moveSpeed)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x + dir->x * moveSpeed + DIST)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x + dir->x * moveSpeed - DIST)] != '1')
		pos->x = pos->x + dir->x * moveSpeed;
	if (map[(int)(pos->y + dir->y * moveSpeed + DIST)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y + dir->y * moveSpeed - DIST)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y + dir->y * moveSpeed)][(int)(pos->x + DIST)] != '1'
		&& map[(int)(pos->y + dir->y * moveSpeed)][(int)(pos->x - DIST)] != '1')
		pos->y = pos->y + dir->y * moveSpeed;
}

void	keyboard_walk_down(t_dvector *pos, t_dvector *dir, char **map,
		double moveSpeed)
{
	if (map[(int)(pos->y + DIST)][(int)(pos->x - dir->x * moveSpeed)] != '1' \
	&& map[(int)(pos->y - DIST)][(int)(pos->x - dir->x * moveSpeed)] != '1' \
	&& map[(int)(pos->y)][(int)(pos->x - dir->x * moveSpeed + DIST)] != '1' \
	&& map[(int)(pos->y)][(int)(pos->x - dir->x * moveSpeed - DIST)] != '1')
		pos->x = pos->x - (dir->x * moveSpeed);
	if (map[(int)(pos->y - dir->y * moveSpeed + DIST)][(int)(pos->x)] != '1' \
	&& map[(int)(pos->y - dir->y * moveSpeed - DIST)][(int)(pos->x)] != '1' \
	&& map[(int)(pos->y - dir->y * moveSpeed)][(int)(pos->x + DIST)] != '1' \
	&& map[(int)(pos->y - dir->y * moveSpeed)][(int)(pos->x - DIST)] != '1')
		pos->y = pos->y - dir->y * moveSpeed;
}

void	keyboard_walk_left(t_dvector *pos, t_dvector *dirPerp, char **map,
		double moveSpeed)
{
	if (map[(int)(pos->y + DIST)][(int)(pos->x - dirPerp->x * moveSpeed)] != '1'
	&& map[(int)(pos->y - DIST)][(int)(pos->x - dirPerp->x * moveSpeed)] != '1'
	&& map[(int)(pos->y)][(int)(pos->x - dirPerp->x * moveSpeed + DIST)] != '1'
	&& map[(int)(pos->y)][(int)(pos->x - dirPerp->x * moveSpeed - DIST)] != '1')
	pos->x = pos->x - dirPerp->x * moveSpeed;
	if (map[(int)(pos->y - dirPerp->y * moveSpeed + DIST)][(int)(pos->x)] != '1'
	&& map[(int)(pos->y - dirPerp->y * moveSpeed - DIST)][(int)(pos->x)] != '1'
	&& map[(int)(pos->y - dirPerp->y * moveSpeed)][(int)(pos->x + DIST)] != '1'
	&& map[(int)(pos->y - dirPerp->y * moveSpeed)][(int)(pos->x - DIST)] != '1')
	pos->y = pos->y - dirPerp->y * moveSpeed;
}

void	keyboard_walk_right(t_dvector *pos, t_dvector *dirPerp, char **map,
		double moveSpeed)
{
	if (map[(int)(pos->y + DIST)][(int)(pos->x + dirPerp->x * moveSpeed)] != '1'
	&& map[(int)(pos->y - DIST)][(int)(pos->x + dirPerp->x * moveSpeed)] != '1'
	&& map[(int)(pos->y)][(int)(pos->x + dirPerp->x * moveSpeed + DIST)] != '1'
	&& map[(int)(pos->y)][(int)(pos->x + dirPerp->x * moveSpeed - DIST)] != '1')
	pos->x = pos->x + dirPerp->x * moveSpeed;
	if (map[(int)(pos->y + dirPerp->y * moveSpeed + DIST)][(int)(pos->x)] != '1'
	&& map[(int)(pos->y + dirPerp->y * moveSpeed - DIST)][(int)(pos->x)] != '1'
	&& map[(int)(pos->y + dirPerp->y * moveSpeed)][(int)(pos->x + DIST)] != '1'
	&& map[(int)(pos->y + dirPerp->y * moveSpeed)][(int)(pos->x - DIST)] != '1')
	pos->y = pos->y + dirPerp->y * moveSpeed;
}
