/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:04 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/08 22:12:00 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	ft_fmod(float f)
{
	while (f <= -1 || f >= 1)
	{
		if (f < 0)
			f += 1;
		else
			f -= 1;
	}
	return (f);
}

void	compRayMap(t_ray *ray, t_pov *pov)
{
	ray->map.x = pov->pos.x;
	ray->map.y = pov->pos.y;
}

void	howTallWallLine(t_ray *ray)
{
	ray->texLineScale = 1 / (ray->perpetualWallDistance);
}

int	whichTextureHasWall(t_game *game, char wall_ori)
{
	if (wall_ori == 'N')
		game->ray.texture = game->textures[NORTH];
	else if (wall_ori == 'E')
		game->ray.texture = game->textures[EAST];
	else if (wall_ori == 'S')
		game->ray.texture = game->textures[SOUTH];
	else if (wall_ori == 'W')
		game->ray.texture = game->textures[WEST];
	else
		msgErrExit("Failure while running set_texture()", 1);
	return (1);
}

void	raycaster(t_game *game, t_pov *pov)
{
	game->ray.screenXPos = 0;

	int screen_width_tmp;
	screen_width_tmp = game->screen_width;
	drawBackground(game);
	while (game->ray.screenXPos < screen_width_tmp)
	{
		compCameraSpaceX(game, pov, game->ray.screenXPos);
		compRayDir(&game->ray, pov);
		compRayMap(&game->ray, pov);
		compDeltaDist(&game->ray);
		setStep(&game->ray);
		compInitSideDist(&game->ray, pov);
		compSideDist(&game->ray, game->mapdata.map);
		compPerpetualWallDist(&game->ray);
		whichWallWasHit(game);
		whichTextureHasWall(game, game->ray.wall_ori);
		whereWasWallHit(&game->ray, pov);
		howTallWallLine(&game->ray);
		game->ray.pixelPos.x = game->ray.screenXPos;
		setCurrentRayTexture(game);
		howToCenterLine(game);
		drawCurWallLine(game);
		game->ray.screenXPos++;
	}
}
