/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/15 20:32:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/libft.h"

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_map
{
	char	**map;
	int		ntiles_cols;
	int		ntiles_rows;
}				t_map;

typedef struct	s_env
{
	t_map	*map;
}				t_env;

#endif
