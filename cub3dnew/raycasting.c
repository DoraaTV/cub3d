/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:22:45 by thrio             #+#    #+#             */
/*   Updated: 2023/12/12 15:01:03 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	save_color(t_data *s, float dist, int color_idx, float wall_hit)
{
	s->i = color_idx;
	s->txt_width = wall_hit;
	return (dist);
}

static void	ft_ray2(t_data *s, t_ray *ray)
{
	if (ray->step_x != 0)
	{
		ray->vert_y = s->player_y + ray->dir_y
			/ ray->dir_x * (ray->vert_x - s->player_x);
		ray->vert_dist = sqrt(pow(s->player_x - ray->vert_x, 2.0)
				+ pow(s->player_y - ray->vert_y, 2.0));
		ray->vert_w = ray->vert_y - (int)ray->vert_y;
		if (ray->step_x > 0)
			ray->vert_w = 1 - ray->vert_w;
	}
	else
		ray->vert_dist = INFINITY;
	if (ray->step_y != 0)
	{
		ray->horz_x = s->player_x + ray->dir_x
			/ ray->dir_y * (ray->horz_y - s->player_y);
		ray->horz_dist = sqrt(pow(s->player_x - ray->horz_x, 2.0)
				+ pow(s->player_y - ray->horz_y, 2.0));
		ray->horz_w = ray->horz_x - (int)ray->horz_x;
		if (ray->step_y > 0)
			ray->horz_w = 1 - ray->horz_w;
	}
	else
		ray->horz_dist = INFINITY;
}

static void	init_ray(t_data *s, t_ray *ray, float angle)
{
	ray->dir_x = cos(angle);
	ray->dir_y = sin(angle);
	ray->step_x = ft_sign(ray->dir_x);
	ray->step_y = ft_sign(ray->dir_y);
	ray->vert_x = (int)s->player_x;
	ray->horz_w = 0;
	ray->horz_x = 0;
	ray->vert_w = 0;
	ray->vert_y = 0;
	if (ray->step_x > 0)
		ray->vert_x += 1.0f;
	ray->horz_y = (int)s->player_y;
	if (ray->step_y > 0)
		ray->horz_y += 1.0f;
}

float	ft_ray(t_data *s, float angle)
{
	t_ray	ray;

	init_ray(s, &ray, angle);
	while (1)
	{
		ft_ray2(s, &ray);
		if (ray.vert_dist < ray.horz_dist)
		{
			if (s->parsing.map[(int)ray.vert_y + s->parsing.start_map]
				[(int)ray.vert_x + (ray.step_x - 1) / 2] == '1')
				return (save_color(s, ray.vert_dist,
						ray.step_x + 1, ray.vert_w));
			else
				ray.vert_x += ray.step_x;
		}
		else
		{
			if (s->parsing.map[((int)ray.horz_y + (ray.step_y - 1) / 2)
					+ s->parsing.start_map][(int)ray.horz_x] == '1')
				return (save_color(s, ray.horz_dist,
						ray.step_y + 2, ray.horz_w));
			else
				ray.horz_y += ray.step_y;
		}
	}
}
