/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dagmarkramer <dagmarkramer@student.42.f      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/09 11:06:10 by mikuiper      #+#    #+#                 */
/*   Updated: 2023/01/11 11:54:08 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/cub3d.h"

int	msg_err_exit(char *s, int exitCode)
{
	ft_putstr_fd("Error\n", 2);
	if (ft_strlen(s) != 0)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
	}
	system ("leaks cub3D");
	exit (exitCode);
}
