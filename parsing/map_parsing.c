
#include "../headers/parsing.h"

void	othercharacters(t_mlx *mlx)
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
			if (!ft_strrchr("01NSEW", mlx->map[i][a]))
			{
				printf("Error\n wrong characters included");
				return (returnft(mlx));
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
		return (returnft(mlx));
	}
}

void	fillmap(t_mlx *mlx, char *line, char *line2)
{
	mlx->ret = 1;
	int	i;

	i = 0;
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (returnft(mlx));
		if (line)
		{
			line2 = line;
			line = ft_strtrim(line2, "\t\n\v\f\r ");
			if (!line)
				return (returnft(mlx));
			free (line2);
		}
		if (ft_strncmp(line, "", 1) != 0)
		{
			mlx->map[i] = line;
			// printf("%s\n", mlx->map[i]);
			i++;
		}
		else
			free (line);
	}
	close (mlx->fd);
}

void	countlines(t_mlx *mlx, char *line, char *line2)
{
	mlx->fd = open(mlx->map_file, O_RDONLY);
	if (mlx->fd == -1)
		return (returnft(mlx));
	while (mlx->ret)
	{
		mlx->ret = get_next_line(mlx->fd, &line);
		if (mlx->ret == -1)
			return (returnft(mlx));
		if (line)
		{
			line2 = line;
			line = ft_strtrim(line2, "\t\n\v\f\r ");
			if (!line)
				return (returnft(mlx));
			free (line2);
		}
		if (ft_strncmp(line, "", ft_strlen(line)) != 0)
			mlx->nr_of_lines++;
		if (line)
			free (line);
	}
	printf("%d nr of lines\n", mlx->nr_of_lines);
	close (mlx->fd);
}

void	checkmapformat(t_mlx *mlx)
{
	if (!ft_strnstr(mlx->map_file, ".cub", ft_strlen(mlx->map_file)))
	{
		printf("Error\n wrong map file format");
		return (returnft(mlx));
	}
}

void	mapparsing(t_mlx *mlx)
{
	char	*line;
	char	*line2;

	mlx->ret = 1;
	mlx->nr_of_lines = 0;
	line = NULL;
	line2 = NULL;
	checkmapformat(mlx);
	countlines(mlx, line, line2);
	mlx->map = ft_calloc(1, sizeof(char *) * (mlx->nr_of_lines + 1));
	if (!mlx->map)
		return (returnft(mlx));
	mlx->fd = open(mlx->map_file, O_RDONLY);
	if (mlx->fd == -1)
		return (returnft(mlx));
	fillmap(mlx, line, line2);
	othercharacters(mlx);
	if (mlx->error == 1)
		return ;
	checkmap (mlx);
}
