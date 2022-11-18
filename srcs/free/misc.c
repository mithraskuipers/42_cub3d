/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 17:22:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/18 08:56:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parsing.h"

// map_free()
// Frees  the char **map stored in the mlx struct.
void	map_free(char **map, t_game *mlx)
{
	mlx->map_row = 0;
	while (mlx->map_row < mlx->n_rows)
	{
		free (map[mlx->map_row]);
		mlx->map_row++;
	}
	free(map);
}
