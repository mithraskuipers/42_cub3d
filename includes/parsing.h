/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 18:00:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/12 22:31:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Custom libraries
# include "./../libs/libft/libft.h"
# include "./../libs/libft/ft_printf/libftprintf.h"

// Built-in libraries
# include <fcntl.h>
# include <stdio.h>

// External libraries
# include "../libs/MLX42/include/MLX42/MLX42.h"

typedef struct s_mlx
{
	char			*map_filename;
	char			**map;
	int				n_lines;
	int				len;
	int				ret;
	int				fd;
	int				error;
	int				longest_width;
	int				longest_height;
	char			**cpy_map;
	int				s_posX;
	int				s_posY;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	int				fcolor;
	int				ccolor;
	int				amount_of_lines_till_map;
	int				i;
	int				a;
}				t_mlx;

// prototypes
int			map_parse(t_mlx *mlx);
int			map_check(t_mlx *mlx);
int			returnft(t_mlx *mlx);
void		free_map(char **map, t_mlx *mlx);
int			get_longest_width(t_mlx *mlx);
int			create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
int			error_msg_ret(char *error_msg, int ret_code);

#endif
