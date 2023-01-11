/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooksKeyboard.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 18:25:55 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 16:07:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	hooks_keyboard_walking(t_game *game, double move_speed)
{
	char	**map;

	map = game->mapdata.map;
	if (mlx_is_key_down(game->mlx42, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx42, MLX_KEY_UP))
		keyboard_walk_up(&game->pov.pos, &game->pov.dir, map, move_speed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx42, MLX_KEY_DOWN))
		keyboard_walk_down(&game->pov.pos, &game->pov.dir, map, move_speed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_A))
		keyboard_walk_left(&game->pov.pos, &game->dir_perp, map, move_speed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_D))
		keyboard_walk_right(&game->pov.pos, &game->dir_perp, map, move_speed);
	hooks_grow_shrink(game);
}

void	hooks_grow_shrink(t_game *game)
{
	if (mlx_is_key_down(game->mlx42, MLX_KEY_M))
	{
		if ((game->player_height * 1.1) < (int)(game->ray.wall_line_height * \
		.7))
			game->player_height = game->player_height * 1.1;
		else
			game->player_height = 2;
	}
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_N))
	{
		if ((game->player_height * 0.95) > 1)
			game->player_height = game->player_height * 0.95;
		else
			game->player_height = 2;
	}
}

void	hooks_keyboard_rotate(t_game *game, double rot_speed)
{
	double	prev_dir_x;
	double	prev_cam_plane_x;

	prev_dir_x = game->pov.dir.x;
	prev_cam_plane_x = game->pov.plane.x;
	if (mlx_is_key_down(game->mlx42, MLX_KEY_LEFT))
		keyboard_rotate_left(&game->pov, prev_dir_x, prev_cam_plane_x, \
		rot_speed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_RIGHT))
		keyboard_rotate_right(&game->pov, prev_dir_x, prev_cam_plane_x, \
		rot_speed);
}
