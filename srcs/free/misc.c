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

#include "./../../includes/cub3d.h"

// map_free()
// Frees  the char **map stored in the game struct.
void	map_free(char **map, t_game *game)
{
	game->map_row = 0;
	while (game->map_row < game->n_rows)
	{
		free (map[game->map_row]);
		game->map_row++;
	}
	free(map);
}
