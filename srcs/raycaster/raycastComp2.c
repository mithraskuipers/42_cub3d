/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastComp2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 09:50:33 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 16:17:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*
init_side_dist() determines side_dist.x and side_dist.y, which re initially the
distance the distance that the ray has to travel from its start position to the
first x-side and y-side, respectfully. Note: Here these values are only
initialized. In later steps, the side_dist.x and side_dist.y will be adjusted.
*/

void	init_side_dist(t_ray *ray, t_pov *pov)
{
	if (ray->dir.x < 0)
	{
		ray->side_dist.x = (pov->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->side_dist.x = (ray->map.x + 1.0 - pov->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->side_dist.y = (pov->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->side_dist.y = (ray->map.y + 1.0 - pov->pos.y) * ray->delta_dist.y;
	}
}

/*
comp_side_dist() computes the side_dist which contains the distance that a ray
has to travel from its start position to go to a neighboring grid border. To
exemplify, it tells you how much the ray has to "grow" from its start position
in order to travel to a neighboring x-axis grid border ("side_dist.x"). The same
applies for y-axis grid borders ("side_dist.y"). It is different from 
"delta_dist" in that "side_dist" concerns the distance from start to grid
border, while delta_dist concerns the distance from grid border to grid border.
Note: This function can theoretically run indefinately, since it will only stop
running if a wall has been hit. When it is done looping, you have the data to
calculate the distance of the ray to the wall. In turn, with this you can
compute how tall the wall has to be drawn (see comp_perp_wall_dist()).

"wall_side" contains information regarding the type of wall that has been hit,
differentiating between "x-side" (wall_side = 0) and "y-side" walls 
(wall_side = 1). By x-side and y-side, I mean the lines of the grid that are the
borders between two squares.

"map" refers to the current grid square that the ray is in. It is expressed in
x-axis and y-axis integer coordinates.

"step" refers to an entire grid square step in the x-axis or y-axis. The
step.x and step.y values are either -1 or 1. These values are set in set_step().
"side_dist" get incremented with "delta_dist" with every jump in their 
direction. "map" gets incremented with every "step".
*/

void	comp_side_dist(t_ray *ray, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x = ray->side_dist.x + ray->delta_dist.x;
			ray->map.x = ray->map.x + ray->step.x;
			ray->wall_side = 0;
		}
		else
		{
			ray->side_dist.y = ray->side_dist.y + ray->delta_dist.y;
			ray->map.y = ray->map.y + ray->step.y;
			ray->wall_side = 1;
		}
		if (map[ray->map.y][ray->map.x] == '1')
		{
			hit = 1;
		}
	}
}

/*
Repeatedly called by raycaster().
comp_perp_wall_dist() computes the perpendicular distance instead of the
Euclidean distance used in other cub3D solutions. The perpendicular distance
is basically the distance between the camera plane and the wall that the current
ray has hit. This information is used to determine how tall the wall has to be
drawn. It is called the perpendicular distance because it is the distance
between the camera plane (for a specific x-axis value on the camera plane), and
where the wall has been hit, assuming that we start measuring from the camera 
plane x-axis value and draw a line that is lying perpendicularly on the camera
plane (= 90 degrees), and goes straight forward to the wall. For an example:
https://lodev.org/cgtutor/images/raycastperpwalldist.png
*/

void	comp_perp_wall_dist(t_ray *ray)
{
	if (ray->wall_side == 0)
		ray->perp_wall_distance = (ray->side_dist.x - ray->delta_dist.x);
	else if (ray->wall_side == 1)
		ray->perp_wall_distance = (ray->side_dist.y - ray->delta_dist.y);
}

/*
where_was_wall_hit() computes where the ray has hit the wall. The outcome is
stored in ray->wall_x, which contains the exact value where the wall was hit,
not just the integer coordinates. This data is used to figure out which x-axis
value oftexture we need to check and project to the screen.
*/

void	where_was_wall_hit(t_ray *ray, t_pov *pov)
{
	if (ray->wall_side)
		ray->wall_x = pov->pos.x + (ray->perp_wall_distance * ray->dir.x);
	else
		ray->wall_x = pov->pos.y + (ray->perp_wall_distance * ray->dir.y);
}
