/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:57:16 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 14:13:14 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing_map_elements(char **text_file, t_parsing *parsing)
{
	(void)text_file;
	if (correct_number(parsing) == 1)
		return (1);
	if (map_closed(parsing) == 1)
		return (1);
	if (map_less_3_lines(parsing) == 1)
		return (1);
	if (check_nbr_player(parsing) == 1)
		return (1);
	if (check_nbr_directions(parsing) == 1)
		return (1);
	return (0);
}

int	check_config_elements(char **text_file, t_parsing *parsing)
{
	if (parsing_rgbs(text_file, parsing) == 1)
		return (1);
	if (parsing_textures(text_file, parsing) == 1)
		return (1);
	return (0);
}

int	parsing_cub3d(char **text_file, t_parsing *parsing)
{
	int	i;

	(void)text_file;
	i = 0;
	if (check_config_elements(parsing->config_elements, parsing) == 1)
		return (1);
	parsing->map[parsing->config_size] = NULL;
	if (parsing_map_elements(&parsing->map[i], parsing) == 1)
		return (1);
	return (0);
}
