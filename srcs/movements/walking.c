/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walking.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 15:09:30 by mikuiper      ########   odam.nl         */
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

void	keyboard_walk_up(t_dvector *pos, t_dvector *dir, char **map, \
double move_speed)
{
	if (map[(int)(pos->y + DIST)][(int)(pos->x + dir->x * move_speed)] \
		!= '1'
		&& map[(int)(pos->y - DIST)][(int)(pos->x + dir->x * move_speed)] \
		!= '1'
		&& map[(int)(pos->y)][(int)(pos->x + dir->x * move_speed + DIST)] \
		!= '1'
		&& map[(int)(pos->y)][(int)(pos->x + dir->x * move_speed - DIST)] \
		!= '1')
		pos->x = pos->x + dir->x * move_speed;
	if (map[(int)(pos->y + dir->y * move_speed + DIST)][(int)(pos->x)] \
		!= '1'
		&& map[(int)(pos->y + dir->y * move_speed - DIST)][(int)(pos->x)] \
		!= '1'
		&& map[(int)(pos->y + dir->y * move_speed)][(int)(pos->x + DIST)] \
		!= '1'
		&& map[(int)(pos->y + dir->y * move_speed)][(int)(pos->x - DIST)] \
		!= '1')
		pos->y = pos->y + dir->y * move_speed;
}

void	keyboard_walk_down(t_dvector *pos, t_dvector *dir, char **map, \
double move_speed)
{
	if (map[(int)(pos->y + DIST)][(int)(pos->x - dir->x * move_speed)] \
	!= '1' \
	&& map[(int)(pos->y - DIST)][(int)(pos->x - dir->x * move_speed)] \
	!= '1' \
	&& map[(int)(pos->y)][(int)(pos->x - dir->x * move_speed + DIST)] \
	!= '1' \
	&& map[(int)(pos->y)][(int)(pos->x - dir->x * move_speed - DIST)] \
	!= '1')
		pos->x = pos->x - dir->x * move_speed;
	if (map[(int)(pos->y - dir->y * move_speed + DIST)][(int)(pos->x)] \
	!= '1' \
	&& map[(int)(pos->y - dir->y * move_speed - DIST)][(int)(pos->x)] \
	!= '1' \
	&& map[(int)(pos->y - dir->y * move_speed)][(int)(pos->x + DIST)] \
	!= '1' \
	&& map[(int)(pos->y - dir->y * move_speed)][(int)(pos->x - DIST)] \
	!= '1')
		pos->y = pos->y - dir->y * move_speed;
}

void	keyboard_walk_left(t_dvector *pos, t_dvector *dir_perp, char **map, \
double move_speed)
{
	if (map[(int)(pos->y + DIST)][(int)(pos->x - dir_perp->x * move_speed)] \
	!= '1'
	&& map[(int)(pos->y - DIST)][(int)(pos->x - dir_perp->x * move_speed)] \
	!= '1'
	&& map[(int)(pos->y)][(int)(pos->x - dir_perp->x * move_speed + DIST)] \
	!= '1'
	&& map[(int)(pos->y)][(int)(pos->x - dir_perp->x * move_speed - DIST)] \
	!= '1')
	pos->x = pos->x - dir_perp->x * move_speed;
	if (map[(int)(pos->y - dir_perp->y * move_speed + DIST)][(int)(pos->x)] \
	!= '1'
	&& map[(int)(pos->y - dir_perp->y * move_speed - DIST)][(int)(pos->x)] \
	!= '1'
	&& map[(int)(pos->y - dir_perp->y * move_speed)][(int)(pos->x + DIST)] \
	!= '1'
	&& map[(int)(pos->y - dir_perp->y * move_speed)][(int)(pos->x - DIST)] \
	!= '1')
	pos->y = pos->y - dir_perp->y * move_speed;
}

void	keyboard_walk_right(t_dvector *pos, t_dvector *dir_perp, char **map, \
double move_speed)
{
	if (map[(int)(pos->y + DIST)][(int)(pos->x + dir_perp->x * move_speed)] \
	!= '1'
	&& map[(int)(pos->y - DIST)][(int)(pos->x + dir_perp->x * move_speed)] \
	!= '1'
	&& map[(int)(pos->y)][(int)(pos->x + dir_perp->x * move_speed + DIST)] \
	!= '1'
	&& map[(int)(pos->y)][(int)(pos->x + dir_perp->x * move_speed - DIST)] \
	!= '1')
	pos->x = pos->x + dir_perp->x * move_speed;
	if (map[(int)(pos->y + dir_perp->y * move_speed + DIST)][(int)(pos->x)] \
	!= '1'
	&& map[(int)(pos->y + dir_perp->y * move_speed - DIST)][(int)(pos->x)] \
	!= '1'
	&& map[(int)(pos->y + dir_perp->y * move_speed)][(int)(pos->x + DIST)] \
	!= '1'
	&& map[(int)(pos->y + dir_perp->y * move_speed)][(int)(pos->x - DIST)] \
	!= '1')
	pos->y = pos->y + dir_perp->y * move_speed;
}
