#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libft/ft_printf/libftprintf.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_wall
{
	int		width;
	int		height;
	void	*mlx;
	char	*window;
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}				t_wall;

typedef struct s_mlx
{
	char			*map_file;
	char			**map;
	int				nr_of_lines;
	int				len;
	int				width;
	int				height;
	void			*mlx;
	char			*window;
	void			*image;
	char			*address;
	int				bits_per_pixel;
	int				line_size;
	int				endian;
	t_wall			wall;
	t_wall			collectible;
	t_wall			exit;
	t_wall			player;
	int				counter;
	int				offset;
	int				offset2;
	unsigned int	trgbcolor;
	int				x;
	int				y;
	int				i;
	int				a;
	t_wall			needed;
	int				exit_found;
	int				collectible_found;
	int				start_found;
	int				b;
	int				ret;
	int				fd;
	t_wall			wall1;
	int				error;
	int				breaky;
	int				coll;
	int				taken;
}				t_mlx;

void	mapparsing(t_mlx *mlx);
void	checkmap(t_mlx *mlx);
void	returnft(t_mlx *mlx);

#endif