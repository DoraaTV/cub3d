/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:28:43 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 17:04:06 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_value_and_sky(int r, int g, t_parsing *parsing)
{
	parsing->sky_value_1 = r;
	parsing->sky_value_2 = g;
	parsing->sky_value_3 = parsing->b;
	parsing->ceiling_color = rgb_to_hex_sky(parsing);
}

int	parsing_rgbs_sky(char **text_file, t_parsing *parsing)
{
	int	line_index;
	int	r;
	int	g;

	line_index = 0;
	while (text_file[line_index] != NULL)
	{
		if (strncmp(text_file[line_index], "C ", 2) == 0)
		{
			if (parse_rgb(text_file[line_index], &r, &g, parsing) == 0)
			{
				if (r >= 0 && r <= 255 && g >= 0
					&& g <= 255 && parsing->b >= 0 && parsing->b <= 255)
				{
					check_value_and_sky(r, g, parsing);
					return (0);
				}
			}
		}
		line_index++;
	}
	printf("Error : sky values are incorrect\n");
	free_parsing(parsing);
	exit (1);
	return (1);
}

void	check_value_and_floor(int r, int g, t_parsing *parsing)
{
	parsing->floor_value_1 = r;
	parsing->floor_value_2 = g;
	parsing->floor_value_3 = parsing->b;
	parsing->floor_color = rgb_to_hex_floor(parsing);
}

int	parsing_rgbs_floor(char **text_file, t_parsing *parsing)
{
	int	line_index;
	int	r;
	int	g;

	line_index = 0;
	while (text_file[line_index] != NULL)
	{
		if (strncmp(text_file[line_index], "F ", 2) == 0)
		{
			if (parse_rgb(text_file[line_index], &r, &g, parsing) == 0)
			{
				if (r >= 0 && r <= 255 && g >= 0
					&& g <= 255 && parsing->b >= 0 && parsing->b <= 255)
				{
					check_value_and_floor(r, g, parsing);
					return (0);
				}
			}
		}
		line_index++;
	}
	printf("Error : floor values are incorrect\n");
	free_parsing(parsing);
	exit (1);
	return (1);
}
