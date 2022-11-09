
#include "../headers/parsing.h"

int	othercharacters(t_mlx *mlx)
{
	int	i;
	int	a;
	int	players_counted;

	players_counted = 0;
	i = 0;
	while (i < mlx->nr_of_lines)
	{
		a = 0;
		mlx->len = (int)ft_strlen(mlx->map[i]);
		while (a < mlx->len)
		{
			if (!ft_strrchr("01NSEW ", mlx->map[i][a]))
			{
				printf("Error\n wrong characters included");
				return (1);
			}
			if (ft_strrchr("NSEW", mlx->map[i][a]))
			{
				players_counted++;
				mlx->s_posX = a;
				mlx->s_posY = i;
			}
			a++;
		}
		i++;
	}
	if (players_counted > 1)
	{
		printf("Error\n no more than 1 player");
		return (1);
	}
	return (0);
}

//
int	fillmap(t_mlx *mlx, char *line, char *line2)
{
	mlx->ret = 1;
	int	i;

	i = 0;
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (1);
		if (line)
		{
			line2 = line;
			// line = ft_strtrim(line2, "\n");
			// if(!line)
			// 	return (1);
			// free (line);
			line = ft_strdup(line2);
			if (!line)
				return (1);
			free (line2);
			// line2 = line;
			// line = ft_strtrim(line2, "\t\n\v\f\r ");
			// if (!line)
			// 	return (returnft(mlx));
			// free (line2);
		}
		if (ft_strncmp(line, "", 1) != 0)
		{
			mlx->map[i] = ft_calloc(1, mlx->longest_width + 1);
			if (!mlx->map[i])
				return (1);
			mlx->map[i] = ft_memset(mlx->map[i], '0', mlx->longest_width);
			// line = ft_strreplace(line, ' ', '0');
			mlx->map[i] = ft_memcpy(mlx->map[i], line, ft_strlen(line));
			printf("%s\n", mlx->map[i]);
			// printf("%s\n", mlx->map[i]);
			free (line);
			i++;
		}
		else
			free (line);
	}
	close (mlx->fd);
	return (0);
}

//
int	countlines(t_mlx *mlx, char *line, char *line2)
{
	mlx->longest_width = 0;
	mlx->fd = open(mlx->map_file, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (1);
		// printf("%s\n", line);
		if(!ft_strncmp(line, "\n", ft_strlen(line)))
		{
			printf("Error\n empty line in map");
			free (line);
			return (1);
		}
		if (line)
		{
			line2 = line;
			// line = ft_strtrim(line2, "\n");
			
			// if(!line)
			// {
			// 	printf("Error\n empty line in map");
			// 	return (1);
			// }
			
			// free (line);
			line = ft_strdup(line2);
			if (!line)
				return (1);
			free (line2);
		}
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
		{
			mlx->nr_of_lines++;
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
	if (!ft_strnstr(mlx->map_file, ".cub", ft_strlen(mlx->map_file)))
	{
		printf("Error\n wrong map file format");
		return (1);
	}
	return (0);
}

int	mlx_stuff(t_mlx *mlx)
{
	mlx_t* mlx42 = mlx_init(5000, 3000, "42Balls", true);
	if (!mlx42)
		return (1);
		// ft_error();

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
	mlx->fd = open(mlx->map_file, O_RDONLY);
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
			mlx->nr_of_lines++;
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
	char	*line2;

	mlx->ret = 1;
	mlx->nr_of_lines = 0; // mk: plaats in init function
	line = NULL; 
	line2 = NULL;
	// get_variables(mlx, line, line2);
	if (map_check_ext(mlx) == 1)
		return (1);
	if (countlines(mlx, line, line2) == 1)
		return (1);
	mlx->map = ft_calloc(1, sizeof(char *) * (mlx->nr_of_lines + 1));
	if (!mlx->map)
		return (1);
	mlx->fd = open(mlx->map_file, O_RDONLY);
	if (mlx->fd == -1)
		return (1);
	
	if (fillmap(mlx, line, line2) == 1)
		return (1);
	if (othercharacters(mlx) == 1)
		return (1);
	if (checkmap (mlx) == 1)
		return (1);
	return (0);
}
