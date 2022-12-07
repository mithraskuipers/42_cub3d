/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/09 13:23:27 by dkramer       #+#    #+#                 */
/*   Updated: 2022/12/07 11:56:07 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	createTrgb(unsigned char t, unsigned char r,
unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}
