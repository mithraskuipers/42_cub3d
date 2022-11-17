/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 17:24:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/17 14:03:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PI 3.14159265

// Custom libraries
# include "./../libs/libft/libft.h"
# include "./../libs/libft/ft_printf/libftprintf.h"

// Built-in libraries
# include <fcntl.h>
# include <stdio.h>

// External libraries
# include "../libs/MLX42/include/MLX42/MLX42.h"


typedef struct s_gamedata
{
	mlx_texture_t	*textures[4];
	char		p_orientation;
	uint32_t	ceiling_rgb;
	uint32_t	floor_rgb;
}					t_gamedata;

typedef struct	s_mlx
{
	char	*map_filename;
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
	// char	*NO;
	// char	*SO;
	// char	*WE;
	// char	*EA;
	// int		fcolor;
	// int		ccolor;
	int		n_till_map;
	int		map_row;
	int		map_col;
	int		stop;
	t_gamedata	gamedata;
	char	player_orientation;
}				t_mlx;

typedef struct	s_parse
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	uint32_t		fcolor;
	uint32_t		ccolor;
	char	**map;
	float	player_direction;
}				t_parse;

// prototypes
int		map_parse(t_mlx *mlx, t_parse *parse);
int		map_check(t_mlx *mlx, t_parse *parse);
int		returnft(t_mlx *mlx);
void	map_free(char **map, t_mlx *mlx);
int		get_longest_width(t_mlx *mlx);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
int		error_msg_ret(char *error_msg, int ret_code);
void	map_free(char **map, t_mlx *mlx);
void	init_map_variables(t_mlx *mlx, t_parse *parse);
int		get_variables(t_mlx *mlx, char *line, t_parse *parse);

// TEMPORARY PROTOTYPES: DEBUG FUNCTIONS
void	debug_print_map(t_parse *parse);
void	debug_highlight_player(t_parse *parse);

#endif
