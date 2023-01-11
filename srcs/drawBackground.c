/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawBackground.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:52:48 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 13:53:20 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static void	combine_colors(t_game *game)
{
	game->mapdata.ceilingColor = convert_rgb_bytes_to_int(
			game->mapdata.ceilingRGB[0], game->mapdata.ceilingRGB[1], \
				game->mapdata.ceilingRGB[2], 255);
	game->mapdata.floorColor = convert_rgb_bytes_to_int(
			game->mapdata.floorRGB[0], game->mapdata.floorRGB[1], \
				game->mapdata.floorRGB[2], 255);
}

static void	draw_img_pixel_loop(t_game *game, uint32_t Y_START,
	uint32_t Y_END, uint32_t color)
{
	uint32_t	x_pos;
	uint32_t	y_pos;

	x_pos = 0;
	while (x_pos < game->screen_width)
	{
		y_pos = Y_START;
		while (y_pos < Y_END)
		{
			mlx_put_pixel(game->mlxImg, x_pos, y_pos, color);
			y_pos++;
		}
		x_pos++;
	}
}

void	draw_background(t_game *game)
{
	combine_colors(game);
	draw_img_pixel_loop(game, 0, \
						(game->screen_height / 2), \
						game->mapdata.ceilingColor);
	draw_img_pixel_loop(game, \
						(game->screen_height / 2), \
						game->screen_height, \
						game->mapdata.floorColor);
}
