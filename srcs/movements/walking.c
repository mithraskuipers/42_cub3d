/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walking.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:19 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/09 12:16:52 by mikuiper      ########   odam.nl         */
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
With the defined preprocessor variable BOUNCE, you can configure how much
distance there should be between the player and the wall.
*/

void	keyboardWalkUp(t_dvector *pos, t_dvector *dir, char **map, double moveSpeed)
{
	if (map[(int)(pos->y + BOUNCE)][(int)(pos->x + dir->x * moveSpeed)] != '1'
		&& map[(int)(pos->y - BOUNCE)][(int)(pos->x + dir->x * moveSpeed)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x + dir->x * moveSpeed + BOUNCE)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x + dir->x * moveSpeed - BOUNCE)] != '1')
		pos->x = pos->x + dir->x * moveSpeed;
	if (map[(int)(pos->y + dir->y * moveSpeed + BOUNCE)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y + dir->y * moveSpeed - BOUNCE)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y + dir->y * moveSpeed)][(int)(pos->x + BOUNCE)] != '1'
		&& map[(int)(pos->y + dir->y * moveSpeed)][(int)(pos->x - BOUNCE)] != '1')
		pos->y = pos->y + dir->y * moveSpeed;
}

void	keyboardWalkDown(t_dvector *pos, t_dvector *dir, char **map, double moveSpeed)
{
	if (map[(int)(pos->y + BOUNCE)][(int)(pos->x - dir->x * moveSpeed)] != '1'
		&& map[(int)(pos->y - BOUNCE)][(int)(pos->x - dir->x * moveSpeed)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x - dir->x * moveSpeed + BOUNCE)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x - dir->x * moveSpeed - BOUNCE)] != '1')
		pos->x = pos->x - dir->x * moveSpeed;
	if (map[(int)(pos->y - dir->y * moveSpeed + BOUNCE)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y - dir->y * moveSpeed - BOUNCE)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y - dir->y * moveSpeed)][(int)(pos->x + BOUNCE)] != '1'
		&& map[(int)(pos->y - dir->y * moveSpeed)][(int)(pos->x - BOUNCE)] != '1')
		pos->y = pos->y - dir->y * moveSpeed;
}

void	keyboardWalkLeft(t_dvector *pos, t_dvector *dirPerp, char **map, double moveSpeed)
{
	if (map[(int)(pos->y + BOUNCE)][(int)(pos->x - dirPerp->x * moveSpeed)] != '1'
		&& map[(int)(pos->y - BOUNCE)][(int)(pos->x - dirPerp->x * moveSpeed)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x - dirPerp->x * moveSpeed + BOUNCE)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x - dirPerp->x * moveSpeed - BOUNCE)] != '1')
		pos->x = pos->x - dirPerp->x * moveSpeed;
	if (map[(int)(pos->y - dirPerp->y * moveSpeed + BOUNCE)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y - dirPerp->y * moveSpeed - BOUNCE)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y - dirPerp->y * moveSpeed)][(int)(pos->x + BOUNCE)] != '1'
		&& map[(int)(pos->y - dirPerp->y * moveSpeed)][(int)(pos->x - BOUNCE)] != '1')
		pos->y = pos->y - dirPerp->y * moveSpeed;
}

void	keyboardWalkRight(t_dvector *pos, t_dvector *dirPerp, char **map, double moveSpeed)
{
	if (map[(int)(pos->y + BOUNCE)][(int)(pos->x + dirPerp->x * moveSpeed)] != '1'
		&& map[(int)(pos->y - BOUNCE)][(int)(pos->x + dirPerp->x * moveSpeed)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x + dirPerp->x * moveSpeed + BOUNCE)] != '1'
		&& map[(int)(pos->y)][(int)(pos->x + dirPerp->x * moveSpeed - BOUNCE)] != '1')
		pos->x += dirPerp->x * moveSpeed;
	if (map[(int)(pos->y + dirPerp->y * moveSpeed + BOUNCE)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y + dirPerp->y * moveSpeed - BOUNCE)][(int)(pos->x)] != '1'
		&& map[(int)(pos->y + dirPerp->y * moveSpeed)][(int)(pos->x + BOUNCE)] != '1'
		&& map[(int)(pos->y + dirPerp->y * moveSpeed)][(int)(pos->x - BOUNCE)] != '1')
		pos->y += dirPerp->y * moveSpeed;
}
