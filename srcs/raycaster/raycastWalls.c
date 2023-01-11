/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastWalls.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 11:45:03 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void getTexPixelCol(t_game *game, int wallHeight, int wallLineHeight)
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	size_t exactTexPixel;

	exactTexPixel = ((size_t)(((double)wallHeight / (double)wallLineHeight) *
					(int)game->ray.texture->height) *
					(int)(game->ray.texture->width) +
					(int)game->ray.curTex) *
					4;
	R = game->ray.texture->pixels[exactTexPixel + 1];
	G = game->ray.texture->pixels[exactTexPixel + 2];
	B = game->ray.texture->pixels[exactTexPixel + 3];
	game->ray.pixelColor = convert_rgb_bytes_to_int(\
									game->ray.texture->pixels[exactTexPixel], \
									R, \
									G, \
									B);
	return;
}

void setCurrentRayTexture(t_game *game)
{
	if ((game->ray.wallDirection == 'N') || \
	(game->ray.wallDirection == 'E'))
	{
		game->ray.curTex = (game->ray.texture->width) * \
		getDecimals(game->ray.wallX);
		return;
	}
	else if ((game->ray.wallDirection == 'S') || \
	(game->ray.wallDirection == 'W'))
	{
		game->ray.curTex = (game->ray.texture->width) - \
		((game->ray.texture->width) * getDecimals(game->ray.wallX));
		return;
	}
	return ;
}

void howToCenterLine(t_game *game, double player_height)
{
	double screenY;
	uint32_t wallLineHeightHalf;

	wallLineHeightHalf = game->ray.wallLineHeight / player_height;
	screenY = game->screen_height / 2;
	game->ray.offsetFromAbove = screenY - wallLineHeightHalf;
	return;
}

void drawCurWallLine(t_game *game)
{
	uint32_t curWallLineHeight;

	curWallLineHeight = START;
	while (curWallLineHeight < game->ray.wallLineHeight)
	{
		game->ray.pixelPos.y = game->ray.offsetFromAbove + curWallLineHeight;
		if (((game->ray.offsetFromAbove + curWallLineHeight) > 0) && \
		((game->ray.offsetFromAbove + curWallLineHeight) < game->screen_height))
		{
			getTexPixelCol(	game, curWallLineHeight, \
							game->ray.wallLineHeight);
			mlx_put_pixel(	game->mlxImg, \
							game->ray.pixelPos.x, \
							game->ray.pixelPos.y, \
							game->ray.pixelColor);
		}
		curWallLineHeight++;
	}
}

double getDecimals(float f)
{
	double	integral;
	double	decimals;
	
	decimals = modf(f, &integral);
	return (decimals);
}
