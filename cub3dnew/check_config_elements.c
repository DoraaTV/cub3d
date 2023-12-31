/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:56:52 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 13:48:30 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	nbr_texture_value(const char *prefix, t_parsing *parsing)
{
	int		i;
	int		count;
	size_t	prefix_length;

	i = 0;
	count = 0;
	prefix_length = strlen(prefix);
	while (i < parsing->config_count)
	{
		if (strncmp(parsing->config_elements[i], prefix, prefix_length) == 0)
		{
			count++;
			if (count > 1)
			{
				printf("Error: Structure '%s' appears more than once\n", prefix);
				free_parsing(parsing);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	parsing_rgbs(char **text_file, t_parsing *parsing)
{
	if (nbr_texture_value("NO ", parsing)
		|| nbr_texture_value("SO ", parsing)
		|| nbr_texture_value("WE ", parsing)
		|| nbr_texture_value("EA ", parsing) || nbr_texture_value("S ", parsing)
		|| nbr_texture_value("F ", parsing) || nbr_texture_value("C ", parsing))
		return (1);
	if (parsing_rgbs_floor(text_file, parsing) == 1)
		return (1);
	if (parsing_rgbs_sky(text_file, parsing) == 1)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;	

	i = 0;
	diff = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
		{
			diff = (unsigned char)s1[i] - (unsigned char)s2[i];
			return (diff);
		}
		i++;
	}
	return (diff);
}

int	extension_compare(const char *text_file, const char *extension)
{
	if (ft_strncmp(text_file + (ft_strlen(text_file) - 4), extension, 4) != 0)
		return (1);
	return (0);
}

int	check_texture_value(char **text_file
	, char *name_texture, t_parsing *parsing)
{
	(void)name_texture;
	if (extension_compare(*text_file, ".xpm") == 1)
	{
		printf("Error: The file must have only the .xpm extension\n");
		free_parsing(parsing);
		exit(1);
	}
	return (0);
}
