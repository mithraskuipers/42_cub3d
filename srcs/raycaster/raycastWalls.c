/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycastWalls.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 14:47:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	get_tex_pixel_col(t_game *game, int wall_height, int wall_line_height)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	size_t	exact_tex_pixel;

	exact_tex_pixel = ((size_t)(((double)wall_height / \
	(double)wall_line_height) \
	* (int)game->ray.texture->height) \
	* (int)(game->ray.texture->width) \
	+ (int)game->ray.curTex) \
	* 4;
	r = game->ray.texture->pixels[exact_tex_pixel + 1];
	g = game->ray.texture->pixels[exact_tex_pixel + 2];
	b = game->ray.texture->pixels[exact_tex_pixel + 3];
	game->ray.pixelColor = convert_rgb_bytes_to_int(\
									game->ray.texture->pixels[exact_tex_pixel], \
									r, \
									g, \
									b);
	return ;
}

void	set_current_ray_texture(t_game *game)
{
	if ((game->ray.wall_direction == 'N') || \
	(game->ray.wall_direction == 'E'))
	{
		game->ray.curTex = (game->ray.texture->width) * \
		get_decimals(game->ray.wall_x);
	}
	else if ((game->ray.wall_direction == 'S') || \
	(game->ray.wall_direction == 'W'))
	{
		game->ray.curTex = (game->ray.texture->width) - \
		((game->ray.texture->width) * get_decimals(game->ray.wall_x));
	}
}

void	how_to_center_line(t_game *game, double player_height)
{
	double		screen_y;
	uint32_t	wall_line_height_half;

	wall_line_height_half = game->ray.wall_line_height / player_height;
	screen_y = game->screen_height / 2;
	game->ray.offset_from_above = screen_y - wall_line_height_half;
}

void	draw_cur_wall_line(t_game *game)
{
	uint32_t	curwall_line_height;

	curwall_line_height = START;
	while (curwall_line_height < game->ray.wall_line_height)
	{
		game->ray.pixelPos.y = game->ray.offset_from_above \
		+ curwall_line_height;
		if (((game->ray.offset_from_above + curwall_line_height) > 0) && \
		((game->ray.offset_from_above + curwall_line_height) < \
		game->screen_height))
		{
			get_tex_pixel_col(game, curwall_line_height, \
							game->ray.wall_line_height);
			mlx_put_pixel(game->mlxImg, \
							game->ray.pixelPos.x, \
							game->ray.pixelPos.y, \
							game->ray.pixelColor);
		}
		curwall_line_height++;
	}
}

double	get_decimals(float f)
{
	double	integral;
	double	decimals;

	decimals = modf(f, &integral);
	return (decimals);
}
