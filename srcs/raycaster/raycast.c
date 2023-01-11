/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:06:04 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 16:33:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

static void	how_tall_wall_line(t_ray *ray)
{
	ray->tex_line_scale = (1 / (ray->perp_wall_distance) * .666);
}

static int	which_tex_has_wall(t_game *game, char wall_direction)
{
	if (wall_direction == 'N')
		game->ray.texture = game->textures[NORTH];
	else if (wall_direction == 'E')
		game->ray.texture = game->textures[EAST];
	else if (wall_direction == 'S')
		game->ray.texture = game->textures[SOUTH];
	else if (wall_direction == 'W')
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
		comp_camera_space_x(game, pov, game->ray.screen_x_pos);
		comp_ray_dir(&game->ray, pov);
		comp_ray_map(&game->ray, pov);
		comp_delta_dist(&game->ray);
		set_step(&game->ray);
		init_side_dist(&game->ray, pov);
		comp_side_dist(&game->ray, game->mapdata.map);
		comp_perp_wall_dist(&game->ray);
		which_wall_was_hit1(game);
		which_wall_was_hit2(game);
		which_tex_has_wall(game, game->ray.wall_direction);
		where_was_wall_hit(&game->ray, pov);
		how_tall_wall_line(&game->ray);
		game->ray.pixel_pos.x = game->ray.screen_x_pos;
		set_current_ray_texture(game);
		game->ray.wall_line_height = (game->ray.texture->height * \
		game->ray.tex_line_scale);
		how_to_center_line(game, game->player_height);
		draw_cur_wall_line(game);
		game->ray.screen_x_pos++;
	}
}
