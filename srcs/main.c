#include "./../includes/cub3d.h"

int	init_textures(t_game *game, t_mapdata *mapdata)
{
	game->gamedata.textures[0] = mlx_load_png(mapdata->NO);
	if (!game->gamedata.textures[0])
		return (error_msg_ret("Failed to load NO map texture.", 1));
	game->gamedata.textures[1] = mlx_load_png(mapdata->EA);
	if (!game->gamedata.textures[1])
		return (error_msg_ret("Failed to load EA map texture.", 1));
	game->gamedata.textures[2] = mlx_load_png(mapdata->SO);
	if (!game->gamedata.textures[2])
		return (error_msg_ret("Failed to load SO map texture.", 1));
	game->gamedata.textures[3] = mlx_load_png(mapdata->WE);
	if (!game->gamedata.textures[3])
		return (error_msg_ret("Failed to load WE map texture.", 1));
	return (0);
}

void	set_start_pos(t_game *game)
{
	game->gamedata.pos_x = game->posX;
	game->gamedata.pos_y = game->posY;
	return ;
}

void	set_direction_vector(t_game *game)
{
	if (game->mapdata.spawn_cardinaldir == 'N')
	{
		game->gamedata.dir_x = 0;
		game->gamedata.dir_y = -1;
		// game->gamedata.player_radians = degrees_to_radians(0);
		// game->gamedata.player_radians = 0;
	}
	else if (game->mapdata.spawn_cardinaldir == 'E')
	{
		game->gamedata.dir_x = 1;
		game->gamedata.dir_y = 0;
		// game->gamedata.player_radians = degrees_to_radians(90);
		// game->gamedata.player_radians = 90;
	}
	else if (game->mapdata.spawn_cardinaldir == 'S')
	{
		game->gamedata.dir_x = 0;
		game->gamedata.dir_y = 1;
		// game->gamedata.player_radians = degrees_to_radians(180);
		// game->gamedata.player_radians = 180;
	}
	else if (game->mapdata.spawn_cardinaldir == 'W')
	{
		game->gamedata.dir_x = -1;
		game->gamedata.dir_y = 0;
		// game->gamedata.player_radians = degrees_to_radians(270);
		// game->gamedata.player_radians = 270;
	}
}




void	set_camera_plane(t_game *game)
{
	if (game->mapdata.spawn_cardinaldir == 'N')
	{
		// game->gamedata.plane_x = -0.66;
		// game->gamedata.plane_y = 0;
		// game->gamedata.player_radians = degrees_to_radians(0);
		// game->gamedata.player_radians = 0;
	}
	else if (game->mapdata.spawn_cardinaldir == 'E')
	{
		// game->gamedata.plane_x = 0;
		// game->gamedata.plane_y = -0.66;
		// game->gamedata.player_radians = degrees_to_radians(90);
		// game->gamedata.player_radians = 90;
	}
	else if (game->mapdata.spawn_cardinaldir == 'S')
	{
		// game->gamedata.plane_x = 0.66;
		// game->gamedata.plane_y = 0;
		// game->gamedata.player_radians = degrees_to_radians(180);
		// game->gamedata.player_radians = 180;
	}
	else if (game->mapdata.spawn_cardinaldir == 'W')
	{
		// game->gamedata.plane_x = 0;
		// game->gamedata.plane_y = 0.66;
		// game->gamedata.player_radians = degrees_to_radians(270);
		// game->gamedata.player_radians = 270;
	}
}


/*
arc tangent = inverse tangent = atan
tangent to degrees? arc tangent
*/

int	draw_bg(t_game *game)
{
	unsigned int	i;

	while (i < RES_X * RES_Y)
	{
		if (i < RES_X * (RES_Y / 2)) // upper half
			mlx_put_pixel(game->mlx_pack.image, i, 0, game->mapdata.ccolor);
		else if (i >= RES_X * (RES_Y / 2)) // lower half
			mlx_put_pixel(game->mlx_pack.image, i, 0, game->mapdata.fcolor);
		i++;
	}
	return (0);
}

void	ray_helper(t_game *game, double cameraX)
{
	game->ray->rayDirX = game->gamedata-> + coords->plane.x * cameraX;
}

t_ray	ray_cast(t_coords coords, game->mapdata->map, double cameraX)
{
	t_ray	ray;
	int		is_hit;

	is_hit = 0;
	ray_helper(coords, &ray, cameraX);
}

int	draw_game(t_game *game)
{
	int		col;
	double	cameraX;

	col = 0;
	while (col < RES_X)
	{
		//x-coordinate in camera space
		cameraX = 2 * x / (double)RES_X - 1;
		// todo
		game->ray = ray = ray_cast(&game->state, game->map_info.map, cameraX);
		// cast ray
		// draw wall
		col++;
	}
	return (0);
}

int	check_keypress(t_game *game)
{
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_pack.mlx);
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_UP))
	{
		printf("You pressed: UP ARROW KEY\n");
		mlx_close_window(game->mlx_pack.mlx);
	}
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_DOWN))
	{
		printf("You pressed: DOWN ARROW KEY\n");
		mlx_close_window(game->mlx_pack.mlx);
	}
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_LEFT))
	{
		printf("You pressed: LEFT ARROW KEY\n");
		mlx_close_window(game->mlx_pack.mlx);
	}
	if (mlx_is_key_down(game->mlx_pack.mlx, MLX_KEY_RIGHT))
	{
		printf("You pressed: RIGHT ARROW KEY\n");
		mlx_close_window(game->mlx_pack.mlx);
	}
	return (0);
}

double	ft_abs(double i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

void frame_callback(void *arg)
{
	t_game *game;
	game = (t_game *)arg;
	draw_bg(game);
	check_keypress(game);
}

int	init_mlx(t_game *game)
{
	game->mlx_pack.mlx = mlx_init(RES_X, RES_Y, "cub3D", true);
	if (!game->mlx_pack.mlx)
		return (error_msg_ret("MLX initialization failed.", 1));
	game->mlx_pack.image = mlx_new_image(game->mlx_pack.mlx, RES_X, RES_Y);
	if (!(game->mlx_pack.image))
		return (error_msg_ret("MLX new image creation failed.", 1));
	mlx_set_cursor_mode(game->mlx_pack.mlx, MLX_MOUSE_HIDDEN);
	if (mlx_image_to_window(game->mlx_pack.mlx, game->mlx_pack.image, 0, 0) < 0)
		return (error_msg_ret("MLX image to window failed.", 1));
	return (0);
}

int	init_game_config(t_game *game)
{
	game->gamedata.fov = 90;
	game->gamedata.ray_len = 40;
	return (0);
}

int start_game(t_game *game)
{
	//mlx_loop_hook(game->mlx_pack.mlx, &static_main_hook, &game);
	mlx_loop_hook(game->mlx_pack.mlx, frame_callback, game);
	mlx_loop(game->mlx_pack.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc != 2)
		return (error_msg_ret("Incorrect number of arguments.", 1));
	game.map_filename = argv[1];
	if (map_parse(&game, &game.mapdata))
		return (1);
	if (init_textures(&game, &game.mapdata))
		return (1);
	// set_camera_plane(&game);
	init_mlx(&game);
	init_game_config(&game);
	start_game(&game);
	// debug_print_2darray(game.mapdata.map);
	map_free(game.mapdata.map, &game);
	// system ("leaks cub3D");
	return (0);
}
