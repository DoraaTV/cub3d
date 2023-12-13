/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:53:02 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 14:15:22 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	correct_number(t_parsing *parsing)
{
	int		start;
	char	current_char;

	current_char = 0;
	start = parsing->start_map - 1;
	while (++start < parsing->num_lines)
		correct_number3(parsing, current_char, start, "NSEW");
	return (0);
}

int	check_spaces(char c)
{
	if ((c > 9 && c < 13) || c == 32)
		return (1);
	return (0);
}

int	check_wall(char **strs, int i, int j)
{
	if (j > (int)ft_strlen(strs[i - 1])
		&& ft_strlen(strs[i - 1]) < ft_strlen(strs[i]))
		return (1);
	if (j > (int)ft_strlen(strs[i + 1])
		&& ft_strlen(strs[i + 1]) < ft_strlen(strs[i]))
		return (1);
	if (strs[i][j - 1] == 0 || check_spaces(strs[i][j - 1]))
		return (1);
	if (strs[i][j + 1] == 0 || check_spaces(strs[i][j + 1]))
		return (1);
	if (strs[i - 1][j] == 0 || check_spaces(strs[i - 1][j]))
		return (1);
	if (strs[i + 1][j] == 0 || check_spaces(strs[i + 1][j]))
		return (1);
	return (0);
}

int	check_all_wall_closed(t_parsing *parsing, int i)
{
	int		j;
	char	**map;

	map = parsing->map;
	while (i < parsing->num_lines)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '0' || map[i][j] == '2' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (check_wall(map, i, j) == 1)
				{
					printf("Error: The walls are not closed\n");
					free_parsing(parsing);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_last_wall(t_parsing *parsing)
{
	int		index_end;
	char	*map_line;
	int		j;

	index_end = parsing->start_map;
	while (index_end < parsing->num_lines)
		index_end++;
	index_end--;
	map_line = parsing->map[index_end];
	j = 0;
	while (map_line[j] != '\0')
	{
		if (map_line[j] != '1' && map_line[j] != ' ')
		{
			printf("Error: Last wall is not closed\n");
			free_parsing(parsing);
			return (1);
		}
		j++;
	}
	return (0);
}
