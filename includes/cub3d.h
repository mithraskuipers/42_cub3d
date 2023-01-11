/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:38 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 16:37:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// CUSTOM LIBRARY
# include "./../libs/libft/libft.h"

// STANDARD LIBRARY
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>

// EXTERNAL LIBRARY
# include "./../libs/MLX42/include/MLX42/MLX42.h"

// CONFIGURATION
# define UNIQ_MAP_CHARS 6
# define GAME_HEIGHT 1200
# define GAME_WIDTH 1200
# define MOVE_SPEED 4
# define ROT_SPEED 4
# define DIST 0.05

// DEFINE WALLS
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

// READABILITY
# define TRUE 1
# define FALSE 0
# define START 0
# define SIDE_HORI 0
# define SIDE_VERT 1

// VECTOR STRUCT: INTEGERS
typedef struct s_ivector
{
	int	x;
	int	y;
}				t_ivector;

// VECTOR STRUCT: DOUBLES
typedef struct s_dvector
{
	double	x;
	double	y;
}				t_dvector;

// RAY DATA STRUCT
typedef struct s_ray
{
	uint32_t		pixel_color;
	uint32_t		wall_line_height;
	t_dvector		pixel_pos;
	int				cur_tex;
	mlx_texture_t	*texture;
	int				offset_from_above;
	int				screen_x_pos;
	t_dvector		dir;
	t_dvector		side_dist;
	t_dvector		delta_dist;
	t_ivector		step;
	t_ivector		map;
	t_dvector		end_pos;
	int				wall_side;
	double			perp_wall_distance;
	double			tex_line_scale;
	int				wall_direction;
	double			wall_x;
	double			dist;
	int				line_x;
	int				hit;
}	t_ray;

// PLANE OF VIEW STRUCT
typedef struct s_pov
{
	t_dvector	dir;
	t_dvector	pos;
	t_dvector	plane;
	double		camera_space_x;
}	t_pov;

// MAPDATA STRUCT
typedef struct s_mapdata
{
	int		map_fd;
	char	*map_path;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
	int32_t	floor_color;
	int32_t	ceiling_color;
	char	*paths[4];
	char	**map;
}	t_mapdata;

// GENERAL GAME DATA STRUCT
typedef struct s_game
{
	double			player_height;
	int				stop;
	int				gnl_ret;
	int				map_maxcols;
	int				len;
	int				when_map_start;
	int				map_row_tmp;
	int				width_map;
	int				height_map;
	mlx_image_t		*mlx_img;
	uint32_t		screen_width;
	uint32_t		screen_height;
	t_ray			ray;
	mlx_t			*mlx42;
	t_mapdata		mapdata;
	t_pov			pov;
	mlx_texture_t	*textures[4];
	char			**cpy_map;
	t_ivector		map_file_dims;
	int				player_count;
	t_ivector		player;
	int				has_player;
	double			movement_speed;
	double			rotation_speed;
	t_dvector		dir_perp;

}	t_game;

// main.c

// createImgs.c
void	draw_background(t_game *game);

// frame_callback.c
// static void	update_game_cfg(t_game *game)
void	frame_callback(void *arg);

// gnl.c
// int	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
char	*ft_strdup_gnl(const char *s1, int len_s1);
char	*ft_strjoin(char const *s1, char const *s2);
// static char	*make_remainder(char **string);
// static char	*make_string(char **string, char *buff);
// static char	*check_remainder_string(int fd, char *buff, char **string);
char	*gnl(int fd);

// hooksKeyboard.c
void	hooks_keyboard_walking(t_game *game, double move_speed);
void	hooks_keyboard_rotate(t_game *game, double rot_speed);
void	hooks_input(t_game *game);
void	hooks_grow_shrink(t_game *game);

// init.c
void	init_game(t_game *game);
void	init_mapdata(t_mapdata *mapdata, char **argv);
void	init_mlx(t_game *game);
int		init_textures(t_game *game);
void	init_pov_dir(t_game *game, int cardinalDirection);
void	init_pov_plane(t_game *game, int cardinalDirection);
void	init_player_pos(t_game *game);

// raycastComp1.c
void	comp_camera_space_x(t_game *game, t_pov *pov, int col);
void	comp_ray_dir(t_ray *ray, t_pov *pov);
void	comp_ray_map(t_ray *ray, t_pov *pov);
void	comp_delta_dist(t_ray *ray);
void	set_step(t_ray *ray);

// raycastComp2.c
void	comp_side_dist(t_ray *ray, char **map);
void	init_side_dist(t_ray *ray, t_pov *pov);
void	comp_perp_wall_dist(t_ray *ray);
void	which_wall_was_hit1(t_game *game);
void	which_wall_was_hit2(t_game *game);
void	where_was_wall_hit(t_ray *ray, t_pov *pov);

// raycasting.c
double	get_decimals(float f);
void	raycaster(t_game *game, t_pov *pov);

// parsing.c
int		map_floodfill(t_game *game, int x, int y);
void	map_read(t_game *game, char *line);
int		does_line_have_player(char *line);
int		get_map_file_dims(t_game *game, char *line);
void	map_mem_allocator(t_game *game, char ***map);
int		map_open(t_game *game);
int		map_check_ext(t_game *game);
int		is_char_in_string(char c, char *s);
int		get_map_cfg(t_game *game, char *line, t_mapdata *mapdata);
int		get_map_config_var(t_game *game, char *line, t_mapdata *mapdata);
void	check_player_count(t_game *game);
int		check_dup(char **split_line, t_mapdata *mapdata);

// parsingColors.c
int		parse_colors_line(char **split_line, t_mapdata *mapdata);
int		check_rgb(char *rgbColors, int rgb[]);
int		process_rgb(char *rgbColors, int rgb[]);

// debug.c
void	printMap(t_game *game);
void	printMapCopy(t_game *game);
void	printPlayerPos(t_game *game);

// raycastWalls.c
void	get_tex_pixel_col(t_game *game, int wall_height, int wall_line_height);
void	set_current_ray_texture(t_game *game);
void	how_to_center_line(t_game *game, double player_height);
void	draw_cur_wall_line(t_game *game);

// rotating.c
void	keyboard_rotate_right(t_pov *pov, double prev_dir_x, \
double prev_cam_plane_x, double rot_speed);
void	keyboard_rotate_left(t_pov *pov, double prev_dir_x, \
double prev_cam_plane_x, double rot_speed);

int		msg_err_exit(char *s, int exitCode);
int		convert_rgb_bytes_to_int(int R, int G, int B, int A);
char	*get_next_line_wrapper(t_game *game);
int		cleanup_char_dp(char **ptr);

void	free_split(char **split, bool skip, int index);
int		cleanup_everything(t_game *game);
int		free_all_and_error(char	**split_line, char *str);

// walking.c
void	keyboard_walk_up(t_dvector *pos, t_dvector *dir, char **map, \
double move_speed);
void	keyboard_walk_down(t_dvector *pos, t_dvector *dir, char **map, \
double move_speed);
void	keyboard_walk_left(t_dvector *pos, t_dvector *dir_perp, char **map, \
double move_speed);
void	keyboard_walk_right(t_dvector *pos, t_dvector *dir_perp, char **map, \
double move_speed);

#endif
