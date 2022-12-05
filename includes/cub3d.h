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
# define RES_X	50
# define RES_Y	20

# define STEP 0.1
# define EMPTY '0'
# define WALL '1'
# define SUCCESS 0
# define FAIL -1

# define X 1
# define Y 2

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
# include <math.h>

/******************************************************************************/
/* STRUCTS                                                                    */
/******************************************************************************/

typedef struct s_dvector_xy
{
	float	x;
	float	y;
}	t_dvector_xy;

typedef struct s_ivector_xy
{
	int	x;
	int	y;
}	t_ivector_xy;

typedef struct s_fvector_lr
{
	float	l;
	float	r;
}	t_fvector_lr;

typedef struct s_gamedata
{
	mlx_texture_t	*textures[4];
	double		radians;
}	t_gamedata;

typedef struct s_mapdata
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	uint32_t	fcolor;
	uint32_t	ccolor;
	char		**map;
	char		spawn_cardinaldir;
}	t_mapdata;

typedef struct	s_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*txts[4];
}	t_mlx;

typedef struct s_ray {
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			step_size;
	double			rot_speed;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				x_tex;
	double			y_tex;
	double			y_tex_step;
	int				forward;
	int				backward;
	int				left;
	int				right;
	int				rot_left;
	int				rot_right;
}	t_ray;

typedef struct s_game
{
	t_ray		ray;
	t_gamedata	gamedata;
	t_mapdata	mapdata;
	t_mlx		mlx;
	t_ivector_xy	playerPos;
	t_dvector_xy	dir;
	t_dvector_xy	plane;
	t_dvector_xy	rayDir;
	t_dvector_xy	sideDist;
	t_dvector_xy	deltaDist;
	t_fvector_lr	move;
	t_fvector_lr	rot;
	t_dvector_xy	step;
	double		spawnRadians;
	double		perpWallDist;
	int			hit;
	int			side;
	double		step_size;
	float		cameraX;
	char	*map_filename;
	int		n_rows;
	int		len;
	int		gnl_ret;
	int		fd;
	int		error;
	int		map_maxcols;
	char	**map_tmp;
	int		playerSpawnX;
	int		playerSpawnY;
	int		n_till_map;
	int		map_row_tmp;
	int		map_col_tmp;
	int		stop;
}	t_game;

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
double	radiansToDegrees(double radians);
double	degreesToRadians(double degrees);
double	ft_abs(double i);

// [FREE]: MISC.C
void	map_free(char **map, t_game *game);

// [DRAW]: BG.C
int	draw_bg(t_game *game);

#endif
