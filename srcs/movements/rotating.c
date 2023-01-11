/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotating.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:13 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 14:03:03 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*
TODO
To rotate the direction vector and plane vector, we multiply the their values
with the rotation matrix:
[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]
*/

void	keyboard_rotate_right(t_pov *pov, double prevDirX, double prevPlaneX,
		double rotSpeed)
{
	pov->dir.x = pov->dir.x * cos(rotSpeed) - pov->dir.y * sin(rotSpeed);
	pov->dir.y = prevDirX * sin(rotSpeed) + pov->dir.y * cos(rotSpeed);
	pov->plane.x = pov->plane.x * cos(rotSpeed) - pov->plane.y * sin(rotSpeed);
	pov->plane.y = prevPlaneX * sin(rotSpeed) + pov->plane.y * cos(rotSpeed);
}

void	keyboard_rotate_left(t_pov *pov, double prevDirX, double prevPlaneX,
		double rotSpeed)
{
	pov->dir.x = pov->dir.x * cos(-rotSpeed) - pov->dir.y * sin(-rotSpeed);
	pov->dir.y = prevDirX * sin(-rotSpeed) + pov->dir.y * cos(-rotSpeed);
	pov->plane.x = pov->plane.x * cos(-rotSpeed) - pov->plane.y
		* sin(-rotSpeed);
	pov->plane.y = prevPlaneX * sin(-rotSpeed) + pov->plane.y * cos(-rotSpeed);
}
