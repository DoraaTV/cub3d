/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printerror_rgbhex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:49:26 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 16:49:33 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex_floor(t_parsing *parsing)
{
	return (parsing->floor_value_1 << 16
		| parsing->floor_value_2 << 8 | parsing->floor_value_3);
}

int	rgb_to_hex_sky(t_parsing *parsing)
{
	return (parsing->sky_value_1 << 16
		| parsing->sky_value_2 << 8 | parsing->sky_value_3);
}

int	print_error_rgb_value(t_parsing *parsing, int i)
{
	printf("Error : Bad value for %c (RGB)\n", "RGB"[i]);
	free_parsing(parsing);
	return (0);
}

int	print_error_rgb(t_parsing *parsing)
{
	printf("Error : Non-numeric character found or number too long\n");
	free_parsing(parsing);
	return (1);
	return (0);
}
