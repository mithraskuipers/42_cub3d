/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastComp.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:05:59 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/12/21 22:06:00 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
The DDA algorithm will always jump exactly one square each loop, either a square
in the x-direction, or a square in the y-direction. If it has to go in the
negative or positive x-direction, and the negative or positive y-direction will
depend on the direction of the ray, and this fact will be stored in stepX and
stepY. Those variables are always either -1 or +1.
*/

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
hit is used to determinate whether or not the coming loop may be ended,
and side will contain if an x-side or a y-side of a wall was hit. If an x-side
was hit, side is set to 0, if an y-side was hit, side will be
1. By x-side and y-side, I mean the lines of the grid that are the borders between
two squares.
*/

/*
compSideDist(2) computes the sideDist which contains the distance that a ray has
to travel from its start position to go to a neighboring grid border. To
exemplify, it tells you how much the ray has to "grow" from its start position
in order to travel to a neighboring x-axis grid border (sideDist.x). The same
applies for y-axis grid borders (sideDist.y). It is different from deltaDist in
that sideDist concerns the distance from start to grid border, while deltaDist
concerns the distance from grid border to grid border.
*/

/*
"map" refers to the current grid square that the ray is in. It is expressed in
x-axis and y-axis integer coordinates.
"step" refers to an entire grid square step in the x-axis or y-axis. The
step.x and step.y values are either -1 or 1. These values are set in setStep(1).
"sideDist" get incremented with "deltaDist" with every jump in their direction.
"map" gets incremented with every "step".
*/

/*
Logic:
Loops until a wall is hit. It increments the ray with 1 grid square in each
iteration. This means that at each iteration the ray jumps a step on the x-axis
with step.x or in the y-axis with step.y. It always jumps exactly 1 square. When
it is done looping, you have the data to calculate the distance of the ray to
the wall. You can compute how high the wall has to be drawn.
*/

/*
When the ray has hit a wall, the loop ends, and then we'll know whether an 
x-side or y-side of a wall was hit in the variable "side", and what wall was hit 
with mapX and mapY. We won't know exactly where the wall was hit however, but 
that's not needed in this case because we won't use textured walls for now.
*/

void	compSideDist(t_ray *ray, char **map)
{
	int	hit;

	hit = 0;
	while (!hit)
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
setStep(1) determines in which direction the DDA algorithm should jump, 
depending on the sign of the current ray direction.

Logic:
The DDA algorithm will always jump exactly one square in each iteration. Either
a square on the x-axis or on the y-axis. If the ray direction has a negative
x-axis value, step.x becomes -1, otherwise 1. Similarly, if it has a negative
y-axis value, step.y becomes -1, otherwise 1.
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

// Calculate step and initial sideDist

void	compInitSideDist(t_ray *ray, t_pov *pov)
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
Repeatedly called by raycaster().
compPerpetualWallDist() computes the perpendicular distance instead of the
Euclidean distance used in other cub3D solutions. The perpendicular distance
is basically the distance between the camera plane and the wall that the current
ray has hit.
*/

void	compPerpetualWallDist(t_ray *ray)
{
	if (ray->wallSide == 0)
		ray->perpetualWallDistance = (ray->sideDist.x - ray->deltaDist.x);
	else if (ray->wallSide == 1)
		ray->perpetualWallDistance = (ray->sideDist.y - ray->deltaDist.y);
}

/*
whichWallWasHit(1) 
wallSide 1 = ????
wallSide 0 = ????
*/

/*
side will contain if an x-side or a y-side of a wall was hit. If an x-side
was hit, side is set to 0, if an y-side was hit, side will be 1. By x-side and
y-side, I mean the lines of the grid that are the borders between two squares.

0 = x axis
1 = y axis
*/

// dirX and dirY represent the direction of the player
// 

void	whichWallWasHit(t_game *game)
{
	// kijkt linkerhelft, linkerzijde
	if (game->ray.dir.x < 0 && game->ray.dir.y < 0)
	{
		if (game->ray.wallSide == SIDE_VER)
			game->ray.wall_ori = 'N';
		else if (game->ray.wallSide == SIDE_HOR)
			game->ray.wall_ori = 'W';
	}
	// kijkt linkerhelft, rechterzijde
	else if (game->ray.dir.x < 0 && game->ray.dir.y >= 0)
	{
		if (game->ray.wallSide == SIDE_VER)
			game->ray.wall_ori = 'S';
		else if (game->ray.wallSide == SIDE_HOR)
			game->ray.wall_ori = 'W';
	}
	// kijkt rechterhelft, linkerzijde
	else if (game->ray.dir.x >= 0 && game->ray.dir.y < 0)
	{
		if (game->ray.wallSide == SIDE_VER)
			game->ray.wall_ori = 'N';
		else if (game->ray.wallSide == SIDE_HOR)
			game->ray.wall_ori = 'E';
	}
	// kijkt rechterhelft, rechterzijde
	else if (game->ray.dir.x >= 0 && game->ray.dir.y >= 0)
	{
		if (game->ray.wallSide == SIDE_VER)
			game->ray.wall_ori = 'S';
		else if (game->ray.wallSide == SIDE_HOR)
			game->ray.wall_ori = 'E';
	}
}

/*
//wallX where exactly the wall was hit
*/

void	whereWasWallHit(t_ray *ray, t_pov *pov)
{
	if (ray->wallSide)
		ray->wallX = pov->pos.x + ray->perpetualWallDistance * ray->dir.x;
	else
		ray->wallX = pov->pos.y + ray->perpetualWallDistance * ray->dir.y;
}
