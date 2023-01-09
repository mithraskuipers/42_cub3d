/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 11:06:10 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/09 11:06:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	msgErrExit(char *s, int exitCode)
{
	ft_putstr_fd("Error\n", 2);
	if (ft_strlen(s) != 0)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
	}
	exit (exitCode);
}