






int	spawn_dir(t_game *game)
{
	double	radians;

	radians = 0;
	if (game->mapdata.spawn_cardinaldir == 'N')
		radians = 0;
	else if (game->mapdata.spawn_cardinaldir == 'E')
		radians = M_PI / 2;
	else if (game->mapdata.spawn_cardinaldir == 'S')
		radians = M_PI;
	else if (game->mapdata.spawn_cardinaldir == 'W')
		radians = 1.5 * M_PI;
	game->gamedata.radians = radians;
	return (0);
}

int	rotate(t_game *game, double radians)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->ray.dir.x;
	game->ray.dir.x = game->ray.dir.x * cos(radians) - game->ray.dir.y * sin(radians);
	game->ray.dir.y = old_dir_x * sin(radians) + game->ray.dir.y * cos(radians);
	old_plane_x = game->ray.plane.x;
	game->ray.plane.x = game->ray.plane.x * cos(radians) - game->ray.plane.y * sin(radians);
	game->ray.plane.y = old_plane_x * sin(radians) + game->ray.plane.y * cos(radians);
	return (0);
}

/*
	- Calculate x-coordinate in camera space
	- Calculate ray position and direction
	- Save which box of the map we're in
*/
void	set_ray_pos(t_game *game, int col)
{
	game->ray.cameraX = (float)(2 * col) / (float)(RES_X - 1);
	game->ray.dir.x = game->ray.dir.x + game->ray.plane.x * game->ray.cameraX;
	game->ray.dir.y = game->ray.dir.y + game->ray.plane.y * game->ray.cameraX;
	game->ray.map_x = game->ray.pos.x;
	game->ray.map_y = game->ray.pos.y;
}


/*
	- Calculate length of ray from one x or y-side to next x or y-side
	- Calculate step and initial sideDist
*/
void	get_ratios(t_ray *ray)
{
	ray->deltaDist.y = fabs(1 / ray->dir.x);
	ray->deltaDist.x = fabs(1 / ray->dir.y);
	ray->hit = 0;
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (ray->pos.x - ray->map_x) * ray->deltaDist.y;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (ray->map_x + 1.0 - ray->pos.x) * ray->deltaDist.y;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (ray->pos.y - ray->map_y) * ray->deltaDist.x;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (ray->map_y + 1.0 - ray->pos.y) * ray->deltaDist.x;
	}
}

void	debug_print_ray_data(t_game *game, int col)
{
	printf("\n");
	printf("raycol# %d:\tray.cameraX: \t\t%f\n", col, game->ray.cameraX);
	printf("raycol# %d:\tray.dir: \t\t%f\t%f\n", col, game->ray.dir.x, game->ray.dir.y);
	printf("raycol# %d:\tray.plane: \t\t%f\t%f\n", col, game->ray.plane.x, game->ray.plane.y);
	printf("raycol# %d:\tray.sideDist: \t\t%f\t%f\n", col, game->ray.sideDist.x, game->ray.sideDist.y);
	printf("raycol# %d:\tray.map: \t\t%d\t\t%d\n", col, game->ray.map_x, game->ray.map_y);
}

/*
	- Jump to next map square in x-direction OR in y-direction
	- Check if ray has hit a wall
*/

void	perform_dda(t_game *game)
{
	while (game->ray.hit == 0)
	{
		// printf("running dda\n");
		if (game->ray.sideDist.x < game->ray.sideDist.y)
		{
			game->ray.sideDist.x += game->ray.deltaDist.y;
			// game->ray.map_x += game->ray.step.x;
			// game->ray.map_x = (int)game->ray.map_x + (int)game->ray.step.x;
			game->ray.map_x = 66;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sideDist.y += game->ray.deltaDist.x;
			// game->ray.map_y += game->ray.step.y;
			// game->ray.map_y = (int)game->ray.map_y + (int)game->ray.step.y;
			game->ray.map_y = 99;
			game->ray.side = 1;
		}
		// game->ray.hit = 1;
		// printf("ray.map_x: %d\n", game->ray.map_x);
		// printf("ray.map_y: %d\n", game->ray.map_y);
		// if (game->mapdata.map[game->ray.map_x][game->ray.map_y] == '1')
		// 	game->ray.hit = 1;
	}
}

int	draw_img(t_game *game)
{
	int	col;

	draw_bg(game);
	col = 0;
	while (col < RES_X)
	{
		set_ray_pos(game, col);
		get_ratios(&(game->ray)); // set ray len
		debug_print_ray_data(game, col);
		// perform_dda(game);
		col++;
	}
	return (0);
}

int	init_raycaster(t_game *game)
{
	game->ray.pos.x = game->playerSpawnX + 0.5;
	game->ray.pos.y = game->playerSpawnY + 0.5;
	game->ray.dir.x = -1;
	game->ray.dir.y = 0;
	game->ray.plane.x = 0;
	game->ray.plane.y = .66;
	game->ray.move.l = 0;
	game->ray.move.r = 0;
	game->ray.rot.l = 0;
	game->ray.rot.r = 0;
	return (0);
}


                          */
/******************************************************************************/

int start_game(t_game *game)
{
	mlx_loop_hook(game->mlx.mlx, frame_callback, game);
	mlx_loop(game->mlx.mlx);
	return (0);
}




/******************************************************************************/
/* frames                                                                     */
/******************************************************************************/

void frame_callback(void *arg)
{
	t_game *game;
	game = (t_game *)arg;
	// draw_bg(game);
	check_keypress(game);
}


void	debug_print_rotate(t_game *game)
{
	printf("debug_print_rotate()\n");
	printf("game->ray.dir.x: \t%f\n", game->ray.dir.x);
	printf("game->ray.dir.y: \t%f\n", game->ray.dir.y);
	printf("game->ray.plane.x: \t%f\n", game->ray.plane.x);
	printf("game->ray.plane.y: \t%f\n", game->ray.plane.y);
}

void	debug_spawn_dir(t_game *game)
{
	printf("game.gamedata.radians: %f\n", game->gamedata.radians);
}