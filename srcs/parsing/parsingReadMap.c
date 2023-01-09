/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingReadMap.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:02 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/09 11:00:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	getMapFileDims(t_game *game, char *line)
{
	int	width;
	int gnlretval;
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
			continue;
		}
		else
		{
			free (line);
			break;
		}
	}
	if (game->mapFileDims.x < 3 || game->mapFileDims.y < 3)
		msgErrExit("Invalid map.", 1);
	return (0);
}

void	mapMemAllocator(t_game *game, char ***map)
{
	int	i;
	int j;

	i = game->whenMapMazeStart;
	j = 0;
	*map = ft_calloc((game->mapFileDims.y + 1), sizeof(char *));
	if (!*map)
		msgErrExit("Failure while allocation memory for map.", 1);
	while (i < (game->mapFileDims.y + 1))
	{
		(*map)[j] = ft_calloc((game->mapFileDims.x + 1), sizeof(char));
		if (!(*map)[j])
			msgErrExit("Failure while allocation memory for map.", 1);
		i++;
		j++;
	}
}

void	mapRead(t_game *game)
{
	int		i;
	char	*line;
	int 	gnlretval;
	int 	j;

	i = 0;
	j = 0;
	while (i <= (game->mapFileDims.y))
	{
		gnlretval = get_next_line(game->mapdata.mapFd, &line);
		if (line == NULL || gnlretval == -1)
			msgErrExit("Failure when running get_next_line()", 1);
		if (i < game->whenMapMazeStart)
		{
			i++;
			free(line);
			continue;
		}
		if (doesLineHavePlayer(line) > 0)
		{
			game->player.x = doesLineHavePlayer(line);
			game->player.y = i - game->whenMapMazeStart;
			game->has_player = 1;
		}
		ft_memcpy(game->mapdata.map[j], line, ft_strlen(line));
		ft_memcpy(game->cpy_map[j], line, ft_strlen(line));
		free(line);
		i++;
		j++;
	}
	if (game->has_player == 0)
		msgErrExit("Your map contains no player spawning point.", 1);
}

int	doesLineHavePlayer(char *line)
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
