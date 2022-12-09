#include "./../includes/cub3d.h"

/******************************************************************************/
/* keys                                                                       */
/******************************************************************************/

int	checkKeypress(t_game *game)
{
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx.mlx);
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_UP))
	{
		printf("You pressed: UP ARROW KEY\n");
		mlx_close_window(game->mlx.mlx);
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_DOWN))
	{
		printf("You pressed: DOWN ARROW KEY\n");
		mlx_close_window(game->mlx.mlx);
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_LEFT))
	{
		printf("You pressed: LEFT ARROW KEY\n");
		mlx_close_window(game->mlx.mlx);
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_RIGHT))
	{
		printf("You pressed: RIGHT ARROW KEY\n");
		mlx_close_window(game->mlx.mlx);
	}
	return (0);
}

/******************************************************************************/
/* textures                                                                   */
/******************************************************************************/

int	initTextures(t_game *game, t_mapdata *mapdata)
{
	game->gamedata.textures[0] = mlx_load_png(mapdata->NO);
	if (!game->gamedata.textures[0])
		return (errorMsgRet("Failed to load NO map texture.", 1));
	game->gamedata.textures[1] = mlx_load_png(mapdata->EA);
	if (!game->gamedata.textures[1])
		return (errorMsgRet("Failed to load EA map texture.", 1));
	game->gamedata.textures[2] = mlx_load_png(mapdata->SO);
	if (!game->gamedata.textures[2])
		return (errorMsgRet("Failed to load SO map texture.", 1));
	game->gamedata.textures[3] = mlx_load_png(mapdata->WE);
	if (!game->gamedata.textures[3])
		return (errorMsgRet("Failed to load WE map texture.", 1));
	return (0);
}

/******************************************************************************/
/* init                                                                       */
/******************************************************************************/

int	initMLX(t_game *game)
{
	game->mlx.mlx = mlx_init(RES_X, RES_Y, "cub3D", true);
	if (!game->mlx.mlx)
		return (errorMsgRet("MLX initialization failed.", 1));
	game->mlx.img = mlx_new_image(game->mlx.mlx, RES_X, RES_Y);
	if (!(game->mlx.img))
		return (errorMsgRet("MLX new image creation failed.", 1));
	mlx_set_cursor_mode(game->mlx.mlx, MLX_MOUSE_HIDDEN);
	if (mlx_image_to_window(game->mlx.mlx, game->mlx.img, 0, 0) < 0)
		return (errorMsgRet("MLX image to window failed.", 1));
	return (0);
}

/*
Init at specific values. Will be adjusted by cardinal direction spawn char.
The ratio between the length of the direction and the camera plane determinates
the FOV, here the direction vector is a bit longer than the camera plane, so the
FOV will be smaller than 90° (more precisely, the FOV is 2 * atan(0.66/1.0)=66°,
which is perfect for a first person shooter game).
dirX and dirY are setup in accordance with lodev
*/

int	initRaycaster(t_game *game)
{
	game->ray.posX = game->playerPos.x + 0.5;
	game->ray.posY = game->playerPos.y + 0.5;

	// initialize ray directions
	game->ray.dirX = -1;
	game->ray.dirY = 0;
	game->ray.planeX = 0;
	game->ray.planeY = 0.66;
	game->ray.stepSize = 0.1;
	game->ray.rotationSpeed = M_PI / 60;
	game->ray.forward = 0;
	game->ray.backward = 0;
	game->ray.left = 0;
	game->ray.right = 0;
	game->ray.rot_left = 0;
	game->ray.rot_right = 0;
	return (0);
}

/******************************************************************************/
/* debug                                                                      */
/******************************************************************************/

void	debugInitRaycaster(t_game *game)
{
	printf("game->ray.posX: %f\n", game->ray.posX = game->playerPos.x + 0.5);
	printf("game->ray.posY: %f\n", game->ray.posY = game->playerPos.y + 0.5);
	printf("game->ray.dirX: %f\n", game->ray.dirX);
	printf("game->ray.dirY: %f\n", game->ray.dirY);
	printf("game->ray.planeX: %f\n", game->ray.planeX);
	printf("game->ray.planeY: %f\n", game->ray.planeY);
	printf("game->ray.stepSize: %f\n", game->ray.stepSize);
	printf("game->ray.rotationSpeed: %f\n", game->ray.rotationSpeed);
	printf("game->ray.forward: %d\n", game->ray.forward);
	printf("game->ray.back: %d\n", game->ray.backward);
	printf("game->ray.left: %d\n", game->ray.left);
	printf("game->ray.right: %d\n", game->ray.right);
	printf("game->ray.rot_left: %d\n", game->ray.rot_left);
	printf("game->ray.rot_right: %d\n", game->ray.rot_right);
	printf("game->ray.cameraX: %f\n", game->ray.cameraX);
	printf("game->ray.rayDirX: %f\n", game->ray.rayDirX);
	printf("game->ray.rayDirY: %f\n", game->ray.rayDirY);
	printf("game->ray.mapX: %d\n", game->ray.mapX);
	printf("game->ray.mapY: %d\n", game->ray.mapY);
	printf("game->ray.deltaDistX: %f\n", game->ray.deltaDistX);
	printf("game->ray.deltaDistY: %f\n", game->ray.deltaDistY);
	printf("game->ray.sideDistX: %f\n", game->ray.sideDistX);
	printf("game->ray.sideDistY: %f\n", game->ray.sideDistY);
	printf("game->ray.hit: %d\n", game->ray.hit);
	if (game->ray.hit == 1)
		exit (1);
	printf("\n");
}

