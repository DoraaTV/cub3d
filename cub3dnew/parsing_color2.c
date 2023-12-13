/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:31:21 by madjogou          #+#    #+#             */
/*   Updated: 2023/12/13 17:20:41 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	passespace_or_printerror(char *str, int *index, t_parsing *parsing)
{
	if (str[*index] == ' ' || str[*index] == '\0')
	{
		while (str[*index] == ' ')
			(*index)++;
	}
	else
	{
		printf("Error : Non-numeric character found\n");
		free_parsing(parsing);
	}
}

int	check_rgb_value(char *str, int *index, t_parsing *parsing, int i)
{
	if (str[*index] != ',')
	{
		printf("Error : Incorrect separator character after %c.\n", "RGB"[i]);
		free_parsing(parsing);
	}
	(*index)++;
	return (0);
}

void	pass_space(char *str, int *index)
{
	while (str[*index] == ' ')
		(*index)++;
}

void	set_variables(t_parsing *parsing, int **values, int *r, int *g)
{
	values[0] = r;
	values[1] = g;
	values[2] = &parsing->b;
}

int	parse_rgb(char *str, int *r, int *g, t_parsing *parsing)
{
	int	index;
	int	*values[3];
	int	i;

	set_variables(parsing, values, r, g);
	index = 2;
	i = -1;
	pass_space(str, &index);
	while (++i < 3)
	{
		if (str[index] == '-' || !is_digit(str[index]))
		{
			printf("Error : Bad value for %c (RGB)\n", "RGB"[i]);
			free_parsing(parsing);
			return (1);
		}
		*values[i] = atoi(str + index);
		while (isdigit(str[index]))
			index++;
		if (i < 2)
			check_rgb_value(str, &index, parsing, i);
	}
	passespace_or_printerror(str, &index, parsing);
	return (0);
}
