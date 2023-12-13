/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_text_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:57:22 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 10:53:51 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_empty_lines_after(char **lines, int start_index, int num_lines, int config_count) 
{
	int empty_line_count;
	int i;
	
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

int	check_map_section(t_parsing *parsing, int num_lines) 
{
	int		i;
	int		j;
	int		nb_ligne_vide;
	int		sign_count;
	char	*line;
	
	sign_count = 0;
	i = 0;
	while (i < num_lines) 
	{
		line = parsing->config_elements[i];
		j = 0;
		while (line[j] != '\0') 
		{   
			if (ft_strncmp(&line[j], "C ", 2) == 0
					|| ft_strncmp(&line[j], "NO ", 3) == 0
					|| ft_strncmp(&line[j], "SO ", 3) == 0
					|| ft_strncmp(&line[j], "WE ", 3) == 0
					|| ft_strncmp(&line[j], "EA ", 3) == 0
					|| ft_strncmp(&line[j], "F ", 2) == 0)
				sign_count++;
			if (sign_count == 6)
			{
				nb_ligne_vide = count_empty_lines_after(parsing->map, i, num_lines, parsing->config_count);
				parsing->ligne_vide = nb_ligne_vide;
				parsing->start_map = nb_ligne_vide + i + 1;

				return (0);
			}
			j++;
		}
		i++;  
	}
	return (1);
}

int	open_file(const char *filename, int *fd) 
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0) 
	{
		printf("Error: Failed to open the file\n");
		return 1;
	}
	return 0;
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

void	resize_and_copy(char ***array, int current_size, int new_size) 
{
	char **new_array;
	
	new_array = (char **)calloc(new_size + 1, sizeof(char * ));
	if (!new_array)
		return ;
	ft_memcpy(new_array, *array, (current_size) * sizeof(char *));
	free(*array);
	*array = new_array;
}

void	process_line(t_parsing *parsing, int *config_size, int *map_size) 
{
	parsing->buffer[parsing->line_index] = '\0';
	if (check_map_section(parsing, *parsing->num_lines_ptr) == 1) 
	{   
		if (*parsing->num_lines_ptr >= *config_size) 
		{
			(*config_size) *= 2;
			resize_and_copy(&parsing->config_elements, *parsing->num_lines_ptr, *config_size);   
		}
		parsing->config_elements[*parsing->num_lines_ptr] = strdup(parsing->buffer);
		parsing->config_count++;
	} 
	else 
	{
		if (*parsing->num_lines_ptr >= *map_size) 
		{
			(*map_size) *= 2;
			resize_and_copy(&parsing->map, *parsing->num_lines_ptr, *map_size);
		}
		parsing->map[*parsing->num_lines_ptr] = strdup(parsing->buffer);
		parsing->map_count++;
	}
	(*parsing->num_lines_ptr)++;
}

void	init_read_variables(t_parsing *parsing)
{
	parsing->num_lines = 0;
	parsing->num_lines_ptr = &parsing->num_lines;
	parsing->line_index = 0;
}

int	put_text_struct(char *file_cub3d_name, t_parsing *parsing) 
{
	char	*line;
	int		fd;
	int		i;
	char	current_char;

	parsing->counter2 = 0;
	if (open_file(file_cub3d_name, &fd) == 1) 
			return 1;
	init_read_variables(parsing);
	parsing->map = (char **)calloc(parsing->config_size + 1, sizeof(char *));
	parsing->config_elements = (char **)calloc(parsing->config_size + 1, sizeof(char *));
	line = get_next_line(fd);
	if (!line)
		return (1);
	while (line)
	{
		i = 0;
		current_char = line[i];
		if (current_char && parsing->config_count == 6 && parsing->counter2 > parsing->counter - 1 && current_char == '\n')
		{
				free(line);
				line = get_next_line(fd);
				while (line)
				{
					free(line);
					line = get_next_line(fd);
				}
				free(line);
				free_parsing(parsing);
		}
		while (current_char != '\0') 
		{
			if (current_char == '\n') 
			{
				process_line(parsing, &parsing->config_size, &parsing->config_size);
				parsing->line_index = 0;
			}  
			else if (parsing->line_index < MAX_LINE_LENGTH - 1) 
			{
				parsing->buffer[parsing->line_index] = current_char;
				parsing->line_index++;
			} 
			else 
			{
				printf("Error: Line too long\n");
				free(line);
				line = get_next_line(fd);
				while (line)
				{
					free(line);
					line = get_next_line(fd);
				}
				free(line);
				free_parsing(parsing);
				return (1);
			}
			i++;
			current_char = line[i];
		}
		free(line);
		line = get_next_line(fd);
		parsing->counter2++;
	}
	if (parsing->config_count < 8)
		parsing->config_elements[parsing->config_count + 1] = NULL;
	else
		parsing->config_elements[parsing->config_count] = NULL;
	if (parsing->line_index > 0) 
		process_line(parsing, &parsing->config_size, &parsing->config_size);
	close(fd);
	return 0;
}
