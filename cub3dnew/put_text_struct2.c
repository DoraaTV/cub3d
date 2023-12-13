/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_text_struct2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:55:20 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 16:17:40 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_line(t_parsing *parsing, int *config_size, int *msize, int fd)
{
	parsing->buffer[parsing->line_index] = '\0';
	if (check_map_section(parsing, *parsing->n_ptr, -1, -1) == 1)
	{
		if (*parsing->n_ptr >= *config_size)
		{
			(*config_size) *= 2;
			if (resize_and_copy(&parsing->config_elements, *parsing->n_ptr,
					*config_size) == 1)
				ft_free_process(parsing, fd);
		}
		parsing->config_elements[*parsing->n_ptr] = ft_strdup(parsing->buffer);
		parsing->config_count++;
	}
	else
	{
		if (*parsing->n_ptr >= *msize)
		{
			(*msize) *= 2;
			if (resize_and_copy(&parsing->map, *parsing->n_ptr, *msize) == 1)
				ft_free_process(parsing, fd);
		}
		parsing->map[*parsing->n_ptr] = ft_strdup(parsing->buffer);
		parsing->map_count++;
	}
	(*parsing->n_ptr)++;
}

int	init_read_variables(t_parsing *parsing, int fd)
{
	parsing->num_lines = 0;
	parsing->n_ptr = &parsing->num_lines;
	parsing->line_index = 0;
	parsing->map = (char **)ft_calloc(parsing->config_size + 1, sizeof(char *));
	parsing->config_elements = (char **)ft_calloc(parsing->config_size + 1,
			sizeof(char *));
	parsing->line = get_next_line(fd);
	if (!parsing->map || !parsing->config_elements || !parsing->line)
		return (1);
	return (0);
}

void	put_text_utils(t_parsing *parsing, int fd, char *current_char, int *i)
{
	while (*current_char != '\0')
	{
		if (*current_char == '\n')
		{
			process_line(parsing, &parsing->config_size,
				&parsing->config_size, fd);
			parsing->line_index = 0;
		}
		else if (parsing->line_index < MAX_LINE_LENGTH - 1)
		{
			parsing->buffer[parsing->line_index] = *current_char;
			parsing->line_index++;
		}
		else
		{
			printf("Error: Line too long\n");
			free_gnl(fd, parsing->line);
			free_parsing(parsing);
		}
		(*i)++;
		*current_char = parsing->line[*i];
	}
}

int	put_text_end(t_parsing *parsing, int fd)
{
	if (parsing->config_count < 8)
		parsing->config_elements[parsing->config_count + 1] = NULL;
	else
		parsing->config_elements[parsing->config_count] = NULL;
	if (parsing->line_index > 0)
		process_line(parsing, &parsing->config_size, &parsing->config_size, fd);
	close(fd);
	return (0);
}

int	put_text_struct(char *file_cub3d_name, t_parsing *parsing)
{
	int		fd;
	int		i;
	char	current_char;

	parsing->counter2 = 0;
	if (open_file(file_cub3d_name, &fd) == 1)
		return (1);
	if (init_read_variables(parsing, fd) == 1)
		return (1);
	while (parsing->line)
	{
		i = 0;
		current_char = parsing->line[i];
		if (current_char && parsing->config_count == 6
			&& parsing->counter2 > parsing->counter - 1 && current_char == '\n')
		{
			free_gnl(fd, parsing->line);
			free_parsing(parsing);
		}
		put_text_utils(parsing, fd, &current_char, &i);
		free(parsing->line);
		parsing->line = get_next_line(fd);
		parsing->counter2++;
	}
	return (put_text_end(parsing, fd));
}
