/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:27:25 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 14:31:31 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_check_file(char *dst, t_data *s, int i)
{
	if (i == 0)
		dst = s->parsing.no_txt;
	else if (i == 1)
		dst = s->parsing.so_txt;
	else if (i == 2)
		dst = s->parsing.we_txt;
	else if (i == 3)
	{
		dst = s->parsing.ea_txt;
	}
	return (dst);
}

float	ft_sign(float n)
{
	if (n > 0)
		return (1.0f);
	else if (n < 0)
		return (-1.0f);
	else
		return (0.0f);
}
