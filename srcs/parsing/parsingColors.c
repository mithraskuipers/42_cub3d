/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingColors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dagmarkramer <dagmarkramer@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:10 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/11 15:33:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*
Taken straight from the MLX readme file. It combines four individual channel
bytes into a single integer using bit-shifting.
*/

int	convert_rgb_bytes_to_int(int R, int G, int B, int A)
{
	return (R << 24 | G << 16 | B << 8 | A);
}

void	get_color_values(char **split_line, t_mapdata *mapdata, char *colors)
{
	if (!ft_strncmp("F", split_line[0], 1))
	{
		check_rgb(colors, mapdata->floorRGB);
		process_rgb(colors, mapdata->floorRGB);
	}
	if (!ft_strncmp("C", split_line[0], 1))
	{
		check_rgb(colors, mapdata->ceilingRGB);
		process_rgb(colors, mapdata->ceilingRGB);
	}
}

int	parse_colors_line(char **split_line, t_mapdata *mapdata)
{
	char	*colors;
	int		i;
	char	*temp;

	i = 2;
	colors = ft_strdup(split_line[1]);
	if (!colors)
		msg_err_exit("Malloc fail", 1);
	while (split_line[i])
	{
		temp = colors;
		colors = ft_strjoin(colors, split_line[i]);
		free(temp);
		if (!colors)
			msg_err_exit("Malloc fail", 1);
		i++;
	}
	get_color_values(split_line, mapdata, colors);
	free_split(split_line, false, 0);
	if (colors[0])
		free (colors);
	return (0);
}

int	check_rgb(char *rgbColors, int rgb[])
{
	char	**splitted_rgb_colors;
	int		i;

	i = 0;
	if (rgb[0] != -1)
		msg_err_exit("Your map cfg contains duplicate RGB data..", 1);
	splitted_rgb_colors = ft_split(rgbColors, ',');
	if (!splitted_rgb_colors)
		msg_err_exit("Failure in ft_split() in check_rgb()", 1);
	while (splitted_rgb_colors[i])
		i++;
	if (i != 3)
		msg_err_exit("Your map cfg contains incorrect RGB data.", 1);
	cleanup_char_dp(splitted_rgb_colors);
	return (0);
}

int	process_rgb(char *rgbColors, int rgb[])
{
	int		i;
	char	**splitted_rgb_colors;

	splitted_rgb_colors = ft_split(rgbColors, ',');
	if (!splitted_rgb_colors)
		msg_err_exit("Failure in ft_split() in process_rgb()", 1);
	rgb[0] = ft_atoi(splitted_rgb_colors[0]);
	rgb[1] = ft_atoi(splitted_rgb_colors[1]);
	rgb[2] = ft_atoi(splitted_rgb_colors[2]);
	cleanup_char_dp(splitted_rgb_colors);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			msg_err_exit("Your map cfg contains incorrect RGB data.", 1);
		i++;
	}
	return (0);
}
