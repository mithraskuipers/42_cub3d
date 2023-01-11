/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotating.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:13 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 16:08:45 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*
To rotate the direction vector and plane vector, we multiply the their values
with the rotation matrix:
[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]
*/

void	keyboard_rotate_right(t_pov *pov, double prev_dir_x, \
		double prev_cam_plane_x, double rot_speed)
{
	pov->dir.x = pov->dir.x * cos(rot_speed) - pov->dir.y * sin(rot_speed);
	pov->dir.y = prev_dir_x * sin(rot_speed) + pov->dir.y * cos(rot_speed);
	pov->plane.x = pov->plane.x * cos(rot_speed) - pov->plane.y * \
	sin(rot_speed);
	pov->plane.y = prev_cam_plane_x * sin(rot_speed) + pov->plane.y * \
	cos(rot_speed);
}

void	keyboard_rotate_left(t_pov *pov, double prev_dir_x, \
		double prev_cam_plane_x, double rot_speed)
{
	pov->dir.x = pov->dir.x * (1 * cos(rot_speed)) - pov->dir.y * \
	(-1 * sin(rot_speed));
	pov->dir.y = prev_dir_x * (-1 * sin(rot_speed)) + pov->dir.y * \
	(1 * cos(rot_speed));
	pov->plane.x = pov->plane.x * (1 * cos(rot_speed)) - pov->plane.y * \
	(-1 * sin(rot_speed));
	pov->plane.y = prev_cam_plane_x * (-1 * sin(rot_speed)) + pov->plane.y * \
	(1 * cos(rot_speed));
}
