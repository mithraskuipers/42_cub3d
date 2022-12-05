/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkuipers <mkuipers@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 07:45:46 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/12/05 22:09:32 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

double	radiansToDegrees(double radians)
{
	return ((radians) * (180 / PI));
}

double	degreesToRadians(double degrees)
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
