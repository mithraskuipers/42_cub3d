/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initGame.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:58 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 16:35:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

void	init_game(t_game *game)
{
	game->player_height = 2;
	game->stop = 0;
	game->gnl_ret = 1;
	game->map_maxcols = 0;
	game->len = 0;
	game->when_map_start = 0;
	game->mapdata.ceiling_rgb[0] = -1;
	game->mapdata.floor_rgb[0] = -1;
	game->mlx_img = NULL;
	game->mapdata.paths[NORTH] = NULL;
	game->mapdata.paths[EAST] = NULL;
	game->mapdata.paths[SOUTH] = NULL;
	game->mapdata.paths[WEST] = NULL;
	game->textures[NORTH] = NULL;
	game->textures[EAST] = NULL;
	game->textures[SOUTH] = NULL;
	game->textures[WEST] = NULL;
	game->mapdata.map = NULL;
	game->map_file_dims.x = 0;
	game->map_file_dims.y = 0;
	game->player_count = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->has_player = 0;
}

void	init_mapdata(t_mapdata *mapdata, char **argv)
{
	mapdata->map_fd = 0;
	mapdata->map_path = argv[1];
}

void	init_mlx(t_game *game)
{
	game->mlx42 = mlx_init(game->screen_width, \
							game->screen_height, \
							"cub3D", \
							true);
	if (!game->mlx42)
		msg_err_exit("Failed during mlx_init().", 1);
	game->mlx_img = mlx_new_image(game->mlx42, \
	game->screen_width, game->screen_height);
}

int	init_textures(t_game *game)
{
	game->textures[NORTH] = mlx_load_png(game->mapdata.paths[NORTH]);
	if (game->textures[NORTH] == NULL)
		msg_err_exit("Failed during mlx_load_png().", 1);
	game->textures[EAST] = mlx_load_png(game->mapdata.paths[EAST]);
	if (game->textures[EAST] == NULL)
		msg_err_exit("Failed during mlx_load_png().", 1);
	game->textures[SOUTH] = mlx_load_png(game->mapdata.paths[SOUTH]);
	if (game->textures[SOUTH] == NULL)
		msg_err_exit("Failed during mlx_load_png().", 1);
	game->textures[WEST] = mlx_load_png(game->mapdata.paths[WEST]);
	if (game->textures[WEST] == NULL)
		msg_err_exit("Failed during mlx_load_png().", 1);
	return (0);
}
