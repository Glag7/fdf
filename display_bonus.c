/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/01 23:16:18 by glag             ###   ########.fr       */
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
	wininfo->zscale = 1.0f;
}

static int	key_hook(int key, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if (key == SDL_SCANCODE_ESCAPE)
		mlx_loop_end(data->mlx.mlx);
	else if (key == SDL_SCANCODE_KP_PERIOD)
	{
		init_win(&data->win, &data->points);
		data->keydown |= RENDER;
	}
	else if (key == SDL_SCANCODE_LSHIFT)
		data->keydown |= SHIFT;
	else if (key == SDL_SCANCODE_KP_PLUS)
	{
		data->win.zscale *= ZOOM_F;
		data->keydown |= RENDER;
	}
	else if (key == SDL_SCANCODE_KP_MINUS)
	{
		data->win.zscale *= ZOOM_B;
		data->keydown |= RENDER;
	}
	//couleurs
	//rotations numpad
	return (0);
}

static int	key_unhook(int key, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if (key == SDL_SCANCODE_LSHIFT)
		data->keydown &= ~SHIFT;
	return (0);
}

static int	zoom(int key, void *data_)
{
	t_data	*data;

	data = data_;
	if (key == 1)
	{
		data->win.xoffset += (data->win.xoffset - data->mouse.x) * ZOOM;
		data->win.yoffset += (data->win.yoffset - data->mouse.y) * ZOOM;
		data->win.scale *= ZOOM_F;
	}
	else if (key == 2)
	{
		data->win.xoffset -= (data->win.xoffset - data->mouse.x) * ZOOM;
		data->win.yoffset -= (data->win.yoffset - data->mouse.y) * ZOOM;
		data->win.scale *= ZOOM_B;
	}
	data->keydown |= RENDER;
	return (0);
}

void	display_grid(t_points points, void *mlx_, void *win)
{
	t_data	data;

	data.mlx = (t_mlx){mlx_, win, NULL};
	init_win(&data.win, &points);
	data.points = points;
	data.mouse = (t_point){0, 0};
	data.mouseold = (t_point){0, 0};
	data.keydown = 0;
	data.fps = 0.0f;
	data.mlx.img = new_img(&data);
	mlx_set_fps_goal(data.mlx.mlx, FPS_CAP);
	mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_MOUSEWHEEL, &zoom, &data);
	mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_KEYDOWN, &key_hook, &data);
	mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_KEYUP, &key_unhook, &data);
	mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_MOUSEDOWN, &mouse_hook, &data);
	mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_MOUSEUP, &mouse_unhook, &data);
	mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_WINDOW_EVENT, &win_hook, mlx_);
	mlx_loop_hook(data.mlx.mlx, &fdf_loop, &data);
	place_points(data.mlx, data.points, data.win);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.win, data.mlx.img, 0, 0);
	mlx_loop(data.mlx.mlx);
	free(data.points.co);
	mlx_destroy_image(data.mlx.mlx, data.mlx.img);
}
