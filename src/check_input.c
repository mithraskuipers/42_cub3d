/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 20:12:46 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/15 20:35:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_input(int argc, char **argv)
{
	if (argc > 2)
		return (msg_err("Too many arguments.", 1));
	// check map
	(void)argv;
	return (0);
}