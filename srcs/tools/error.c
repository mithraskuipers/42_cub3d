/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 18:10:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/11/09 09:59:11 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// error_msg_ret()
// Prints an error message and returns with code.
int	error_msg_ret(char *error_msg, int ret_code)
{
	if (ft_strlen(error_msg) == 0)
		return (ret_code);
	printf("Error.\n%s\n", error_msg);
	return (ret_code);
}
