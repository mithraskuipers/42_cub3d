/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastWalls.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 14:56:47 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void getTexPixelCol(t_game *game, int wallHeight, int wall_line_height)
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	size_t exactTexPixel;

	exactTexPixel = ((size_t)(((double)wallHeight / (double)wall_line_height) *
					(int)game->ray.texture->height) *
					(int)(game->ray.texture->width) +
					(int)game->ray.cur_tex) *
					4;
	R = game->ray.texture->pixels[exactTexPixel + 1];
	G = game->ray.texture->pixels[exactTexPixel + 2];
	B = game->ray.texture->pixels[exactTexPixel + 3];
	game->ray.pixel_color = convert_rgb_bytes_to_int(\
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
		game->ray.cur_tex = (game->ray.texture->width) * \
		getDecimals(game->ray.wallX);
		return;
	}
	else if ((game->ray.wallDirection == 'S') || \
	(game->ray.wallDirection == 'W'))
	{
		game->ray.cur_tex = (game->ray.texture->width) - \
		((game->ray.texture->width) * getDecimals(game->ray.wallX));
		return;
	}
	return ;
}

void howToCenterLine(t_game *game, double player_height)
{
	double screenY;
	uint32_t wall_line_heightHalf;

	wall_line_heightHalf = game->ray.wall_line_height / player_height;
	screenY = game->screen_height / 2;
	game->ray.offset_from_above = screenY - wall_line_heightHalf;
	return;
}

void drawCurWallLine(t_game *game)
{
	uint32_t curwall_line_height;

	curwall_line_height = START;
	while (curwall_line_height < game->ray.wall_line_height)
	{
		game->ray.pixel_pos.y = game->ray.offset_from_above + curwall_line_height;
		if (((game->ray.offset_from_above + curwall_line_height) > 0) && \
		((game->ray.offset_from_above + curwall_line_height) < game->screen_height))
		{
			getTexPixelCol(	game, curwall_line_height, \
							game->ray.wall_line_height);
			mlx_put_pixel(	game->mlxImg, \
							game->ray.pixel_pos.x, \
							game->ray.pixel_pos.y, \
							game->ray.pixel_color);
		}
		curwall_line_height++;
	}
}

double getDecimals(float f)
{
	double	integral;
	double	decimals;
	
	decimals = modf(f, &integral);
	return (decimals);
}
