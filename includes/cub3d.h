/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:38 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/08 22:19:06 by mikuiper      ########   odam.nl         */
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
# define GAME_WIDTH 1000
# define GAME_HEIGHT 1000
# define MOVE_SPEED 4
# define ROT_SPEED 4
# define WALL_BOUNCE 0.025

// DEFINE WALLS
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

// READABILITY
# define TRUE 1
# define FALSE 0
# define START 0
# define SIDE_HOR 0
# define SIDE_VER 1

// VECTOR STRUCT: FLOATS
typedef struct	s_fvector
{
	float	x;
	float	y;
}				t_fvector;

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
	t_fvector		pixelPos;
	int				curTex;
	mlx_texture_t	*texture;
	int				offsetFromAbove;
	int				screenXPos;
	t_dvector		dir;
	t_dvector		sideDist;
	t_dvector		deltaDist;
	t_ivector		step;
	t_ivector		map;
	t_fvector		end_pos;
	int				wallSide;
	double			perpetualWallDistance;
	double			texLineScale;
	int				wall_ori;
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
	int stop;
	int gnl_ret;
	int nRowsMapFile;
	int map_maxcols;
	int len;
	int whenMapMazeStart;
	int map_row_tmp;

	mlx_image_t	*mlxImg;
	uint32_t			screen_width;
	uint32_t			screen_height;
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

// raycastComp.c
void	compCameraSpaceX(t_game *game, t_pov *pov, int col);
void	compRayDir(t_ray *ray, t_pov *pov);
void	compDeltaDist(t_ray *ray);
void	compSideDist(t_ray *ray, char **map);
void	setStep(t_ray *ray);
void	compInitSideDist(t_ray *ray, t_pov *pov);
void	compPerpetualWallDist(t_ray *ray);
void	whichWallWasHit(t_game *game);
void	whereWasWallHit(t_ray *ray, t_pov *pov);

// raycasting.c
float	ft_fmod(float f);
void	compRayMap(t_ray *ray, t_pov *pov);
void	howTallWallLine(t_ray *ray);
int		whichTextureHasWall(t_game *game, char wall_ori);
void	raycaster(t_game *game, t_pov *pov);

// parsing.c
void	mapFloodfill(t_game *game, int x, int y);
void	mapRead(t_game *game);
int		doesLineHavePlayer(char *line);
int		getMapFileDims(t_game *game, char *line);
void	mapMemAllocator(t_game *game, char ***map);
int		mapOpen(t_game *game);
int		mapCheckExt(t_game *game);
int		isCharInString(char c, char *s);
int		getMapConfig(t_game *game, char *line, t_mapdata *mapdata);
int		getMapConfigVar(t_game *game, char *line, t_mapdata *mapdata);
void	checkPlayerCount(t_game *game);

// parsingColors.c
int	parseColorsLine(char **split_line, t_mapdata *mapdata);
int	checkRGB(char *rgbColors, int rgb[]);
int	processRGB(char *rgbColors, int rgb[]);

// debug.c
void	printMap(t_game *game);
void	printMapCopy(t_game *game);
void	printPlayerPos(t_game *game);

// raycastWalls.c
void	getTexPixelCol(t_game *game, int wallHeight, int wallLineHeight);
void	setCurrentRayTexture(t_game *game);
void	howToCenterLine(t_game *game);
void	drawCurWallLine(t_game *game);

// rotating.c
void	keyboardRotateRight(t_pov *pov, double prevDirX, double prevPlaneX, double rotSpeed);
void	keyboardRotateLeft(t_pov *pov, double prevDirX, double prevPlaneX, double rotSpeed);

// utils.c
int		msgErrExit(char *s, int exitCode);
int		getRGBA(int R, int G, int B, int A);
char	*get_next_line_wrapper(t_game *game);
int		freeCharDP(char **ptr);

void	freeSplit(char **split, bool skip, int index);
int		cleanupGame(t_game *game);
int		free_all_and_error(char	**split_line, char *str);

// walking.c
void	keyboardWalkUp(t_dvector *pos, t_dvector *dir, char **map, double moveSpeed);
void	keyboardWalkDown(t_dvector *pos, t_dvector *dir, char **map, double moveSpeed);
void	keyboardWalkLeft(t_dvector *pos, t_dvector *dirPerp, char **map, double moveSpeed);
void	keyboardWalkRight(t_dvector *pos, t_dvector *dirPerp, char **map, double moveSpeed);

#endif