void	debugSpawnRadians(t_game *game)
{
	printf("\nspawnRadians: %f\n\n", game->spawnRadians);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

int	spawnDegrees(t_game *game)
{
	int	degrees;

	degrees = 0;
	if (game->mapdata.spawn_cardinaldir == 'N')
		degrees = 0;
	else if (game->mapdata.spawn_cardinaldir == 'E')
		degrees = 90;
	else if (game->mapdata.spawn_cardinaldir == 'S')
		degrees = 180;
	else if (game->mapdata.spawn_cardinaldir == 'W')
		degrees = 270;
	return (degrees);
}

void	updateRayData(t_game *game)
{
	double	dirX_tmp;
	double	planeX_tmp;

	dirX_tmp = game->ray.dirX;
	game->ray.dirX = game->ray.dirX * cos(game->spawnRadians) - game->ray.dirY * sin(game->spawnRadians);
	game->ray.dirY = dirX_tmp * sin(game->spawnRadians) + game->ray.dirY * cos(game->spawnRadians);
	planeX_tmp = game->ray.planeX;
	game->ray.planeX = game->ray.planeX * cos(game->spawnRadians) - game->ray.planeY * sin(game->spawnRadians);
	game->ray.planeY = planeX_tmp * sin(game->spawnRadians) + game->ray.planeY * cos(game->spawnRadians);
}

/*
Calculate the x-coordinate in camera space
Calculate ray direction (rayDirX, rayDirY)
Save the player coordinates
*/

/*


*/

void	setRayPos(t_game *game, int x)
{
	game->ray.cameraX = 2 * x / (double)RES_X - 1;
	game->ray.rayDirX = game->ray.dirX + game->ray.planeX * game->ray.cameraX;
	game->ray.rayDirY = game->ray.dirY + game->ray.planeY * game->ray.cameraX;
	game->ray.mapX = (int)game->ray.posX;
	game->ray.mapY = (int)game->ray.posY;
}

/*
Compute the distance a ray has from one xside or yside to the next xside or yside.
Calculate step and initial sideDist
*/

/*



*/

void	setRayLen(t_ray *ray)
{
	ray->deltaDistY = fabs(1 / ray->rayDirX);
	ray->deltaDistX = fabs(1 / ray->rayDirY);
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistY;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistY;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistX;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistX;
	}
}

/*
DDA is a fast algorithm typically used on square grids to find which squares a 
line hits (for example to draw a line on a screen, which is a grid of square 
pixels). So we can also use it to find which squares of the map our ray hits, 
and stop the algorithm once a square that is a wall is hit.
*/

/*


*/

void	digitalDifferentialAnalysis(t_game *game)
{
	printf("\nRunning digitalDifferentialAnalysis..\n");
	while (game->ray.hit == 0)
	{
		if (game->ray.sideDistX < game->ray.sideDistY)
		{
			game->ray.sideDistX = game->ray.sideDistX + game->ray.deltaDistY;
			game->ray.mapX = game->ray.mapX + game->ray.stepX;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sideDistY = game->ray.sideDistY + game->ray.deltaDistX;
			game->ray.mapY = game->ray.mapY + game->ray.stepY;
			game->ray.side = 1;
		}
		if (game->mapdata.map[game->ray.mapX][game->ray.mapY] == '1')
		{
			game->ray.hit = 1;
			// debugInitRaycaster(game);
			// exit(1);
		}
	}
}

/*



*/

void	setupGameWorld(t_ray *ray)
{
	if (!ray->side) // == 0
	{
		ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
	}
	else if (ray->side)
	{
		ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
	}
	ray->lineHeight = (int)(RES_Y / ray->perpWallDist);
	ray->drawStart = -(ray->lineHeight) / 2 + RES_Y / 2;
	if (ray->drawStart < 0)
	{
		ray->drawStart = 0;
	}
	ray->drawEnd = ray->lineHeight / 2 + RES_Y / 2;
	if (ray->drawEnd >= RES_Y)
	{
		ray->drawEnd = RES_Y - 1;
	}
}

/*



*/

int	renderFrame(t_game *game)
{
	int	col;

	col = 0;
	while (col < RES_X)
	{
		// sleep(1);
		setRayPos(game, col);
		game->ray.hit = 0;
		setRayLen(&(game->ray));
		debugInitRaycaster(game);
		printf("col: %d\n", col);
		digitalDifferentialAnalysis(game);
		setupGameWorld(&(game->ray));
		col++;
	}
	return (0);
}

/******************************************************************************/
/*                                                                            */
/******************************************************************************/

void frameCallback(void *arg)
{
	t_game *game;
	game = (t_game *)arg;
	// renderBackground(game);
	// checkKeypress(game);
	initRaycaster(game);
	debugInitRaycaster(game);
	game->spawnRadians = degreesToRadians(spawnDegrees(game));
	debugSpawnRadians(game);
	updateRayData(game);
	debugInitRaycaster(game);
	renderFrame(game);
	printf("\n\n");
}

int startGame(t_game *game)
{
	// mlx_loop_hook(game->mlx.mlx, frameCallback, game);
	// mlx_loop(game->mlx.mlx);

	frameCallback(game);
	return (0);
}

/******************************************************************************/
/* main                                                                       */
/******************************************************************************/

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (errorMsgRet("Incorrect number of arguments.", 1));
	game.map_filename = argv[1];
	if (parseMap(&game, &game.mapdata))
		return (1);
	// if (initTextures(&game, &game.mapdata))
	// 	return (1);
	// initMLX(&game);
	startGame(&game);
	//map_free(game.mapdata.map, &game);
	return (0);
}
