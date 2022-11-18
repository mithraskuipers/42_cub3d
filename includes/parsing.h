/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 17:24:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/18 08:57:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PI 3.14159265359
# define RES_X	480
# define RES_Y	320

// Custom libraries
# include "./../libs/libft/libft.h"
# include "./../libs/libft/ft_printf/libftprintf.h"

// Built-in libraries
# include <fcntl.h>
# include <stdio.h>

// External libraries
# include "../libs/MLX42/include/MLX42/MLX42.h"

/******************************************************************************/
/* STRUCTS                                                                    */
/******************************************************************************/

typedef struct s_gamedata
{
	mlx_texture_t	*textures[4];
	char		p_orientation;
	uint32_t	ceiling_rgb;
	uint32_t	floor_rgb;
}					t_gamedata;

typedef struct	s_mlx
{
	mlx_t			*mlx_ins;
	mlx_image_t		*mlx_img;
	mlx_texture_t	*assets[4];
}				t_mlxs;

typedef struct	s_game
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

}				t_game;

typedef struct	s_parse
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	uint32_t	fcolor;
	uint32_t	ccolor;
	char		**map;
	float		player_direction;
}				t_parse;

/******************************************************************************/
/* PROTOTYPES                                                                 */
/******************************************************************************/

// [PARSING]: CHECKERS.C
int	map_floodfill(int x, int y, t_game *mlx);
int	map_copy(t_game *mlx, t_parse *parse);
int	map_check(t_game *mlx, t_parse *parse);

// [PARSING]: PARSING.C
int	map_check_chars(t_game *mlx, t_parse *parse);
int	map_fill(t_game *mlx, char *line, t_parse *parse);
int	map_count_rows(t_game *mlx, char *line);
int	map_check_ext(t_game *mlx);
int	mlx_stuff(t_parse *parse, t_game *mlx);

// [PARSING]: UTILS.C
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);

// [PARSING]: VARIABLES.C
void	free_split(char **split, bool skip, int index);
int		free_all_and_error(char	**split_line, char *str);
int		get_colors(char	**split_line, t_parse *parse);
int		get_other_cases(char **split_line, t_parse *parse, t_game *mlx);
int		get_one_variable(t_game *mlx, char *line, t_parse *parse);
int		loop_through_lines(t_game *mlx, char *line, t_parse *parse);
int		get_variables(t_game *mlx, char *line, t_parse *parse);
void	init_map_variables(t_game *mlx, t_parse *parse);
void	print_parse(t_parse *parse);
int		map_parse(t_game *mlx, t_parse *parse);


// [TOOLS]: ERROR.C
int		error_msg_ret(char *error_msg, int ret_code);

// [DEBUG]: MISC.C
void	debug_print_map(t_parse *parse);
void	debug_highlight_player(t_parse *parse);

// [MATH]: CONVERSIONS.C
float	radians_to_degrees(float radians);
float	degrees_to_radians(float degrees);

// [FREE]: MISC.C
void	map_free(char **map, t_game *mlx);

#endif
