/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   frame_callback.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:05:14 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 09:38:59 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

/*
updateGameCfg() updates the game movement speed and rotation speed. 
delta_time (autom. determined by the MLX library) is the time difference between
the previous frame and the current frame.
*/

static void	updateGameCfg(t_game *game)
{
	game->movementSpeed = game->mlx42->delta_time * MOVE_SPEED;
	game->rotationSpeed = game->mlx42->delta_time * ROT_SPEED;
	game->dirPerp.x = game->pov.dir.y * -1;
	game->dirPerp.y = game->pov.dir.x;
}

void hooksInput(t_game *game)
{
	hooksKeyboardWalking(game, game->movementSpeed);
	hooksKeyboardRotate(game, game->rotationSpeed);
}

/*
checkMlxWindowResize() simp
*/

void	checkMlxWindowResize(mlx_t *mlx, t_game *game)
{
	if (game->screen_width != (uint32_t)mlx->width || game->screen_height != (uint32_t)mlx->height)
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
	game->mlxImg = mlx_new_image(game->mlx42, game->screen_width, game->screen_height);
	updateGameCfg(game);
	hooksInput(game);
	checkMlxWindowResize(game->mlx42, game);
	raycaster(game, &game->pov);
	mlx_image_to_window(game->mlx42, game->mlxImg, 0, 0);
	if (mlx_is_key_down(game->mlx42, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx42);
}
