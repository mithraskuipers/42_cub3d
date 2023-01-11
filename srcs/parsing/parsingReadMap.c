/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingReadMap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:02 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 15:04:47 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	get_map_file_dims(t_game *game, char *line)
{
	int	width;
	int	gnlretval;

	while (TRUE)
	{
		gnlretval = get_next_line(game->mapdata.mapFd, &line);
		if (gnlretval == 1)
		{
			width = ft_strlen(line);
			if (width > game->mapFileDims.x)
				game->mapFileDims.x = width;
			game->mapFileDims.y++;
			free (line);
			continue ;
		}
		else
		{
			free (line);
			break ;
		}
	}
	return (0);
}

void	map_mem_allocator(t_game *game, char ***map)
{
	int	i;
	int	j;

	i = game->whenMapMazeStart;
	j = 0;
	*map = ft_calloc((game->mapFileDims.y + 1), sizeof(char *));
	if (!*map)
		msg_err_exit("Failure while allocation memory for map.", 1);
	while (i < (game->mapFileDims.y + 1))
	{
		(*map)[j] = ft_calloc((game->mapFileDims.x + 1), sizeof(char));
		if (!(*map)[j])
			msg_err_exit("Failure while allocation memory for map.", 1);
		i++;
		j++;
	}
}

char	*return_line(char *line, t_game *game)
{
	int		gnlretval;

	gnlretval = get_next_line(game->mapdata.mapFd, &line);
	if (line == NULL || gnlretval == -1)
		msg_err_exit("Failure when running get_next_line()", 1);
	return (line);
}

void	map_read(t_game *game, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i <= (game->mapFileDims.y))
	{
		line = return_line(line, game);
		if (i >= game->whenMapMazeStart)
		{
			if (does_line_have_player(line) > -1)
			{
				game->player.x = does_line_have_player(line);
				game->player.y = i - game->whenMapMazeStart;
				game->has_player = 1;
			}
			if ((int)ft_strlen(line) > game->widthMap)
				game->widthMap = ft_strlen(line);
			ft_memcpy(game->mapdata.map[j], line, ft_strlen(line));
			ft_memcpy(game->cpy_map[j], line, ft_strlen(line));
			j++;
		}
		i++;
		free(line);
	}
}

int	does_line_have_player(char *line)
{
	if (ft_strchr(line, 'N'))
		return (ft_strchr(line, 'N') - line);
	else if (ft_strchr(line, 'E'))
		return (ft_strchr(line, 'E') - line);
	else if (ft_strchr(line, 'S'))
		return (ft_strchr(line, 'S') - line);
	else if (ft_strchr(line, 'W'))
		return (ft_strchr(line, 'W') - line);
	return (-1);
}
