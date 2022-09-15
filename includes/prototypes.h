/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prototypes.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 13:35:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/15 20:49:15 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

#include "structs.h"

// CHECK_INPUT.C
int	check_input(int argc, char **argv);

// READ_MAP.C
int	read_map(char *map_name, t_env *env);

// MESSAGES.C
int	msg_err(char *s, int return_code);

#endif
