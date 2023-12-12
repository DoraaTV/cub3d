/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:13:55 by thrio             #+#    #+#             */
/*   Updated: 2023/12/12 15:01:03 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycast(t_data *s)
{
	int				x;
	float			dv;
	float			angle;
	static float	fov;

	fov = 60 * M_PI / 180;
	angle = s->player_direction - fov / 2;
	dv = fov / (WINDOW_WIDTH - 1);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		draw_line(s, x, ft_ray(s, angle) * cos(s->player_direction - angle));
		angle += dv;
		x++;
	}
}

void	draw_game(t_data *s)
{
	s->img.img = mlx_new_image(s->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	s->img.addr = mlx_get_data_addr(s->img.img,
			&s->img.bpp, &s->img.line_l, &s->img.endian);
	draw_floor_ceiling(s);
	ft_raycast(s);
	mlx_put_image_to_window(s->mlx, s->win, s->img.img, 0, 0);
}

int	init_var(t_data *s)
{
	int	i;

	i = -1;
	s->i = 0;
	s->txt_width = 0.0f;
	s->texture = (t_image *)malloc(sizeof(t_image) * 4);
	if (!s->texture)
		ft_close(s);
	while (++i < 4)
		s->texture[i].img = NULL;
	return (0);
}

void	init_window(t_data *s)
{
	s->mlx = mlx_init();
	if (!s->mlx)
		exit (1);
	ft_init_textures(s);
	s->win = mlx_new_window(s->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!s->win)
		exit (1);
}

void	ft_raycasting(t_data *s)
{
	if (init_var(s) == 1)
		exit (1);
	init_window(s);
	ft_find_player(s);
	draw_game(s);
	mlx_hook(s->win, 17, 0, &ft_close, s);
	mlx_hook(s->win, 2, 1L << 0, &ft_keys, s);
	mlx_loop(s->mlx);
}
