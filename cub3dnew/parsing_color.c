/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:28:43 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 10:41:59 by thrio            ###   ########.fr       */
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

int	parse_rgb(char *str, int *r, int *g, int *b, t_parsing *parsing)
{
	int	index;
	int	*values[3] = {r, g, b};
	int	i;
	
	i = 0;
	index = 2;
	while (str[index] == ' ')
			index++;
	while (i < 3) 
	{
		if (str[index] == '-' || !is_digit(str[index])) 
		{
			printf("Error : Bad value for %c (RGB)\n", "RGB"[i]);
			free_parsing(parsing);
			return 1;
		}
		*values[i] = atoi(str + index);
		while (isdigit(str[index])) 
		{
			index++;
		}
		if (i < 2)
		{  
			if (str[index] != ',') 
			{
				printf("Error : Incorrect separator character after %c.\n", "RGB"[i]);
				free_parsing(parsing);
				return 1;
			}
			index++;
		}
		i++;
	}
	if (str[index] == ' ' || str[index] == '\0') 
	{
		while (str[index] == ' ')
			index++;
	} 
	else 
	{
			printf("Error : Non-numeric character found\n");
			free_parsing(parsing);
			return (1);
	}
	return (0);
}

int parsing_rgbs_sky(char **text_file, t_parsing *parsing)
{
	int line_index;
	int r;
	int g;
	int b;

	line_index = 0;
	while (text_file[line_index] != NULL) 
	{
		if (strncmp(text_file[line_index], "C ", 2) == 0) 
		{                 
			if (parse_rgb(text_file[line_index], &r, &g, &b, parsing) == 0) 
			{
				if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
				{
					parsing->sky_value_1 = r;
					parsing->sky_value_2 = g;
					parsing->sky_value_3 = b;
					parsing->ceiling_color = rgb_to_hex_sky(parsing);
					return (0);
				}
				
			}
		}
		line_index++;
	}
  
	printf("Error : sky values are incorrect\n");
	free_parsing(parsing);
	return (1);
}

int parsing_rgbs_floor(char **text_file, t_parsing *parsing)
{
	int line_index;
	int r;
	int g;
	int b;
	
	line_index = 0;
	while (text_file[line_index] != NULL) 
	{
		if (strncmp(text_file[line_index], "F ", 2) == 0) 
		{
			if (parse_rgb(text_file[line_index], &r, &g, &b, parsing) == 0) 
			{
				if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
				{
					parsing->floor_value_1 = r;
					parsing->floor_value_2 = g;
					parsing->floor_value_3 = b;
					parsing->floor_color = rgb_to_hex_floor(parsing);
					return (0);
				}
			}
		}
		line_index++;
	}
	printf("Error : floor values are incorrect\n");
	free_parsing(parsing);
	exit (1);
	return 1;
}
