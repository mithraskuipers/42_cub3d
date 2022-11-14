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

#include "./../../includes/parsing.h"

int	map_check_chars(t_mlx *mlx)
{
	size_t	n_players;

	n_players = 0;
	mlx->map_row = 0; 															// Is deze in de mlx struct alleen om minder regels te gebruiken? Of is er nog een reden?
	while (mlx->map_row < mlx->n_rows)
	{
		mlx->map_col = 0;
		mlx->len = (int)ft_strlen(mlx->map[mlx->map_row]);						// Waarom typecasting?
		while (mlx->map_col < mlx->len)
		{
			if (!ft_strrchr("01NESW ", mlx->map[mlx->map_row][mlx->map_col]))
				return (error_msg_ret("Wrong characters included.", 1));
			if (ft_strrchr("NESW", mlx->map[mlx->map_row][mlx->map_col]))
			{
				n_players++;
				mlx->s_posX = mlx->map_col;
				mlx->s_posY = mlx->map_row;
			}
			mlx->map_col++;
		}
		mlx->map_row++;
	}
	if (n_players > 1)
		return (error_msg_ret("Only 1 player is allowed.", 1));
	return (0);
}

int	map_fill(t_mlx *mlx, char *line)
{
	int	i;

	i = 0;
	mlx->ret = 1;
	mlx->map_row = 0;
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (1);
		if (i > mlx->n_till_map - 1 && ft_strncmp(line, "", 1) != 0)
		{
			mlx->map[mlx->map_row] = ft_calloc(1, mlx->longest_width + 1);
			if (!mlx->map[mlx->map_row])
				return (1);
			mlx->map[mlx->map_row] = ft_memset(mlx->map[mlx->map_row], '0',
					mlx->longest_width);
			mlx->map[mlx->map_row] = ft_memcpy(mlx->map[mlx->map_row], line,
					ft_strlen(line));
			printf("%s\n", mlx->map[mlx->map_row]);
			free (line);
			mlx->map_row++;
		}
		else
			free (line);
		i++;
	}
	close (mlx->fd);
	return (0);
}

int	map_count_rows(t_mlx *mlx, char *line)
{
	int	i;

	i = 0;
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (error_msg_ret("Failed to read map.", 1));
		if (i > mlx->n_till_map - 1 && !ft_strncmp(line, "\n", ft_strlen(line)))
		{
			free (line);
			return (error_msg_ret("Empty line in map.", 1));
		}
		if (i > mlx->n_till_map - 1 && ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			mlx->n_rows++;
			mlx->len = (int)ft_strlen(line);
			if (mlx->len > mlx->longest_width)
				mlx->longest_width = mlx->len;
		}
		if (line)
			free (line);
		i++;
	}
	close (mlx->fd);
	return (0);
}

// map_check_ext() checks whether the file extension is ".cub".
int	map_check_ext(t_mlx *mlx)
{
	if (!ft_strrchr(mlx->map_filename, '.') || \
	ft_strncmp(ft_strrchr(mlx->map_filename, '.'), ".cub", 5))
		return (error_msg_ret("Please provide a map with .cub extension.", 1));
	return (0);
}

int	mlx_stuff(t_mlx *mlx)
{
	mlx_t	*mlx42;

	mlx42 = mlx_init(5000, 3000, "42Balls", true);
	if (!mlx42)
		return (1);
	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx42, 256, 256);
	if (!img || (mlx_image_to_window(mlx42, img, 0, 0) < 0))
		return (1);

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 100, 100, mlx->fcolor);
	
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx42);
	mlx_terminate(mlx42);
	return (0);
}

int	map_parse(t_mlx *mlx)
{
	char	*line;

	mlx->ret = 1;
	mlx->n_rows = 0;
	line = NULL;
	mlx->longest_width = 0;
	init_map_variables(mlx);
	if (get_variables(mlx, line) == 1)
		return (1);
	if (map_check_ext(mlx) == 1)
		return (1);
	if (map_count_rows(mlx, line) == 1)
		return (1);
	mlx->map = ft_calloc(1, sizeof(char *) * (mlx->n_rows + 1));
	if (!mlx->map)
		return (1);
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	if (map_fill(mlx, line) == 1)
		return (1);
	if (map_check_chars(mlx) == 1)
		return (1);
	if (map_check (mlx) == 1)
		return (1);
	mlx_stuff(mlx);
	return (0);
}
