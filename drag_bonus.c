/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:43:16 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/27 21:30:03 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	drag(void *data_)
{
	static	t_point	old = {0, 0};
	t_point		mouse;
	t_data	*data;

	data = (t_data *)data_;
	mlx_mouse_get_pos(data->mlx->mlx, (int *)&mouse.x, (int *)&mouse.y);
	data->win->xoffset += mouse.x - old.x;
	data->win->yoffset += mouse.y - old.y;
	old = mouse;
	return (0);
}
/*
int	mouse_hook(int key, void *data_)//cacher souris ?
{
	t_data	*data;

	data = (t_data *)data_;
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
	data->mlx->img = new_img(data);
	if (key == 1)
	{
		drag(data->win, data->mlx);
		place_points(*data->mlx, *data->points, *data->win);
	}
	//else if key == 3 rotate
	return (0);
}*/

int	mouse_unhook(int key, void *data_)
{
}
