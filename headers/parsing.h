#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libft/ft_printf/libftprintf.h"
# include <fcntl.h>
# include <stdio.h>
#include "../MLX42/include/MLX42/MLX42.h"

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
	int				s_posX;
	int				s_posY;
		// NO ./path_to_the_north_texture
// SO ./path_to_the_south_texture
// WE ./path_to_the_west_texture
// EA ./path_to_the_east_texture
// F 220,100,0
// C 225,30,0
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	int				fcolor;
	int				ccolor;
	int				amount_of_lines_till_map;
	// int
}				t_mlx;

void	map_parse(t_mlx *mlx);
void	checkmap(t_mlx *mlx);
void	returnft(t_mlx *mlx);
void	free_map(char **map, t_mlx *mlx);
void	get_longest_width(t_mlx *mlx);
unsigned int		get_rgba(int r, int g, int b);
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);

#endif