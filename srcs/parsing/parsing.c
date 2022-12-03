/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 13:02:20 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/13 17:20:59 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	map_check_chars(t_game *game, t_mapdata *mapdata)
{
	size_t	n_players;

	n_players = 0;
	game->map_row = 0; 															// Is deze in de game struct alleen om minder regels te gebruiken? Of is er nog een reden?
	while (game->map_row < game->n_rows)
	{
		game->map_col = 0;
		game->len = (int)ft_strlen(mapdata->map[game->map_row]);						// Waarom typecasting?
		while (game->map_col < game->len)
		{
			if (!ft_strrchr("01NESW ", mapdata->map[game->map_row][game->map_col]))
				return (error_msg_ret("Wrong characters included.", 1));
			if (ft_strrchr("NESW", mapdata->map[game->map_row][game->map_col]))
			{
				n_players++;
				game->playerSpawnX = game->map_col;
				game->playerSpawnY = game->map_row;
				game->mapdata.spawn_cardinaldir = mapdata->map[game->map_row][game->map_col];
			}
			game->map_col++;
		}
		game->map_row++;
	}
	if (n_players > 1)
		return (error_msg_ret("Only 1 player is allowed.", 1));
	return (0);
}

int	map_fill(t_game *game, char *line, t_mapdata *mapdata)
{
	int	i;

	i = 0;
	game->gnl_ret = 1;
	game->map_row = 0;
	while (game->gnl_ret)
	{
		game->gnl_ret = get_next_line(game->fd, &line);
		if (game->gnl_ret == -1)
			return (1);
		if (i >= game->n_till_map && ft_strncmp(line, "", 1) != 0)
		{
			mapdata->map[game->map_row] = ft_calloc(1, game->map_widest + 1);
			if (!mapdata->map[game->map_row])
				return (1);
			mapdata->map[game->map_row] = ft_memset(mapdata->map[game->map_row], '0',
					game->map_widest);
			mapdata->map[game->map_row] = ft_memcpy(mapdata->map[game->map_row], line,
					ft_strlen(line));
			free (line);
			game->map_row++;
		}
		else
			free (line);
		i++;
	}
	close (game->fd);
	return (0);
}

int	map_count_rows(t_game *game, char *line)
{
	int	i;
	int	prev_empty;

	i = 0;
	prev_empty = 0;
	game->fd = open(game->map_filename, O_RDONLY);
	if (game->fd == -1)
		return (1);
	while (game->gnl_ret)
	{
		game->gnl_ret = get_next_line(game->fd, &line);
		if (game->gnl_ret == -1)
			return (error_msg_ret("Failed to read map.", 1));
		if (i >= game->n_till_map && !ft_strncmp(line, "", ft_strlen(line)))
			prev_empty = 1;
		if (i >= game->n_till_map && ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			if (prev_empty == 1)
			{
				free (line);
				return (error_msg_ret("Empty line in map.", 1));
			}
			game->n_rows++;
			game->len = (int)ft_strlen(line);
			if (game->len > game->map_widest)
				game->map_widest = game->len;
		}
		if (line)
			free (line);
		i++;
	}
	close (game->fd);
	return (0);
}

// map_check_ext() checks whether the file extension is ".cub".
int	map_check_ext(t_game *game)
{
	if (!ft_strrchr(game->map_filename, '.') || \
	ft_strncmp(ft_strrchr(game->map_filename, '.'), ".cub", 5))
		return (error_msg_ret("Please provide a map with .cub extension.", 1));
	return (0);
}

int	mlx_stuff(t_mapdata *mapdata, t_game *game)
{
	mlx_t	*mlx42;

	mlx42 = mlx_init(5000, 3000, "42Balls", true);
	if (!mlx42)
		return (1);
	/* Do stuff */
	(void)game;
	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx42, 256, 256);
	if (!img || (mlx_image_to_window(mlx42, img, 0, 0) < 0))
		return (1);

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 100, 100, (unsigned int)mapdata->fcolor);
	
	// Register a hook and pass game as an optional param.
	// NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(game, ft_hook, game);
	mlx_loop(mlx42);
	mlx_terminate(mlx42);
	return (0);
}

int	map_parse(t_game *game, t_mapdata *mapdata)
{
	char	*line;

	game->gnl_ret = 1;
	game->n_rows = 0;
	line = NULL;
	game->map_widest = 0;
	init_map_variables(game, mapdata);
	if (get_variables(game, line, mapdata) == 1)
		return (1);
	if (map_check_ext(game) == 1)
		return (1);
	if (map_count_rows(game, line) == 1)
		return (1);
	mapdata->map = ft_calloc(1, sizeof(char *) * (game->n_rows + 1));
	if (!mapdata->map)
		return (1);
	game->fd = open(game->map_filename, O_RDONLY);
	if (game->fd == -1)
		return (1);
	if (map_fill(game, line, mapdata) == 1)
		return (1);
	if (map_check_chars(game, mapdata) == 1)
		return (1);
	if (map_check (game, mapdata) == 1)
		return (1);

	// mlx_stuff(mapdata, game);
	// print_parse(mapdata);
	return (0);
}

