/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_text_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:07:45 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 16:32:54 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_process(t_parsing *parsing, int fd)
{
	printf("Error: malloc failed.\n");
	free_gnl(fd, parsing->line);
	free_parsing(parsing);
}

char	*ft_strdup(const char *s)
{
	char	*sortie;
	int		size;
	int		i;

	i = 0;
	size = ft_strlen(s);
	sortie = (char *)malloc(sizeof(char) * (size + 1));
	if (!sortie)
		return (NULL);
	while (s[i])
	{
		sortie[i] = s[i];
		i++;
	}
	sortie[i] = '\0';
	return (sortie);
}
