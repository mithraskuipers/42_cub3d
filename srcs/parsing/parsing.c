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

int	map_check_chars(t_game *mlx, t_parse *parse)
{
	size_t	n_players;

	n_players = 0;
	mlx->map_row = 0; 															// Is deze in de mlx struct alleen om minder regels te gebruiken? Of is er nog een reden?
	while (mlx->map_row < mlx->n_rows)
	{
		mlx->map_col = 0;
		mlx->len = (int)ft_strlen(parse->map[mlx->map_row]);						// Waarom typecasting?
		while (mlx->map_col < mlx->len)
		{
			if (!ft_strrchr("01NESW ", parse->map[mlx->map_row][mlx->map_col]))
				return (error_msg_ret("Wrong characters included.", 1));
			if (ft_strrchr("NESW", parse->map[mlx->map_row][mlx->map_col]))
			{
				n_players++;
				mlx->s_posX = mlx->map_col;
				mlx->s_posY = mlx->map_row;
				mlx->player_orientation = parse->map[mlx->map_row][mlx->map_col];
			}
			mlx->map_col++;
		}
		mlx->map_row++;
	}
	if (n_players > 1)
		return (error_msg_ret("Only 1 player is allowed.", 1));
	return (0);
}

int	map_fill(t_game *mlx, char *line, t_parse *parse)
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
		if (i >= mlx->n_till_map && ft_strncmp(line, "", 1) != 0)
		{
			parse->map[mlx->map_row] = ft_calloc(1, mlx->longest_width + 1);
			if (!parse->map[mlx->map_row])
				return (1);
			parse->map[mlx->map_row] = ft_memset(parse->map[mlx->map_row], '0',
					mlx->longest_width);
			parse->map[mlx->map_row] = ft_memcpy(parse->map[mlx->map_row], line,
					ft_strlen(line));
			free (line);
			printf("%s\n", parse->map[mlx->map_row]);
			mlx->map_row++;
		}
		else
			free (line);
		i++;
	}
	close (mlx->fd);
	return (0);
}

int	map_count_rows(t_game *mlx, char *line)
{
	int	i;
	int	prev_empty;

	i = 0;
	prev_empty = 0;
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (error_msg_ret("Failed to read map.", 1));
		if (i >= mlx->n_till_map && !ft_strncmp(line, "", ft_strlen(line)))
			prev_empty = 1;
		if (i >= mlx->n_till_map && ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			if (prev_empty == 1)
			{
				free (line);
				return (error_msg_ret("Empty line in map.", 1));
			}
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
int	map_check_ext(t_game *mlx)
{
	if (!ft_strrchr(mlx->map_filename, '.') || \
	ft_strncmp(ft_strrchr(mlx->map_filename, '.'), ".cub", 5))
		return (error_msg_ret("Please provide a map with .cub extension.", 1));
	return (0);
}

int	mlx_stuff(t_parse *parse, t_game *mlx)
{
	mlx_t	*mlx42;

	mlx42 = mlx_init(5000, 3000, "42Balls", true);
	if (!mlx42)
		return (1);
	/* Do stuff */
	(void)mlx;
	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx42, 256, 256);
	if (!img || (mlx_image_to_window(mlx42, img, 0, 0) < 0))
		return (1);

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 100, 100, (unsigned int)parse->fcolor);
	
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx42);
	mlx_terminate(mlx42);
	return (0);
}

void	print_parse(t_parse *parse)
{
	// char	*NO;
	// char	*SO;
	// char	*WE;
	// char	*EA;
	// int		fcolor;
	// int		ccolor;
	// char	**map;
	// printf("%s\n", parse->map[0]);
	// printf("%s\n", parse->NO);
	// printf("%s\n", parse->SO);
	// printf("%s\n", parse->EA);
	// printf("%s\n", parse->WE);
	// printf("%d\n", parse->fcolor);
	// printf("%d\n", parse->ccolor);
	(void)parse;
}

int	map_parse(t_game *mlx, t_parse *parse)
{
	char	*line;

	mlx->ret = 1;
	mlx->n_rows = 0;
	line = NULL;
	mlx->longest_width = 0;
	init_map_variables(mlx, parse);
	if (get_variables(mlx, line, parse) == 1)
		return (1);
	if (map_check_ext(mlx) == 1)
		return (1);
	if (map_count_rows(mlx, line) == 1)
		return (1);
	parse->map = ft_calloc(1, sizeof(char *) * (mlx->n_rows + 1));
	if (!parse->map)
		return (1);
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	if (map_fill(mlx, line, parse) == 1)
		return (1);
	if (map_check_chars(mlx, parse) == 1)
		return (1);
	if (map_check (mlx, parse) == 1)
		return (1);

	// mlx_stuff(parse, mlx);
	// print_parse(parse);
	return (0);
}

