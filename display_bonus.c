/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/12 17:27:54 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static inline void	key_hook_more(int key, t_data *data)
{
	if (key == SDL_SCANCODE_LCTRL)
		data->keydown |= CTRL;
	else if (key == SDL_SCANCODE_C || key == SDL_SCANCODE_KP_ENTER)
	{
		data->win.cnum = (data->win.cnum + 1) % NCOLOR;
		data->win.color = data->color[data->win.cnum];
		data->keydown |= RENDER;
	}
	else if (key >= 30 && key <= 39)
	{
		if (data->keydown & CTRL)
			manage_win(data, key - 30, 1);
		else
		{
			manage_win(data, key - 30, 0);
			data->keydown |= RENDER;
		}
	}
	else if (key == SDL_SCANCODE_SPACE)
		data->keydown ^= ANIM;
}

static int	key_hook(int key, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if (key == SDL_SCANCODE_ESCAPE)
		mlx_loop_end(data->mlx.mlx);
	else if (key == SDL_SCANCODE_R || key == SDL_SCANCODE_KP_PERIOD)
	{
		init_win(&data->win, &data->points);
		data->keydown |= RENDER;
	}
	else if (key == SDL_SCANCODE_KP_PLUS || key == SDL_SCANCODE_F)
	{
		data->win.zscale *= ZOOM_F;
		data->keydown |= RENDER;
	}
	else if (key == SDL_SCANCODE_KP_MINUS || key == SDL_SCANCODE_V)
	{
		data->win.zscale *= ZOOM_B;
		data->keydown |= RENDER;
	}
	else if (key == SDL_SCANCODE_LSHIFT)
		data->keydown |= SHIFT;
	else
		key_hook_more(key, data);
	return (0);
}

static int	key_unhook(int key, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if (key == SDL_SCANCODE_LSHIFT)
		data->keydown &= ~SHIFT;
	if (key == SDL_SCANCODE_LCTRL)
		data->keydown &= ~CTRL;
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
	if (init_data(&data, &points) == 0)
	{
		mlx_set_fps_goal(data.mlx.mlx, FPS_CAP);
		mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_MOUSEWHEEL, &zoom, &data);
		mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_KEYDOWN, &key_hook, &data);
		mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_KEYUP, &key_unhook, &data);
		mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_MOUSEDOWN,
			&mouse_hook, &data);
		mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_MOUSEUP,
			&mouse_unhook, &data);
		mlx_on_event(data.mlx.mlx, data.mlx.win, MLX_WINDOW_EVENT,
			&win_hook, &data);
		mlx_loop_hook(data.mlx.mlx, &fdf_loop, &data);
		mlx_put_image_to_window(data.mlx.mlx, data.mlx.win, data.mlx.img, 0, 0);
		mlx_loop(data.mlx.mlx);
		mlx_destroy_image(data.mlx.mlx, data.mlx.img);
	}
	else
		put_error("epic malloc fail\n", 17, 1);
	free(data.points.co);
	free(data.pixels);
	free(data.pos);
}
