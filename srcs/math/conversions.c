/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 07:45:46 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/18 07:46:03 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

float	radians_to_degrees(float radians)
{
	return ((radians) * (180 / PI));
}

float	degrees_to_radians(float degrees)
{
	return ((degrees) * (PI / 180));
}

double	ft_abs(double i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}
