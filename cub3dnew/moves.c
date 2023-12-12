/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:28:32 by thrio             #+#    #+#             */
/*   Updated: 2023/12/12 10:31:01 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_data *s, int direction)
{
	float	dist;
	float	dist_x;
	float	dist_y;
	float	angle;

	angle = s->player_direction + direction * M_PI / 2;
	dist_x = 0.1f * cos(angle);
	dist_y = 0.1f * sin(angle);
	dist = ft_ray(s, ft_sign(dist_y) * M_PI / 2);
	if (dist * dist < dist_y * dist_y)
		dist_y = 0.0f;
	dist = ft_ray(s, (1 - (ft_sign(dist_x) + 1) / 2) * M_PI);
	if (dist * dist < dist_x * dist_x)
		dist_x = 0.0f;
	dist = ft_ray(s, angle);
	if (dist * dist < dist_x * dist_x + dist_y * dist_y)
	{
		if (ft_sign(dist_y) * ft_sign(dist_x) != 0)
			dist_y = 0.0f;
	}
	s->player_x += dist_x;
	s->player_y += dist_y;
}

int	ft_keys(int key, t_data *s)
{
	if (s->win == NULL)
		return (0);
	if (key == XK_Escape || key == XK_q || key == XK_Q)
	{
		ft_close(s);
		exit (0);
	}
	if (key == 65362 || key == 119)
		ft_move(s, 0);
	else if (key == 65364 || key == 115)
		ft_move(s, 2);
	else if (key == 65361)
		s->player_direction -= 0.02f * M_PI;
	else if (key == 65363)
		s->player_direction += 0.02f * M_PI;
	else if (key == 100)
		ft_move(s, 1);
	else if (key == 97)
		ft_move(s, 3);
	else
		return (0);
	mlx_destroy_image(s->mlx, s->img.img);
	draw_game(s);
	return (1);
}
