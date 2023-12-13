/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:44:10 by madjogou          #+#    #+#             */
/*   Updated: 2023/12/13 11:10:55 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	good_name_file_cub(int ac, char **av)
{
	char	*name_file;

	name_file = av[1];
	if (ac != 2)
	{
		if (ac < 2)
			printf("Error : insufficient number of arguments\n");
		else
			printf("Error : too much of arguments\n");
		return (1);
	}
	if (strstr(name_file, ".cub") == NULL
		|| strcmp(name_file + strlen(name_file) - 4, ".cub") != 0)
	{
		printf("Error : The file must have the .cub extension\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (good_name_file_cub(ac, av) == 1)
		return (1);
	if (parsing(av[1], &data) == 1)
		return (1);
	i = -1;
	while (++i < data.parsing.config_count)
		free(data.parsing.config_elements[i]);
	free(data.parsing.config_elements);
	ft_raycasting(&data);
	return (0);
}
