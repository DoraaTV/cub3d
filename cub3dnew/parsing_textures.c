/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:48:09 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 16:31:36 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ea_txt(char **text_file, t_parsing *parsing, int i)
{
	int	line_index;

	line_index = -1;
	while (text_file[++line_index] != NULL)
	{
		i = -1;
		while (text_file[line_index][++i] != '\0')
		{
			if (strncmp(&text_file[line_index][i], "EA ", 3) == 0)
			{
				if (check_texture_value(&text_file[line_index]
						, "EA", parsing) == 0)
				{
					i = i + 2;
					while (text_file[line_index][i] == ' ')
						i++;
					parsing->ea_txt = ft_strdup(&text_file[line_index][i]);
					return (0);
				}
			}
		}
	}
	printf("Error : EA texture value is invalid\n");
	return (free_parsing(parsing));
}

int	check_we_txt(char **text_file, t_parsing *parsing)
{
	int	line_index;
	int	i;

	line_index = -1;
	while (text_file[++line_index] != NULL)
	{
		i = -1;
		while (text_file[line_index][++i] != '\0')
		{
			if (ft_strncmp(&text_file[line_index][i], "WE ", 3) == 0)
			{
				if (check_texture_value(&text_file[line_index]
						, "WE", parsing) == 0)
				{
					i = i + 2;
					while (text_file[line_index][i] == ' ')
						i++;
					parsing->we_txt = strdup(&text_file[line_index][i]);
					return (0);
				}
			}
		}
	}
	printf("Error : WE texture value is invalid\n");
	return (free_parsing(parsing));
}

int	check_so_txt(char **text_file, t_parsing *parsing)
{
	int	line_index;
	int	i;

	line_index = -1;
	while (text_file[++line_index] != NULL)
	{
		i = -1;
		while (text_file[line_index][++i] != '\0')
		{
			if (strncmp(&text_file[line_index][i], "SO ", 3) == 0)
			{
				if (check_texture_value(&text_file[line_index]
						, "SO", parsing) == 0)
				{
					i = i + 2;
					while (text_file[line_index][i] == ' ')
						i++;
					parsing->so_txt = ft_strdup(&text_file[line_index][i]);
					return (0);
				}
			}
		}
	}
	printf("Error : SO texture value is invalid\n");
	return (free_parsing(parsing));
}

int	check_no_txt(char **text_file, t_parsing *parsing)
{
	int	line_index;
	int	i;

	line_index = -1;
	while (text_file[++line_index] != NULL)
	{
		i = 0;
		while (text_file[line_index][i] != '\0')
		{
			if (strncmp(text_file[line_index], "NO ", 3) == 0)
			{
				if (check_texture_value(&text_file[line_index]
						, "NO", parsing) == 0)
				{
					i = i + 2;
					while (text_file[line_index][i] == ' ')
						i++;
					parsing->no_txt = ft_strdup(&text_file[line_index][i]);
					return (0);
				}
			}
		}
	}
	printf("Error : NO texture value is invalid\n");
	return (free_parsing(parsing));
}

int	parsing_textures(char **text_file, t_parsing *parsing)
{
	if (check_no_txt(text_file, parsing) == 1)
		return (1);
	if (check_so_txt(text_file, parsing) == 1)
		return (1);
	if (check_we_txt(text_file, parsing) == 1)
		return (1);
	if (check_ea_txt(text_file, parsing, 0) == 1)
		return (1);
	if (check_all_text(parsing) == 1)
		return (1);
	return (0);
}
