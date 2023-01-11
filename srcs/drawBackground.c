/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawBackground.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:05:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 11:45:01 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static void	combineColors(t_game *game)
{
	game->mapdata.ceilingColor = convert_rgb_bytes_to_int(	game->mapdata.ceilingRGB[0], \
											game->mapdata.ceilingRGB[1], \
											game->mapdata.ceilingRGB[2], \
											255);
	game->mapdata.floorColor = convert_rgb_bytes_to_int(		game->mapdata.floorRGB[0], \
											game->mapdata.floorRGB[1], \
											game->mapdata.floorRGB[2], \
											255);
}

static void	drawImgPixelLoop(t_game *game, uint32_t Y_START, uint32_t Y_END, uint32_t color)
{
	uint32_t	X_POS;
	uint32_t	Y_POS;

	X_POS = 0;
	while (X_POS < game->screen_width)
	{
		Y_POS = Y_START;
		while (Y_POS < Y_END)
		{
			mlx_put_pixel(game->mlxImg, X_POS, Y_POS, color);
			Y_POS++;
		}
		X_POS++;
	}
}

void	drawBackground(t_game *game)
{
	combineColors(game);
	drawImgPixelLoop(	game, \
						0, \
						(game->screen_height / 2), \
						game->mapdata.ceilingColor);
	drawImgPixelLoop(	game, \
						(game->screen_height / 2), \
						game->screen_height, \
						game->mapdata.floorColor);
}
