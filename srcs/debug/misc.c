/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 22:33:51 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/13 17:25:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parsing.h"

#include <stdio.h>

static void	color_red()
{
	printf("\033[0;31m");
}

static void	color_orange()
{
	printf("\033[38;5;214m");
}

// static void	color_green()
// {
// 	printf("\033[0;32m");
// }

static void	color_reset()
{
	printf("\033[0m");
}

void	debug_print_map(t_mlx *mlx)
{
	size_t	i;
	size_t	j;
	char	**map;

	i = 0;
	map = mlx->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!map[i][j+1])
			{
				printf("\n");
				break ;
			}
			printf("%c", map[i][j]);
			j++;
		}
		i++;
	}
}

static int cell_is_player(char c)
{
	if ((c == 'N') || (c == 'E') || (c == 'S') || (c == 'W'))
		return (1);
	return (0);
}

void	debug_highlight_player(t_mlx *mlx)
{
	size_t	i;
	size_t	j;
	int		player_found;
	char	**map;

	i = 0;
	map = mlx->map;
	player_found = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (cell_is_player(map[i][j]))
			{
				player_found = 1;
				color_red();
				printf("%c", map[i][j]);
				color_reset();
			}
			if (!map[i][j+1])
			{
				if (player_found)
				{
					player_found = 0;
					color_orange();
					printf(" <-------- PLAYER");
					color_reset();
				}
				printf("\n");
				break ;
			}
			printf("%c", map[i][j]);
			j++;
		}
		i++;
	}
}
