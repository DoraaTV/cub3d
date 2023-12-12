/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thrio <thrio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:30:08 by thrio             #+#    #+#             */
/*   Updated: 2023/12/12 15:01:03 by thrio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_data *s)
{
	unsigned int	*dst;
	unsigned int	i;

	dst = (unsigned int *)s->img.addr;
	i = WINDOW_WIDTH * WINDOW_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = s->parsing.ceiling_color;
	i = WINDOW_WIDTH * WINDOW_HEIGHT / 2 + 1;
	while (--i > 0)
		*dst++ = s->parsing.floor_color;
}

void	draw_line(t_data *s, int w, float dist)
{
	unsigned int	*dst;
	unsigned int	*src;
	unsigned int	h;
	float			src_factor;
	float			dst_shift;

	h = (float)WINDOW_HEIGHT / dist;
	src_factor = 0.0f;
	dst_shift = (float)s->texture[s->i].height / h;
	if (h > WINDOW_HEIGHT)
	{
		src_factor = 0.5f * (h - WINDOW_HEIGHT) * dst_shift;
		h = WINDOW_HEIGHT;
	}
	src = (unsigned int *)s->texture[s->i].addr;
	src += (int)((float)s->txt_width * s->texture[s->i].width);
	dst = (unsigned int *)s->img.addr + w + (WINDOW_HEIGHT - h) / 2
		* WINDOW_WIDTH;
	while (h-- > 0)
	{
		*dst = *(src + ((int)src_factor) * s->texture[s->i].width);
		dst += WINDOW_WIDTH;
		src_factor += dst_shift;
	}
}
