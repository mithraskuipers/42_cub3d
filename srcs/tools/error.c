/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 18:10:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/12/07 08:30:35 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// errorMsgRet()
// Prints an error message and returns with code.
int	errorMsgRet(char *error_msg, int ret_code)
{
	if (ft_strlen(error_msg) == 0)
		return (ret_code);
	printf("Error.\n%s\n", error_msg);
	return (ret_code);
}
