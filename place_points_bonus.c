/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_points_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:17:44 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/27 18:22:11 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

//il faut envoyer des points dans l'ecran
//vector
//floats
//ligne droite ?
//a tester avec bomba.fdf pour opti
//division par 0 ?
//ligne de 2 de long
static void	draw_line(void *mlx, void *img, t_point start, t_point end)
{
	t_fpoint	delta;
	t_fpoint	inc;
	t_fpoint	pos;
	float		steps;
	float		i;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	if (fabsf(delta.x) > fabsf(delta.y))
		steps = fabsf(delta.x);
	else
		steps = fabsf(delta.y);
	inc.x = delta.x / steps;
	inc.y = delta.y / steps;
	pos.x = start.x;
	pos.y = start.y;
	i = 0.0f;
	while (i < steps)
	{
		mlx_set_image_pixel(mlx, img, pos.x, pos.y, 0xFEEDFACE);
		pos.x += inc.x;
		pos.y += inc.y;
		i += 1.0f;
	}
}

static void	draw_half(t_mlx mlx, t_points points, t_win winfo)
{
	size_t	i;
	size_t	j;
	t_point	start;
	t_point	end;

	i = 0;
	while (i < points.wid)
	{
		j = 0;
		start.x = (float)i * winfo.scale * HALF_S + winfo.xoffset;
		start.y = -(TWOTHIRD_S * (float)points.co[i] - SIXTH_S
				* (float)i) * winfo.scale + winfo.yoffset;
		j = 1;
		while (j < points.hei)
		{
			end.x = ((float)i - j) * winfo.scale * HALF_S + winfo.xoffset;
			end.y = -(TWOTHIRD_S * (float)points.co[j * points.wid + i]
					- SIXTH_S * (float)(i + j)) * winfo.scale + winfo.yoffset;
			draw_line(mlx.mlx, mlx.img, start, end);
			start = end;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
}

void	place_points(t_mlx mlx, t_points points, t_win winfo)
{
	size_t	i;
	size_t	j;
	t_point	start;
	t_point	end;

	i = -1;
	while (++i < points.hei)
	{
		start.x = -(float)i * winfo.scale * HALF_S + winfo.xoffset;
		start.y = -(TWOTHIRD_S * (float)points.co[i * points.wid] - SIXTH_S
				* (float)i) * winfo.scale + winfo.yoffset;
		j = 1;
		while (j < points.wid)
		{
			end.x = ((float)j - i) * winfo.scale * HALF_S + winfo.xoffset;
			end.y = -(TWOTHIRD_S * (float)points.co[i * points.wid + j]
					- SIXTH_S * (float)(i + j)) * winfo.scale + winfo.yoffset;
			draw_line(mlx.mlx, mlx.img, start, end);
			start = end;
			j++;
		}
	}
	draw_half(mlx, points, winfo);
}
