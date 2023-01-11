/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastComp1.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:05:59 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 15:04:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*
Generally speaking, the game window dimensions can be expressed in x-axis and
y-axis pixel measurements. If the x and y dimensions of the window are 640x480,
you know there are 640 pixels on the x-axis of the window. For each of these
x-axis values (i.e. window columns) we send out a ray. However, instead of using
the raw x-axis values (ranging from 0-640 in this example), we transform these
x-axis coordinates to values ranging from -1 to 1, where the exact center of the
x-axis range has the value 0. comp_camera_space_x(2) does exactly this, namely
transforming the x-axis range values to values -1 (left) and 1 (right). We refer
to these new x-axis values as the camera space.
*/

void	comp_camera_space_x(t_game *game, t_pov *pov, int col)
{
	pov->cameraSpaceX = (2 * col / (double)game->screen_width - 1) * -1;
}

/*
comp_ray_dir(2) computes the direction it should send the ray to. It receives
the data to compute a single ray direction. From the outside, this function is
called for each possible screen x-axis value that is transformed to be an x-axis
value in camera space format.
*/

void	comp_ray_dir(t_ray *ray, t_pov *pov)
{
	ray->dir.x = pov->dir.x + pov->plane.x * pov->cameraSpaceX;
	ray->dir.y = pov->dir.y + pov->plane.y * pov->cameraSpaceX;
}

void	comp_ray_map(t_ray *ray, t_pov *pov)
{
	ray->map.x = pov->pos.x;
	ray->map.y = pov->pos.y;
}

/*
In this cub3D implementating, you can represent the game world in a rough grid
of squares. In the current raycasting approach, namely DDA, we keep track of the
grid square that the current ray is in (i.e. "ray position") in int variables
map.x and map.y. However, if we want to store both (a) which square the ray is
in, and (b) where in the square the ray is in, we need to store the data in a
float.
*/

/*
delta_dist contains the distance that a ray has to travel to go from one grid
border to another, but neighboring, grid border. To exemplify, it tells you how
much the ray has to "grow" in order to travel from one x-axis grid border to a
neighboring x-axis grid border (delta_dist.x). The same applies for y-axis grid
borders (delta_dist.y). It is different from side_dist in that delta_dist
concerns the distance from grid border to grid border, while side_dist concerns
the distance from start to grid border.
*/

void	comp_delta_dist(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->delta_dist.x = pow(10, 30);
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = pow(10, 30);
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
}

/*
set_step() determines in which direction the DDA algorithm should jump, depending
on the sign of the current ray direction.

Explanation:
The DDA algorithm will always jump exactly one square in each iteration. Either
jumping a square on the x-axis or on the y-axis. If the ray direction has a
negative x-axis value, step.x becomes -1, otherwise 1. Similarly, if it has a
negative y-axis value, step.y becomes -1, otherwise 1.
*/

void	set_step(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
	}
	else
	{
		ray->step.x = 1;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
	}
	else
	{
		ray->step.y = 1;
	}
}
