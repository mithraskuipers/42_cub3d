/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkuipers <mkuipers@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 17:22:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/12/03 11:19:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

// map_free()
// Frees  the char **map stored in the game struct.
void	map_free(char **map, t_game *game)
{
	game->map_row_tmp = 0;
	while (game->map_row_tmp < game->n_rows)
	{
		free (map[game->map_row_tmp]);
		game->map_row_tmp++;
	}
	free(map);
}
