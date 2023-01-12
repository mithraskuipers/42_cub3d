/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strreplace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 14:18:26 by dkramer       #+#    #+#                 */
/*   Updated: 2023/01/12 10:41:40 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strreplace(char *dst, int before, int after)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		if (dst[i] == before)
			dst[i] = after;
		i++;
	}
	return (dst);
}
