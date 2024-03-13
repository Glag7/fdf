/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:25:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/12 16:31:06 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

//space because mlx
static void	drawfps(t_mlx *mlx, char draw)
{
	static char	num[8] = "fps:    ";
	static int	color[9] = {RED, ORE, ORA, YEL, YGR, LGR, GRE, GRE, GRE};
	static int	frames = 0;

	frames += frames < 85;
	if (!draw)
		return ;
	mlx_string_put(mlx->mlx, mlx->win, 0, 10, 0xFF000000, num);
	if (frames > 9)
	{
		num[6] = 0;
		num[5] = frames % 10 + '0';
		num[4] = frames / 10 + '0';
		mlx_string_put(mlx->mlx, mlx->win, 0, 10, color[frames / 10], num);
		num[6] = ' ';
	}
	else
	{
		num[5] = 0;
		num[4] = frames % 10 + '0';
		mlx_string_put(mlx->mlx, mlx->win, 0, 10, RED, num);
		num[5] = ' ';
	}
	frames = 0;
}

static void	render(t_data *data, t_mlx mlx, int *pixels,
	unsigned char *keydown)
{
	int	i;
	int	j;

	ft_bzero(pixels, WID * HEI * sizeof(int));
	place_points(data->points, data->win, pixels, data->pos);
	i = 0;
	while (i < HEI)
	{
		j = 0;
		while (j < WID)
		{
			mlx_set_image_pixel(mlx.mlx, mlx.img, j, i, pixels[i * WID + j]);
			j++;
		}
		i++;
	}
	*keydown &= ~RENDER;
}

static inline void	do_anim(t_data *data,
	struct timespec old, struct timespec new)
{
	float				delta;
	float				offset;

	delta = (new.tv_nsec - old.tv_nsec) * 1e-9f;
	delta += new.tv_sec - old.tv_sec;
	data->win.yaw -= delta * 3e-1;
	offset = data->win.scale / data->og_scale
		* 1.5e3f * delta * (sin(2. * (new.tv_sec + new.tv_nsec * 1e-9))
			- sin(2. * (old.tv_sec + old.tv_nsec * 1e-9)));
	data->win.yoffset += offset;
	compute_mat(data, data->win.rotmat);
	data->keydown |= RENDER;
}

static inline void	manage_mouse(t_data *data)
{
	t_point	tmp;

	data->mouseold = data->mouse;
	mlx_mouse_get_pos(data->mlx.mlx, (int *)&tmp.x, (int *)&tmp.y);
	data->mouse = tmp;
	tmp.x = data->mouse.x - data->mouseold.x;
	tmp.y = data->mouse.y - data->mouseold.y;
	if (data->keydown & LMB)
	{
		data->win.xoffset += tmp.x;
		data->win.yoffset += tmp.y;
		if (tmp.x || tmp.y)
			data->keydown |= RENDER;
	}
	if (data->keydown & RMB)
		update_rot(data, tmp);
}

int	fdf_loop(void *data_)
{
	static struct timespec	past = {0, 0};
	struct timespec			curr;
	t_data					*data;

	data = data_;
	manage_mouse(data);
	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	if (data->keydown & ANIM)
		do_anim(data, past, curr);
	if (data->keydown & RENDER)
		render(data, data->mlx, data->pixels, &data->keydown);
	drawfps(&data->mlx, past.tv_sec < curr.tv_sec);
	past = curr;
	return (0);
}
