#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libft/ft_printf/libftprintf.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_mlx
{
	char			*map_file;
	char			**map;
	int				nr_of_lines;
	int				len;
	int				ret;
	int				fd;
	int				error;
	int				longest_width;
	int				longest_height;
	char			**cpy_map;
}				t_mlx;

void	mapparsing(t_mlx *mlx);
void	checkmap(t_mlx *mlx);
void	returnft(t_mlx *mlx);
void	free_map(char **map, t_mlx *mlx);

#endif