/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_elements2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:24:45 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 13:09:34 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_first_wall(t_parsing *parsing)
{
	int		i;
	char	*map_line;
	int		j;

	j = 0;
	i = parsing->start_map;
	map_line = parsing->map[i];
	while (map_line[j] != '\0')
	{
		if (map_line[j] != '1' && map_line[j] != ' ')
		{
			printf("Error: First wall is not closed\n");
			free_parsing(parsing);
			return (1);
		}
		j++;
	}
	return (0);
}

int	map_closed(t_parsing *parsing)
{
	if (check_first_wall(parsing) == 1)
		return (1);
	if (check_last_wall(parsing) == 1)
		return (1);
	if (check_all_wall_closed(parsing, parsing->start_map + 1) == 1)
		return (1);
	return (0);
}

int	map_less_3_lines(t_parsing *parsing)
{
	int	num_lines;
	int	start;

	start = parsing->start_map;
	num_lines = 0;
	while (start < parsing->num_lines)
	{
		num_lines++;
		start++;
	}
	if (num_lines <= 3)
	{
		printf("Error: The map has less than 3 lines.\n");
		free_parsing(parsing);
		return (1);
	}
	return (0);
}

int	check_nbr_player(t_parsing *parsing)
{
	int		player_count;
	int		start;

	player_count = 0;
	start = parsing->start_map;
	while (start < parsing->num_lines)
	{
		too_much_player(parsing, &player_count, start);
		start++;
	}
	if (player_count == 0)
	{
		printf("Error: There is no player on the map\n");
		free_parsing(parsing);
		return (1);
	}
	return (0);
}
