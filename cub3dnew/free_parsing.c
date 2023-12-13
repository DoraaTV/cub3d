/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:25:00 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 14:31:31 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture(t_parsing *parsing)
{
	if (!parsing->so_txt)
		free(parsing->no_txt);
	else if (!parsing->we_txt)
	{
		free(parsing->no_txt);
		free(parsing->so_txt);
	}
	else if (!parsing->ea_txt)
	{
		free(parsing->no_txt);
		free(parsing->so_txt);
		free(parsing->we_txt);
	}
	else
	{
		free(parsing->no_txt);
		free(parsing->so_txt);
		free(parsing->we_txt);
		free(parsing->ea_txt);
	}
}

int	free_parsing2(t_parsing *parsing)
{
	int	i;

	i = -1;
	free_texture(parsing);
	while (++i < parsing->config_count)
		free(parsing->config_elements[i]);
	free(parsing->config_elements);
	free(parsing->map);
	exit(1);
	return (1);
}

int	free_parsing(t_parsing *parsing)
{
	int	i;

	i = -1;
	free_texture(parsing);
	while (++i < parsing->config_count)
		free(parsing->config_elements[i]);
	free(parsing->config_elements);
	i = 0;
	i = parsing->config_count;
	while (i < parsing->start_map)
	{
		free(parsing->map[i]);
		i++;
	}
	i = 0;
	while (i < parsing->map_count - parsing->ligne_vide)
	{
		if (parsing->map[i + parsing->start_map])
			free(parsing->map[i + parsing->start_map]);
		i++;
	}
	free(parsing->map);
	exit (1);
	return (0);
}
