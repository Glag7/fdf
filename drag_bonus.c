/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drag_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:43:16 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/01 17:12:41 by glag             ###   ########.fr       */
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
