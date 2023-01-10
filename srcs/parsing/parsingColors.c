/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingColors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagmarkramer <dagmarkramer@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:08:10 by dkramer           #+#    #+#             */
/*   Updated: 2023/01/10 21:33:11 by dagmarkrame      ###   ########.fr       */
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
	char	*colors;
	int		i;
	char	*temp;

	i = 1;
	colors = "";
	if (!split_line[2])
		colors = split_line[1];
	else
	{
		while (split_line[i])
		{
			temp = ft_strdup(colors);
			if (colors[0])
				free (colors);
			if (!temp)
				msgErrExit("Malloc fail", 1);
			colors = ft_strjoin(temp, split_line[i]);
			free (temp);
			if (!colors)
				msgErrExit("Malloc fail", 1);
			i++;
		}
	}
	if (!ft_strncmp("F", split_line[0], 1))
	{
		checkRGB(colors, mapdata->floorRGB);
		processRGB(colors, mapdata->floorRGB);

	}
	if (!ft_strncmp("C", split_line[0], 1))
	{
		checkRGB(colors, mapdata->ceilingRGB);
		processRGB(colors, mapdata->ceilingRGB);
	}
	freeSplit(split_line, false, 0);
	if (colors[0])
		free (colors);
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
