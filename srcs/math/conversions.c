/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 07:45:46 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/12/07 11:59:26 by mikuiper      ########   odam.nl         */
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

double	toAbsolute(double i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}
