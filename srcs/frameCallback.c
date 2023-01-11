/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frameCallback.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 15:40:36 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 15:40:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

/*
update_game_cfg() updates the game movement speed and rotation speed. 
delta_time (autom. determined by the MLX library) is the time difference between
the previous frame and the current frame.
*/

static void	update_game_cfg(t_game *game)
{
	game->movement_speed = game->mlx42->delta_time * MOVE_SPEED;
	game->rotation_speed = game->mlx42->delta_time * ROT_SPEED;
	game->dir_perp.x = game->pov.dir.y * -1;
	game->dir_perp.y = game->pov.dir.x;
}

void hooks_input(t_game *game)
{
	hooks_keyboard_walking(game, game->movement_speed);
	hooks_keyboard_rotate(game, game->rotation_speed);
}

/*
check_mlx_win_resize() simp
*/

void	check_mlx_win_resize(mlx_t *mlx, t_game *game)
{
	if (game->screen_width != (uint32_t)mlx->width || game->screen_height != \
	(uint32_t)mlx->height)
	{
		game->screen_width = mlx->width;
		game->screen_height = mlx->height;
		mlx_resize_image(game->mlxImg, game->screen_width, game->screen_height);
	}
}

void	frame_callback(void *arg)
{
	t_game	*game;

	game = arg;
	mlx_delete_image(game->mlx42, game->mlxImg);
	game->mlxImg = mlx_new_image(game->mlx42, game->screen_width, \
	game->screen_height);
	update_game_cfg(game);
	hooks_input(game);
	check_mlx_win_resize(game->mlx42, game);
	raycaster(game, &game->pov);
	mlx_image_to_window(game->mlx42, game->mlxImg, 0, 0);
	if (mlx_is_key_down(game->mlx42, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx42);
}
