/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawBackground.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 13:52:48 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 16:35:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

static void	combine_colors(t_game *game)
{
	game->mapdata.ceiling_color = convert_rgb_bytes_to_int(
			game->mapdata.ceiling_rgb[0], game->mapdata.ceiling_rgb[1], \
				game->mapdata.ceiling_rgb[2], 255);
	game->mapdata.floor_color = convert_rgb_bytes_to_int(
			game->mapdata.floor_rgb[0], game->mapdata.floor_rgb[1], \
				game->mapdata.floor_rgb[2], 255);
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
			mlx_put_pixel(game->mlx_img, x_pos, y_pos, color);
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
						game->mapdata.ceiling_color);
	draw_img_pixel_loop(game, \
						(game->screen_height / 2), \
						game->screen_height, \
						game->mapdata.floor_color);
}
