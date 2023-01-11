/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:04 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 14:57:33 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

static void	howTallWallLine(t_ray *ray)
{
	ray->texLineScale = (1 / (ray->perpendicularWallDistance));
}

static int	whichTextureHasWall(t_game *game, char wallDirection)
{
	if (wallDirection == 'N')
		game->ray.texture = game->textures[NORTH];
	else if (wallDirection == 'E')
		game->ray.texture = game->textures[EAST];
	else if (wallDirection == 'S')
		game->ray.texture = game->textures[SOUTH];
	else if (wallDirection == 'W')
		game->ray.texture = game->textures[WEST];
	else
		msg_err_exit("Failure while running set_texture()", 1);
	return (1);
}

void	raycaster(t_game *game, t_pov *pov)
{
	game->ray.screen_x_pos = 0;

	draw_background(game);
	while (game->ray.screen_x_pos < (int)game->screen_width)
	{
		compCameraSpaceX(game, pov, game->ray.screen_x_pos);
		compRayDir(&game->ray, pov);
		compRayMap(&game->ray, pov);
		compDeltaDist(&game->ray);
		setStep(&game->ray);
		initSideDist(&game->ray, pov);
		compSideDist(&game->ray, game->mapdata.map);
		compPerpendicularWallDist(&game->ray);
		whichWallWasHit(game);
		whichTextureHasWall(game, game->ray.wallDirection);
		whereWasWallHit(&game->ray, pov);
		howTallWallLine(&game->ray);
		game->ray.pixel_pos.x = game->ray.screen_x_pos;
		setCurrentRayTexture(game);
		game->ray.wall_line_height = (game->ray.texture->height * \
		game->ray.texLineScale);
		howToCenterLine(game, game->player_height);
		drawCurWallLine(game);
		game->ray.screen_x_pos++;
	}
}
