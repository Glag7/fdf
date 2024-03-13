/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:06:22 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/12 14:11:37 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static inline void	init_shortcuts(t_data *data)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		manage_win(data, i, 1);
		i++;
	}
}

int	init_data(t_data *data, t_points *points)
{
	data->points = *points;
	data->pos = NULL;
	data->pixels = malloc(WID * HEI * sizeof(int));
	if (data->pixels == NULL)
		return (1);
	data->pos = malloc(points->wid * points->hei * sizeof(t_fpoint));
	if (data->pos == NULL)
		return (1);
	init_win(&data->win, points);
	data->og_scale = data->win.scale;
	data->mouse = (t_point){0, 0};
	data->mouseold = (t_point){0, 0};
	data->keydown = RENDER;
	data->color[0] = &base_color;
	data->color[1] = &blue_gradient;
	data->color[2] = &red_gradient;
	data->color[3] = &weird_color;
	data->color[4] = &random_color;
	data->win.cnum = 0;
	data->win.color = &base_color;
	data->mlx.img = new_img(data);
	init_shortcuts(data);
	return (0);
}
