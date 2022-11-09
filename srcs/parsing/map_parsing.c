/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_parsing.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 13:02:20 by dkramer       #+#    #+#                 */
/*   Updated: 2022/11/09 13:23:01 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/parsing.h"

int	othercharacters(t_mlx *mlx)
{
	int	players_counted;

	players_counted = 0;
	mlx->i = 0;
	while (mlx->i < mlx->n_lines)
	{
		mlx->a = 0;
		mlx->len = (int)ft_strlen(mlx->map[mlx->i]);
		while (mlx->a < mlx->len)
		{
			if (!ft_strrchr("01NSEW ", mlx->map[mlx->i][mlx->a]))
				return (error_msg_ret("Wrong characters included.", 1));
			if (ft_strrchr("NSEW", mlx->map[mlx->i][mlx->a]))
			{
				players_counted++;
				mlx->s_posX = mlx->a;
				mlx->s_posY = mlx->i;
			}
			mlx->a++;
		}
		mlx->i++;
	}
	if (players_counted > 1)
		return (error_msg_ret("No more than 1 player.", 1));
	return (0);
}

// TODO
int	map_fill(t_mlx *mlx, char *line)
{
	mlx->ret = 1;
	mlx->i = 0;
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (1);
		if (ft_strncmp(line, "", 1) != 0)
		{
			mlx->map[mlx->i] = ft_calloc(1, mlx->longest_width + 1);
			if (!mlx->map[mlx->i])
				return (1);
			mlx->map[mlx->i] = ft_memset(mlx->map[mlx->i], '0',
					mlx->longest_width);
			mlx->map[mlx->i] = ft_memcpy(mlx->map[mlx->i], line,
					ft_strlen(line));
			free (line);
			mlx->i++;
		}
		else
			free (line);
	}
	close (mlx->fd);
	return (0);
}

// TODO
int	countlines(t_mlx *mlx, char *line)
{
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (1);
		if (!ft_strncmp(line, "\n", ft_strlen(line)))
		{
			free (line);
			return (error_msg_ret("Empty line in map.", 1));
		}
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			mlx->n_lines++;
			mlx->len = (int)ft_strlen(line);
			if (mlx->len > mlx->longest_width)
				mlx->longest_width = mlx->len;
		}
		if (line)
			free (line);
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

int	get_variables(t_mlx *mlx, char *line, char *line2)
{
	// (void)mlx;
	// 220,100,0
	// mlx->fcolor = get_rgba(255, 255, 255);
	mlx->amount_of_lines_till_map = 0;
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (1);
		if (line)
		{
			line2 = line;
			line = ft_strtrim(line2, "\t\n\v\f\r ");
			if (!line)
				return (1);
			free (line2);
		}
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			mlx->n_lines++;
			mlx->len = (int)ft_strlen(line);
			if (mlx->len > mlx->longest_width)
				mlx->longest_width = mlx->len;
		}
		if (line)
			free (line);
		mlx->amount_of_lines_till_map++;
	}
	close (mlx->fd);
	mlx->fcolor = create_trgb(255, 255, 255, 255);
	printf("%ud\n", mlx->fcolor);
	return (0);
	// mlx_stuff(mlx);
	
// 	NO ./path_to_the_north_texture
// SO ./path_to_the_south_texture
// WE ./path_to_the_west_texture
// EA ./path_to_the_east_texture
// F 220,100,0
// C 225,30,0
	
}

int	map_parse(t_mlx *mlx)
{
	char	*line;

	mlx->ret = 1;
	mlx->n_lines = 0; // mk: plaats in init function
	line = NULL;
	mlx->longest_width = 0;
	// get_variables(mlx, line, line2);
	if (map_check_ext(mlx) == 1)
		return (1);
	if (countlines(mlx, line) == 1)
		return (1);
	mlx->map = ft_calloc(1, sizeof(char *) * (mlx->n_lines + 1));
	if (!mlx->map)
		return (1);
	mlx->fd = open(mlx->map_filename, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	if (map_fill(mlx, line) == 1)
		return (1);
	if (othercharacters(mlx) == 1)
		return (1);
	if (checkmap (mlx) == 1)
		return (1);
	return (0);
}
