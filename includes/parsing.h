/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 17:24:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/14 13:59:57 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// Custom libraries
# include "./../libs/libft/libft.h"
# include "./../libs/libft/ft_printf/libftprintf.h"

// Built-in libraries
# include <fcntl.h>
# include <stdio.h>

// External libraries
# include "../libs/MLX42/include/MLX42/MLX42.h"

typedef struct	s_mlx
{
	char	*map_filename;
	char	**map;
	int		n_rows;
	int		len;
	int		ret;
	int		fd;
	int		error;
	int		longest_width;
	int		longest_height;
	char	**cpy_map;
	int		s_posX;
	int		s_posY;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		fcolor;
	int		ccolor;
	int		n_till_map;
	int		map_row;
	int		map_col;
}				t_mlx;

// prototypes
int		map_parse(t_mlx *mlx);
int		map_check(t_mlx *mlx);
int		returnft(t_mlx *mlx);
void	map_free(char **map, t_mlx *mlx);
int		get_longest_width(t_mlx *mlx);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
int		error_msg_ret(char *error_msg, int ret_code);
void	map_free(char **map, t_mlx *mlx);
void	init_map_variables(t_mlx *mlx);
int		get_variables(t_mlx *mlx, char *line);

// TEMPORARY PROTOTYPES: DEBUG FUNCTIONS
void	debug_print_map(t_mlx *mlx);
void	debug_highlight_player(t_mlx *mlx);

#endif
