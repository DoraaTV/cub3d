/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:57:13 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 16:58:28 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test(char *line, int *check, t_parsing *s, int *count)
{
	int	i;

	i = 0;
	(void)i;
	if (line[0] == '1' || line[0] == ' ')
	{
		if (line[0] == ' ')
		{
			while (line[i])
			{
				if (line[i] == '1')
				{
					s->counter = (*count);
					(*check) = 1;
				}
				i++;
			}
		}
		s->counter = *count;
		(*check) = 1;
	}
}

void	free_gnl(int fd, char *line)
{
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	ft_get_size(char *file_cub3d_name, t_parsing *s)
{
	int		fd;
	char	*line;
	int		check;
	int		count;

	check = 0;
	count = 0;
	fd = open(file_cub3d_name, O_RDONLY);
	if (fd < 2)
		return (1);
	line = get_next_line(fd);
	while (line && check == 0)
	{
		test(line, &check, s, &count);
		s->config_size++;
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free_gnl(fd, line);
	return (0);
}

void	init_struct(t_parsing	*parsing)
{
	parsing->floor_value_1 = -1;
	parsing->floor_value_2 = -1;
	parsing->floor_value_3 = -1;
	parsing->sky_value_1 = -1;
	parsing->sky_value_2 = -1;
	parsing->sky_value_3 = -1;
	parsing->b = 0;
	parsing->no_txt = NULL;
	parsing->we_txt = NULL;
	parsing->so_txt = NULL;
	parsing->ea_txt = NULL;
	parsing->s_texture_value = NULL;
	parsing->map = NULL;
	parsing->config_count = 0;
	parsing->sign_count = 0;
	parsing->config_size = 0;
	parsing->map_count = 0;
	parsing->start_map = 0;
	parsing->ligne_vide = 0;
	parsing->config_elements = NULL;
	parsing->copied_map = NULL;
	parsing->map_height = 0;
}

int	parsing(char *file_cub3d_name, t_data *data)
{
	t_parsing	*parsing;

	data->parsing.counter = 0;
	init_struct(&data->parsing);
	if (ft_get_size(file_cub3d_name, &data->parsing) == 1)
		return (1);
	if (data->parsing.counter < 6)
		return (1);
	parsing = &data->parsing;
	if (put_text_struct(file_cub3d_name, &data->parsing) == 1)
	{
		printf("Error : text cannot be put into structure\n");
		free_parsing(&data->parsing);
		return (1);
	}
	if (parsing_cub3d(parsing->config_elements, &data->parsing) == 1)
		return (1);
	return (0);
}
