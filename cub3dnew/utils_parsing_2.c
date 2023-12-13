/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:26:05 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 16:43:22 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

int	free_init_window(t_data *s)
{
	int	i;

	i = 0;
	ft_free_txt(s, i);
	i = s->parsing.config_count;
	while (i < s->parsing.start_map)
	{
		free(s->parsing.map[i]);
		i++;
	}
	i = 0;
	while (i < s->parsing.map_count - s->parsing.ligne_vide)
	{
		if (s->parsing.map[i + s->parsing.start_map])
			free(s->parsing.map[i + s->parsing.start_map]);
		i++;
	}
	free(s->parsing.map);
	exit(1);
	return (1);
}

int	check_all_text(t_parsing *parsing)
{
	if (parsing->ea_txt == NULL)
	{
		printf("Error: EA texture allocation failed.\n");
		free_parsing(parsing);
	}
	if (parsing->no_txt == NULL)
	{
		printf("Error: NO texture allocation failed.\n");
		free_parsing(parsing);
	}
	if (parsing->so_txt == NULL)
	{
		printf("Error: SO texture allocation failed.\n");
		free_parsing(parsing);
	}
	if (parsing->we_txt == NULL)
	{
		printf("Error: WE texture allocation failed.\n");
		free_parsing(parsing);
	}
	return (0);
}
