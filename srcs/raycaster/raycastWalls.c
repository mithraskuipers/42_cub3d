/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastWalls.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/09 18:53:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/**
 * Base object for disk loaded textures.
 * It contains rudementary information about the texture.
 *
 * @param width The width of the texture.
 * @param height The height of the texture.
 * @param pixels The literal pixel data.
 * @param bytes_per_pixel The amounst of bytes in a pixel, always 4.
 */

/*
getTexPixelColor() simply extract
...

first it calculates the total number of pixels in the texture of interest.
multiplies that with a scale???? then by 4 because 4 bytes per pixel.
*/

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
	game->ray.pixelColor = getRGBA(	game->ray.texture->pixels[exactTexPixel], \
									R, \
									G, \
									B);
	return;
}

void setCurrentRayTexture(t_game *game)
{
	if ((game->ray.wallDirection == 'S') || (game->ray.wallDirection == 'E'))
	{
		game->ray.curTex = game->ray.texture->width * fabs(1 - ft_fmod(game->ray.wallX));
		return;
	}
	else if ((game->ray.wallDirection == 'N') || (game->ray.wallDirection == 'W'))
	{
		game->ray.curTex = game->ray.texture->width * fabs(ft_fmod(game->ray.wallX));
		return;
	}
}

void howToCenterLine(t_game *game)
{
	double screenY;
	uint32_t wallLineHeightHalf;

	wallLineHeightHalf = game->ray.wallLineHeight / 10; // divide by bigger number to give illusion of beging giant
	screenY = game->screen_height / 2; //original, keep
	// screenY = game->textures[0]->height / 2; // works, interesting? TODO INSPECT!
	game->ray.offsetFromAbove = screenY - wallLineHeightHalf;
	return;
}

void drawCurWallLine(t_game *game)
{
	u_int32_t curWallLineHeight;

	curWallLineHeight = START;
	while (curWallLineHeight < game->ray.wallLineHeight)
	{
		game->ray.pixelPos.y = game->ray.offsetFromAbove + curWallLineHeight;
		if (((game->ray.offsetFromAbove + curWallLineHeight) > 0) && ((game->ray.offsetFromAbove + curWallLineHeight) < game->screen_height))
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
