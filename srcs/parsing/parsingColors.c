/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsingColors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 22:08:10 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/10 16:10:12 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

/*
Taken straight from the MLX readme file. It combines four individual channel
bytes into a single integer using bit-shifting.
*/

int getRGBA(int R, int G, int B, int A)
{
	return (R << 24 | G << 16 | B << 8 | A);
}

int	parseColorsLine(char **split_line, t_mapdata *mapdata)
{
	char	**split_color;
	// char	**line;
	char	*colors;
	int		i;

	i = 1;
	// line = ft_split(split_line[1], ' ');
	if (!split_line[2])
		colors = split_line[1];
	else
	{
		while (split_line[i])
		{
			colors = ft_strjoin(colors, split_line[i]);
			// free (line[i]);
			i++;
		}
	}
	// free (line);
	// free (split_line[1]);
	printf("%s\n", colors);
	split_color = ft_split(colors, ',');
	if (!split_color[0] || !split_color[1] || !split_color[2])
	{
		freeSplit(split_color, false, 0);
		return (free_all_and_error(split_line, "Wrong format variable."));
	}
	if (!ft_strncmp("F", split_line[0], 1))
	{
		checkRGB(split_line[1], mapdata->floorRGB);
		processRGB(split_line[1], mapdata->floorRGB);

	}
	if (!ft_strncmp("C", split_line[0], 1))
	{
		checkRGB(split_line[1], mapdata->ceilingRGB);
		processRGB(split_line[1], mapdata->ceilingRGB);
	}
	freeSplit(split_color, false, 0);
	freeSplit(split_line, false, 0);
	return (0);
}

int	checkRGB(char *rgbColors, int rgb[])
{
	char	**splittedRgbColors;
	int		i;

	i = 0;
	if (rgb[0] != -1)
		msgErrExit("Your map cfg contains duplicate RGB data..", 1);
	splittedRgbColors = ft_split(rgbColors, ',');
	if (!splittedRgbColors)
		msgErrExit("Failure in ft_split() in checkRGB()", 1);
	while (splittedRgbColors[i])
		i++;
	if (i != 3)
		msgErrExit("Your map cfg contains incorrect RGB data.", 1);
	cleanupCharDP(splittedRgbColors);
	return (0);
}

int	processRGB(char *rgbColors, int rgb[])
{
	int	i;
	char **splittedRgbColors;

	splittedRgbColors = ft_split(rgbColors, ',');
	if (!splittedRgbColors)
		msgErrExit("Failure in ft_split() in processRGB()", 1);
	rgb[0] = ft_atoi(splittedRgbColors[0]);
	rgb[1] = ft_atoi(splittedRgbColors[1]);
	rgb[2] = ft_atoi(splittedRgbColors[2]);
	cleanupCharDP(splittedRgbColors);
	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			msgErrExit("Your map cfg contains incorrect RGB data.", 1);
		i++;
	}
	return (0);
}
