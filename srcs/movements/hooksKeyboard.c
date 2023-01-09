/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooksKeyboard.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 18:25:55 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/09 19:15:09 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	hooksKeyboardWalking(t_game *game, double moveSpeed)
{
	char	**map;

	map = game->mapdata.map;
	if (mlx_is_key_down(game->mlx42, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx42, MLX_KEY_UP))
		keyboardWalkUp(&game->pov.pos, &game->pov.dir, map, moveSpeed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_S)
		|| mlx_is_key_down(game->mlx42, MLX_KEY_DOWN))
		keyboardWalkDown(&game->pov.pos, &game->pov.dir, map, moveSpeed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_A))
		keyboardWalkLeft(&game->pov.pos, &game->dirPerp, map, moveSpeed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_D))
		keyboardWalkRight(&game->pov.pos, &game->dirPerp, map, moveSpeed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_M))
	{
		if ((game->player_height * 1.1) < (int)(game->ray.wallLineHeight * .7))
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

void	hooksKeyboardRotate(t_game *game, double rotSpeed)
{
	double	prevDirX;
	double	prevPlaneX;

	prevDirX = game->pov.dir.x;
	prevPlaneX = game->pov.plane.x;
	if (mlx_is_key_down(game->mlx42, MLX_KEY_LEFT))
		keyboardRotateLeft(&game->pov, prevDirX, prevPlaneX, rotSpeed);
	else if (mlx_is_key_down(game->mlx42, MLX_KEY_RIGHT))
		keyboardRotateRight(&game->pov, prevDirX, prevPlaneX, rotSpeed);
}
