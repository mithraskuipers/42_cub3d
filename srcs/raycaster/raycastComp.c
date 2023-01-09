/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastComp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:05:59 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/09 18:33:45 by mikuiper      ########   odam.nl         */
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
x-axis range has the value 0. compCameraSpaceX(2) does exactly this, namely
transforming the x-axis range values to values -1 (left) and 1 (right). We refer
to these new x-axis values as the camera space.
*/

void	compCameraSpaceX(t_game *game, t_pov *pov, int col)
{
	pov->cameraSpaceX = (2 * col / (double)game->screen_width - 1) * -1;
}

/*
compRayDir(2) computes the direction it should send the ray to. It receives the
data to compute a single ray direction. From the outside, this function is
called for each possible screen x-axis value that is transformed to be an x-axis
value in camera space format.
*/

void	compRayDir(t_ray *ray, t_pov *pov)
{
	ray->dir.x = pov->dir.x + pov->plane.x * pov->cameraSpaceX;
	ray->dir.y = pov->dir.y + pov->plane.y * pov->cameraSpaceX;
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
deltaDist contains the distance that a ray has to travel to go from one grid
border to another, but neighboring, grid border. To exemplify, it tells you how
much the ray has to "grow" in order to travel from one x-axis grid border to a
neighboring x-axis grid border (deltaDist.x). The same applies for y-axis grid
borders (deltaDist.y). It is different from sideDist in that deltaDist concerns
the distance from grid border to grid border, while sideDist concerns the
distance from start to grid border.
*/

void	compDeltaDist(t_ray *ray)
{
	if (ray->dir.x == 0)
		ray->deltaDist.x = pow(10,30);
	else
		ray->deltaDist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->deltaDist.y = pow(10,30);
	else
		ray->deltaDist.y = fabs(1 / ray->dir.y);
}

/*
setStep() determines in which direction the DDA algorithm should jump, depending
on the sign of the current ray direction.

Explanation:
The DDA algorithm will always jump exactly one square in each iteration. Either
jumping a square on the x-axis or on the y-axis. If the ray direction has a
negative x-axis value, step.x becomes -1, otherwise 1. Similarly, if it has a
negative y-axis value, step.y becomes -1, otherwise 1.
*/

void	setStep(t_ray *ray)
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

/*
initSideDist() determines sideDist.x and sideDist.y, which re initially the
distance the distance that the ray has to travel from its start position to the
first x-side and y-side, respectfully. Note: Here these values are only
initialized. In later steps, the sideDist.x and sideDist.y will be adjusted.
*/

void	initSideDist(t_ray *ray, t_pov *pov)
{
	if (ray->dir.x < 0)
	{
		ray->sideDist.x = (pov->pos.x - ray->map.x) * ray->deltaDist.x;
	}
	else
	{
		ray->sideDist.x = (ray->map.x + 1.0 - pov->pos.x) * ray->deltaDist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->sideDist.y = (pov->pos.y - ray->map.y) * ray->deltaDist.y;
	}
	else
	{
		ray->sideDist.y = (ray->map.y + 1.0 - pov->pos.y) * ray->deltaDist.y;
	}
}

/*
compSideDist() computes the sideDist which contains the distance that a ray has
to travel from its start position to go to a neighboring grid border. To
exemplify, it tells you how much the ray has to "grow" from its start position
in order to travel to a neighboring x-axis grid border ("sideDist.x"). The same
applies for y-axis grid borders ("sideDist.y"). It is different from "deltaDist"
in that "sideDist" concerns the distance from start to grid border, while 
deltaDist concerns the distance from grid border to grid border. Note: This
function can theoretically run indefinately, since it will only stop running if
a wall has been hit. When it is done looping, you have the data to calculate the
distance of the ray to the wall. In turn, with this you can compute how tall the
wall has to be drawn (see compPerpendicularWallDist()).

"wallSide" contains information regarding the type of wall that has been hit,
differentiating between "x-side" (wallSide = 0) and "y-side" walls 
(wallSide = 1). By x-side and y-side, I mean the lines of the grid that are the
borders between two squares.

"map" refers to the current grid square that the ray is in. It is expressed in
x-axis and y-axis integer coordinates.

"step" refers to an entire grid square step in the x-axis or y-axis. The
step.x and step.y values are either -1 or 1. These values are set in setStep().
"sideDist" get incremented with "deltaDist" with every jump in their direction.
"map" gets incremented with every "step".
*/

void	compSideDist(t_ray *ray, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x = ray->sideDist.x + ray->deltaDist.x;
			ray->map.x = ray->map.x + ray->step.x;
			ray->wallSide = 0;
		}
		else
		{
			ray->sideDist.y = ray->sideDist.y + ray->deltaDist.y;
			ray->map.y = ray->map.y + ray->step.y;
			ray->wallSide = 1;
		}
		if (map[ray->map.y][ray->map.x] == '1')
		{
			hit = 1;
		}
	}
}

/*
Repeatedly called by raycaster().
compPerpendicularWallDist() computes the perpendicular distance instead of the
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

void	compPerpendicularWallDist(t_ray *ray)
{
	if (ray->wallSide == 0)
		ray->perpendicularWallDistance = (ray->sideDist.x - ray->deltaDist.x);
	else if (ray->wallSide == 1)
		ray->perpendicularWallDistance = (ray->sideDist.y - ray->deltaDist.y);
}

/*
TODO whichWallWasHit() computes which wall was hit.
*/

void	whichWallWasHit(t_game *game)
{
	// kijkt linkerhelft, linkerzijde
	if (game->ray.dir.x < 0 && game->ray.dir.y < 0)
	{
		if (game->ray.wallSide == SIDE_VERT)
			game->ray.wallDirection = 'N';
		else if (game->ray.wallSide == SIDE_HORI)
			game->ray.wallDirection = 'W';
	}
	// kijkt linkerhelft, rechterzijde
	else if (game->ray.dir.x < 0 && game->ray.dir.y >= 0)
	{
		if (game->ray.wallSide == SIDE_VERT)
			game->ray.wallDirection = 'S';
		else if (game->ray.wallSide == SIDE_HORI)
			game->ray.wallDirection = 'W';
	}
	// kijkt rechterhelft, linkerzijde
	else if (game->ray.dir.x >= 0 && game->ray.dir.y < 0)
	{
		if (game->ray.wallSide == SIDE_VERT)
			game->ray.wallDirection = 'N';
		else if (game->ray.wallSide == SIDE_HORI)
			game->ray.wallDirection = 'E';
	}
	// kijkt rechterhelft, rechterzijde
	else if (game->ray.dir.x >= 0 && game->ray.dir.y >= 0)
	{
		if (game->ray.wallSide == SIDE_VERT)
			game->ray.wallDirection = 'S';
		else if (game->ray.wallSide == SIDE_HORI)
			game->ray.wallDirection = 'E';
	}
}

/*
whereWasWallHit() computes where the ray has hit the wall.
*/

void	whereWasWallHit(t_ray *ray, t_pov *pov)
{
	if (ray->wallSide)
		ray->wallX = pov->pos.x + ray->perpendicularWallDistance * ray->dir.x;
	else
		ray->wallX = pov->pos.y + ray->perpendicularWallDistance * ray->dir.y;
}
