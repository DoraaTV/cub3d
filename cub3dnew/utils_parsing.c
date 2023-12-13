/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:30:48 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 15:24:27 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	mult;

	mult = nmemb * size;
	if (nmemb <= 0 || size <= 0)
		return (malloc(0));
	if (size != mult / nmemb)
		return (NULL);
	res = (char *)malloc(size * nmemb);
	if (!res)
		return (NULL);
	res = ft_memset(res, 0, nmemb * size);
	return (res);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	correct_number2(t_parsing *parsing, char current_char, char *player_chars)
{
	if (strchr(player_chars, current_char) == NULL)
	{
		if (current_char >= 'A' && current_char <= 'Z')
		{
			printf("Error : %c this direction does not exist\n",
				current_char);
			free_parsing(parsing);
			return (1);
		}
	}
	if ((current_char < '0' || current_char > '1')
		&& strchr(player_chars, current_char) == NULL
		&& current_char != ' ')
	{
		printf("Error: %c is not a correct number\n", current_char);
		free_parsing(parsing);
		return (1);
	}
	return (0);
}

void	correct_number3(t_parsing *parsing
	, char current_char, int start, char *player_chars)
{
	char	*line;
	int		i;

	line = parsing->map[start];
	i = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != '\0')
	{
		current_char = line[i];
		if (current_char >= 9 && current_char <= 13)
		{
			i++;
			continue ;
		}
		if (current_char == ' ')
			line[i] = '1';
		correct_number2(parsing, current_char, player_chars);
		i++;
	}
}

void	too_much_player(t_parsing *parsing, int *player_count, int start)
{
	char		*line;
	char		*player_chars;
	size_t		i;

	line = parsing->map[start];
	player_chars = "NSEW";
	i = 0;
	while (i < strlen(player_chars))
	{
		if (strchr(line, player_chars[i]) != NULL)
		{
			(*player_count)++;
			if (*player_count > 1)
			{
				printf("Error: There is more than one player on the map\n");
				free_parsing(parsing);
			}
		}
		i++;
	}
}
