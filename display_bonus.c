/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/27 21:32:55 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	init_win(t_win *wininfo, t_points *points)
{
	float	wid;
	float	hei;
	float	scale;

	wid = (float)(points->wid + points->hei - 2) * HALF_S;
	hei = (points->max - points->min) * TWOTHIRD_S;
	if ((float)WID / wid < (float)HEI / hei)
		scale = (float)(WID - PAD) / wid;
	else
		scale = (float)(HEI - PAD) / hei;
	wininfo->xoffset = ((float)WID
			- ((float)points->wid - points->hei) * scale * HALF_S) / 2.0f;
	wininfo->yoffset = ((float)HEI
			+ (points->max + points->min) * TWOTHIRD_S * scale) / 2.0f;
	wininfo->wid = wid;
	wininfo->hei = hei;
	wininfo->scale = scale;
}

static int	key_hook(int key, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if (key == SDL_SCANCODE_ESCAPE)
		mlx_loop_end(data->mlx->mlx);
	else if (key == SDL_SCANCODE_R && fps(0, 0.0f) > MIN_FPS)
	{
		mlx_destroy_image(data->mlx->mlx, data->mlx->img);
		data->mlx->img = new_img(data);
		init_win(data->win, data->points);
		place_points(*data->mlx, *data->points, *data->win);
	}
	return (0);
}

static int	zoom(int key, void *data_)
{
	t_data	*data;
	t_point	mouse;

	data = data_;
	mlx_mouse_get_pos(data->mlx->mlx, (int *)&mouse.x, (int *)&mouse.y);
	if (key == 1)
	{
		data->win->xoffset += (data->win->xoffset - mouse.x) * ZOOM;
		data->win->yoffset += (data->win->yoffset - mouse.y) * ZOOM;
		data->win->scale *= ZOOM_F;
	}
	else if (key == 2)
	{
		data->win->xoffset -= (data->win->xoffset - mouse.x) * ZOOM;
		data->win->yoffset -= (data->win->yoffset - mouse.y) * ZOOM;
		data->win->scale *= ZOOM_B;
	}
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	data->mlx->img = new_img(data);
	place_points(*data->mlx, *data->points, *data->win);
	return (0);
}

void	display_grid(t_points points, void *mlx_, void *win)
{
	t_win	wininfo;
	t_mlx	mlx;
	t_data	data;

	init_win(&wininfo, &points);
	mlx = (t_mlx){mlx_, win, NULL};
	data = (t_data){&mlx, &points, &wininfo};
	mlx.img = new_img(&data);
	mlx_set_fps_goal(mlx.mlx, 60);
	place_points(mlx, points, wininfo);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_on_event(mlx.mlx, mlx.win, MLX_MOUSEWHEEL, &zoom, &data);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, &key_hook, &data);
	//mlx_on_event(mlx.mlx, mlx.win, MLX_MOUSEDOWN, &mouse_hook, &data);
	//mlx_on_event(mlx.mlx, mlx.win, MLX_MOUSEUP, &mouse_unhook, &data);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, &win_hook, mlx.mlx);
	mlx_loop_hook(mlx.mlx, &putfps, &mlx);
	mlx_string_put(mlx.mlx, mlx.win, 0, 10, 0xFFFFFF00, "fps:");
	mlx_loop(mlx.mlx);
	free(points.co);
	mlx_destroy_image(mlx.mlx, mlx.img);
}
