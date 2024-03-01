/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:25:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/01 19:22:57 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

#define RED 0xFFFF0000
#define ORE 0xFFFF3300
#define ORA 0xFFFF7700
#define YEL 0xFFFFFF00
#define YGR 0xFF77FF00
#define LGR 0xFF11FF00
#define GRE 0xFF00FF00

//space because mlx
static inline void	drawfps(t_mlx *mlx, int todraw)
{
	static char	num[8] = "fps:    ";
	static int	color[9] = {RED, ORE, ORA, YEL, YGR, LGR, GRE, GRE, GRE};

	mlx_string_put(mlx->mlx, mlx->win, 0, 10, 0xFF000000, num);
	if (todraw > 9)
	{
		num[6] = 0;
		num[5] = todraw % 10 + '0';
		num[4] = todraw / 10 + '0';
		mlx_string_put(mlx->mlx, mlx->win, 0, 10, color[todraw / 10], num);
		num[6] = ' ';
	}
	else
	{
		num[5] = 0;
		num[4] = todraw % 10 + '0';
		mlx_string_put(mlx->mlx, mlx->win, 0, 10, RED, num);
		num[5] = ' ';
	}
}

static void	putfps(t_data *data)
{
	static struct timespec	past = {0, 0};
	struct timespec			curr;
	static int				frames = 0;

	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	data->fps = 1.0f / ((float)(curr.tv_sec - past.tv_sec)
			+ (float)(curr.tv_nsec - past.tv_nsec) *1e-9);
	frames++;
	if (curr.tv_sec > past.tv_sec)
	{
		drawfps(&data->mlx, frames);
		frames = 0;
	}
	past = curr;
}

//do NOT remove tmp (padding)
int	fdf_loop(void *data_)
{
	t_data	*data;
	t_point	tmp;

	data = data_;
	data->mouseold = data->mouse;
	mlx_mouse_get_pos(data->mlx.mlx, (int *)&tmp.x, (int *)&tmp.y);
	data->mouse = tmp;
	if (data->keydown & LMB && data->fps > MIN_FPS)
	{
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
		data->mlx.img = new_img(data);
		data->win.xoffset += data->mouse.x - data->mouseold.x;
		data->win.yoffset += data->mouse.y - data->mouseold.y;
		place_points(data->mlx, data->points, data->win);
	}
	else if (data->keydown & RMB && data->fps > MIN_FPS) //else ?
	{
	}
	putfps(data);
	return (0);
}
