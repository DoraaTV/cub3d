/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_text_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:57:22 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 16:11:15 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_empty_lines_after(char **lines, int start_index, int num_lines,
		int config_count)
{
	int	empty_line_count;
	int	i;

	i = start_index + 1;
	empty_line_count = 0;
	(void)config_count;
	while (i < num_lines)
	{
		if (lines[i][0] == '\0' || (lines[i][0] == '\n' && lines[i][1] == '\0'))
			empty_line_count++;
		i++;
	}
	return (empty_line_count);
}

int	check_map_section(t_parsing *parsing, int num_lines, int i, int j)
{
	int		sign_count;
	char	*line;

	sign_count = 0;
	while (++i < num_lines)
	{
		line = parsing->config_elements[i];
		j = -1;
		while (line[++j] != '\0')
		{
			if (ft_strncmp(&line[j], "C ", 2) == 0 || ft_strncmp(&line[j],
					"NO ", 3) == 0 || ft_strncmp(&line[j], "SO ", 3) == 0
				|| ft_strncmp(&line[j], "WE ", 3) == 0 || ft_strncmp(&line[j],
					"EA ", 3) == 0 || ft_strncmp(&line[j], "F ", 2) == 0)
				sign_count++;
			if (sign_count == 6)
			{
				parsing->ligne_vide = count_empty_lines_after(parsing->map, i,
						num_lines, parsing->config_count);
				parsing->start_map = parsing->ligne_vide + i + 1;
				return (0);
			}
		}
	}
	return (1);
}

int	open_file(const char *filename, int *fd)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
	{
		printf("Error: Failed to open the file\n");
		return (1);
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dest);
}

int	resize_and_copy(char ***array, int current_size, int new_size)
{
	char	**new_array;

	new_array = (char **)ft_calloc(new_size + 1, sizeof(char *));
	if (!new_array)
		return (1);
	ft_memcpy(new_array, *array, (current_size) * sizeof(char *));
	free(*array);
	*array = new_array;
	return (0);
}
