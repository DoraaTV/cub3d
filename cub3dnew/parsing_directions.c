/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_directions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:10:30 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 13:12:17 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	direction_count(t_parsing *parsing, int i)
{
	int	destination_count;

	destination_count = 0;
	destination_count++;
	if (destination_count > 1)
	{
		printf("Error: Too much direction on the map\n");
		free_parsing(parsing);
		return (1);
	}
	i++;
	return (0);
}

int	check_nbr_directions(t_parsing *parsing)
{
	int		destination_count;
	int		start;
	char	*line;
	char	*destination_chars;
	size_t	i;

	destination_count = 0;
	start = parsing->start_map;
	while (start < parsing->num_lines)
	{
		line = parsing->map[start];
		destination_chars = "SWE";
		i = 0;
		while (i < strlen(destination_chars))
		{
			if (strchr(line, destination_chars[i]) != NULL)
			{
				direction_count(parsing, i);
			}
			i++;
		}
		start++;
	}
	return (0);
}
