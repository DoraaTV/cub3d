/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:14:15 by thrio             #+#    #+#             */
/*   Updated: 2023/12/13 16:41:39 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free2(t_data *s);

int	ft_close(t_data *s)
{
	ft_free(s);
	return (0);
}

int	ft_init_textures(t_data *s)
{
	s->texture[0].img = mlx_xpm_file_to_image(s->mlx,
			s->parsing.no_txt, &s->texture[0].width,
			&s->texture[0].height);
	s->texture[1].img = mlx_xpm_file_to_image(s->mlx,
			s->parsing.so_txt, &s->texture[1].width,
			&s->texture[1].height);
	s->texture[2].img = mlx_xpm_file_to_image(s->mlx,
			s->parsing.we_txt, &s->texture[2].width,
			&s->texture[2].height);
	s->texture[3].img = mlx_xpm_file_to_image(s->mlx,
			s->parsing.ea_txt, &s->texture[3].width,
			&s->texture[3].height);
	if (!s->texture[0].img || !s->texture[1].img
		|| !s->texture[2].img || !s->texture[3].img)
		ft_free2(s);
	s->texture[0].addr = mlx_get_data_addr(s->texture[0].img,
			&s->texture[0].bpp, &s->texture[0].line_l, &s->texture[0].endian);
	s->texture[1].addr = mlx_get_data_addr(s->texture[1].img,
			&s->texture[1].bpp, &s->texture[1].line_l, &s->texture[1].endian);
	s->texture[2].addr = mlx_get_data_addr(s->texture[2].img,
			&s->texture[2].bpp, &s->texture[2].line_l, &s->texture[2].endian);
	s->texture[3].addr = mlx_get_data_addr(s->texture[3].img,
			&s->texture[3].bpp, &s->texture[3].line_l, &s->texture[3].endian);
	return (1);
}

void	ft_free2(t_data *s)
{
	int	i;

	i = 0;
	ft_free_txt(s, i);
	mlx_destroy_display(s->mlx);
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
	free(s->mlx);
	exit (0);
}

void	ft_free_txt(t_data *s, int i)
{
	int		checker;
	char	*texture;

	texture = NULL;
	checker = 0;
	while (i < 4)
	{
		if (s->texture[i].img != NULL)
			mlx_destroy_image(s->mlx, s->texture[i].img);
		else if (checker == 0 && s->texture[i].img == NULL)
		{
			texture = ft_check_file(texture, s, i);
			printf("Error: The file %s can't be opened\n", texture);
			checker = 1;
		}
		i++;
	}
	free(s->parsing.so_txt);
	free(s->parsing.we_txt);
	free(s->parsing.no_txt);
	free(s->parsing.ea_txt);
	free(s->parsing.s_texture_value);
	free(s->texture);
}

void	ft_free(t_data *s)
{
	int	i;

	i = 0;
	ft_free_txt(s, i);
	mlx_destroy_image(s->mlx, s->img.img);
	mlx_destroy_window(s->mlx, s->win);
	mlx_destroy_display(s->mlx);
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
	free(s->mlx);
	exit (0);
}
