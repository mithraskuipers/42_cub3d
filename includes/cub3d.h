/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:38 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 11:44:59 by dkramer       ########   odam.nl         */
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
# define GAME_WIDTH 800
# define GAME_HEIGHT 600
# define MOVE_SPEED 4
# define ROT_SPEED 4
# define BOUNCE 0.05

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
typedef struct	s_ivector
{
	int	x;
	int	y;
}				t_ivector;

// VECTOR STRUCT: DOUBLES
typedef struct	s_dvector
{
	double	x;
	double	y;
}				t_dvector;

// RAY DATA STRUCT
typedef struct s_ray
{
	uint32_t		pixelColor;
	uint32_t		wallLineHeight;
	t_dvector		pixelPos;
	int				curTex;
	mlx_texture_t	*texture;
	int				offsetFromAbove;
	int				screenXPos;
	t_dvector		dir;
	t_dvector		sideDist;
	t_dvector		deltaDist;
	t_ivector		step;
	t_ivector		map;
	t_dvector		end_pos;
	int				wallSide;
	double			perpendicularWallDistance;
	double			texLineScale;
	int				wallDirection;
	double			wallX;
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
	double		cameraSpaceX;
}	t_pov;

// MAPDATA STRUCT
typedef struct s_mapdata
{
	int		mapFd;
	char	*mapPath;
	int		mapFileNbrLines;
	int		floorRGB[3];
	int		ceilingRGB[3];
	int32_t	floorColor;
	int32_t	ceilingColor;
	char	*paths[4];
	char	**map;
}	t_mapdata;

// GENERAL GAME DATA STRUCT
typedef struct s_game
{
	double player_height;
	int stop;
	int gnl_ret;
	int nRowsMapFile;
	int map_maxcols;
	int len;
	int whenMapMazeStart;
	int map_row_tmp;
	int widthMap;
	int heightMap;
	mlx_image_t	*mlxImg;
	uint32_t		screen_width;
	uint32_t		screen_height;
	t_ray			ray;
	mlx_t			*mlx42;
	t_mapdata		mapdata;
	t_pov			pov;
	mlx_texture_t	*textures[4];
	char			**cpy_map;
	t_ivector		mapFileDims;
	int				player_count;
	t_ivector		player;
	int				has_player;
	double			movementSpeed;
	double			rotationSpeed;
	t_dvector	dirPerp;

}	t_game;

// main.c

// createImgs.c
// static void	combineColors(t_game *game);
// static void	drawImgPixelLoop(t_game *game, uint32_t Y_START, uint32_t Y_END, uint32_t color);
void	drawBackground(t_game *game);

// frameCallback.c
// static void	updateGameCfg(t_game *game)
void	frameCallback(void *arg);

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
void	hooksKeyboardWalking(t_game *game, double moveSpeed);
void	hooksKeyboardRotate(t_game *game, double rotSpeed);
void	hooksInput(t_game *game);

// init.c
void	initGame(t_game *game);
void	initMapdata(t_mapdata *mapdata, char **argv);
void	initMLX(t_game *game);
int		initTextures(t_game *game);
void	initPovDir(t_game *game, int cardinalDirection);
void	initPovPlane(t_game *game, int cardinalDirection);
void	initPlayerPos(t_game *game);

// raycastComp1.c
void	compCameraSpaceX(t_game *game, t_pov *pov, int col);
void	compRayDir(t_ray *ray, t_pov *pov);
void	compRayMap(t_ray *ray, t_pov *pov);
void	compDeltaDist(t_ray *ray);
void	setStep(t_ray *ray);

// raycastComp2.c
void	compSideDist(t_ray *ray, char **map);
void	initSideDist(t_ray *ray, t_pov *pov);
void	compPerpendicularWallDist(t_ray *ray);
void	whichWallWasHit(t_game *game);
void	whereWasWallHit(t_ray *ray, t_pov *pov);



// raycasting.c
double	getDecimals(float f);
void	raycaster(t_game *game, t_pov *pov);

// parsing.c
int		map_floodfill(t_game *game, int x, int y);
void	map_read(t_game *game);
int		does_line_have_player(char *line);
int		get_map_file_dims(t_game *game, char *line);
void	map_mem_allocator(t_game *game, char ***map);
int		map_open(t_game *game);
int		map_check_ext(t_game *game);
int		is_char_in_string(char c, char *s);
int		get_map_cfg(t_game *game, char *line, t_mapdata *mapdata);
int		get_map_config_var(t_game *game, char *line, t_mapdata *mapdata);
void	check_player_count(t_game *game);

// parsingColors.c
int	parse_colors_line(char **split_line, t_mapdata *mapdata);
int	checkRGB(char *rgbColors, int rgb[]);
int	processRGB(char *rgbColors, int rgb[]);

// debug.c
void	printMap(t_game *game);
void	printMapCopy(t_game *game);
void	printPlayerPos(t_game *game);

// raycastWalls.c
void	getTexPixelCol(t_game *game, int wallHeight, int wallLineHeight);
void	setCurrentRayTexture(t_game *game);
void	howToCenterLine(t_game *game, double player_height);
void	drawCurWallLine(t_game *game);

// rotating.c
void	keyboardRotateRight(t_pov *pov, double prevDirX, double prevPlaneX, double rotSpeed);
void	keyboardRotateLeft(t_pov *pov, double prevDirX, double prevPlaneX, double rotSpeed);

int		msg_err_exit(char *s, int exitCode);
int		convert_rgb_bytes_to_int(int R, int G, int B, int A);
char	*get_next_line_wrapper(t_game *game);
int		cleanupCharDP(char **ptr);

void	free_split(char **split, bool skip, int index);
int		cleanup_everything(t_game *game);
int		free_all_and_error(char	**split_line, char *str);

// walking.c
void	keyboardWalkUp(t_dvector *pos, t_dvector *dir, char **map, double moveSpeed);
void	keyboardWalkDown(t_dvector *pos, t_dvector *dir, char **map, double moveSpeed);
void	keyboardWalkLeft(t_dvector *pos, t_dvector *dirPerp, char **map, double moveSpeed);
void	keyboardWalkRight(t_dvector *pos, t_dvector *dirPerp, char **map, double moveSpeed);

#endif
