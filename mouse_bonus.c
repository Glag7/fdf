/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:43:16 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/10 14:46:46 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	mouse_hook(int key, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if (key == 1)
		data->keydown |= LMB;
	else if (key == 3)
		data->keydown |= RMB;
	else if (key == 2)
	{
		data->win.proj = !data->win.proj;
		if (data->win.proj == 0)
			init_projmat(data->win.projmat);
		else
			init_projmat_d(data->win.projmat);
		data->keydown |= RENDER;
	}
	return (0);
}

int	mouse_unhook(int key, void *data_)
{
	t_data	*data;

	data = (t_data *)data_;
	if (key == 1)
		data->keydown &= ~LMB;
	else if (key == 3)
		data->keydown &= ~RMB;
	return (0);
}
