/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:17:25 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/15 20:17:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	msg_err(char *s, int return_code)
{
	if (ft_strlen(s) != 0)
		printf("Error: %s\n", s);
	return (return_code);
}
