/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:05:02 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/12/21 22:05:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	printMap(t_game *game)
{
	int i;
	char **map;

	i = 0;
	map = game->mapdata.map;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	printMapCopy(t_game *game)
{
	int i;
	char **map;

	i = 0;
	map = game->cpy_map;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}


void	printPlayerPos(t_game *game)
{
	printf("game->player.x: %d\n", game->player.x);
	printf("game->player.y: %d\n", game->player.y);
}
