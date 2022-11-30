/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bg.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkuipers <mkuipers@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 17:34:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/29 17:34:49 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	draw_bg(t_game *game)
{
	unsigned int	i;

	i = 0;
	while (i < RES_X * RES_Y)
	{
		if (i < RES_X * (RES_Y / 2)) // upper half
			mlx_put_pixel(game->mlx_pack.image, i, 0, game->mapdata.ccolor);
		else if (i >= RES_X * (RES_Y / 2)) // lower half
			mlx_put_pixel(game->mlx_pack.image, i, 0, game->mapdata.fcolor);
		i++;
	}
	return (0);
}
