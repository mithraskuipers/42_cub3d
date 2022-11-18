/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 17:24:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/18 08:57:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/

# define PI 3.14159265359
# define RES_X	480
# define RES_Y	320

/******************************************************************************/
/* INCLUDES                                                                   */
/******************************************************************************/

// External libraries
# include "../libs/MLX42/include/MLX42/MLX42.h"

// Custom libraries
# include "./../libs/libft/libft.h"
# include "./../libs/libft/ft_printf/libftprintf.h"

// Built-in libraries
# include <fcntl.h>
# include <stdio.h>

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

typedef struct	s_mapdata
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	uint32_t	fcolor;
	uint32_t	ccolor;
	char		**map;
	float		player_direction;
}				t_mapdata;

typedef struct	s_mlx
{
	mlx_t			*mlx_instance;
	mlx_image_t		*mlx_image;
	mlx_texture_t	*assets[4];
}				t_mlxs;

typedef struct	s_game
{
	t_gamedata	gamedata;
	t_mapdata	mapdata;
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
	int		n_till_map;
	int		map_row;
	int		map_col;
	int		stop;
	char	player_orientation;

}				t_game;

/******************************************************************************/
/* PROTOTYPES                                                                 */
/******************************************************************************/

// [PARSING]: CHECKERS.C
int	map_floodfill(int x, int y, t_game *game);
int	map_copy(t_game *game, t_mapdata *mapdata);
int	map_check(t_game *game, t_mapdata *mapdata);

// [PARSING]: PARSING.C
int	map_check_chars(t_game *game, t_mapdata *mapdata);
int	map_fill(t_game *game, char *line, t_mapdata *mapdata);
int	map_count_rows(t_game *game, char *line);
int	map_check_ext(t_game *game);
int	mlx_stuff(t_mapdata *mapdata, t_game *game);

// [PARSING]: UTILS.C
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);

// [PARSING]: VARIABLES.C
void	free_split(char **split, bool skip, int index);
int		free_all_and_error(char	**split_line, char *str);
int		get_colors(char	**split_line, t_mapdata *mapdata);
int		get_other_cases(char **split_line, t_mapdata *mapdata, t_game *game);
int		get_one_variable(t_game *game, char *line, t_mapdata *mapdata);
int		loop_through_lines(t_game *game, char *line, t_mapdata *mapdata);
int		get_variables(t_game *game, char *line, t_mapdata *mapdata);
void	init_map_variables(t_game *game, t_mapdata *mapdata);
int		map_parse(t_game *game, t_mapdata *mapdata);

// [TOOLS]: ERROR.C
int		error_msg_ret(char *error_msg, int ret_code);

// [DEBUG]: MISC.C
void	debug_print_map(t_mapdata *mapdata);
void	debug_highlight_player(t_mapdata *mapdata);
void	debug_print_2darray(char **map);

// [MATH]: CONVERSIONS.C
float	radians_to_degrees(float radians);
float	degrees_to_radians(float degrees);

// [FREE]: MISC.C
void	map_free(char **map, t_game *game);

#endif
