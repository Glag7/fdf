/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:12:09 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/12 17:51:07 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static inline void	check_angles(t_data *data)
{
	if (data->win.yaw < 0.f)
		data->win.yaw += PI_2;
	else if (data->win.yaw > PI_2)
		data->win.yaw -= PI_2;
	if (data->win.pitch < 0.f)
		data->win.pitch += PI_2;
	else if (data->win.pitch > PI_2)
		data->win.pitch -= PI_2;
	if (data->win.roll < 0.f)
		data->win.roll += PI_2;
	else if (data->win.roll > PI_2)
		data->win.roll -= PI_2;
}

//x for cos and y for sin
void	compute_mat(t_data *data, float *mat)
{
	t_fpoint	yaw;
	t_fpoint	pitch;
	t_fpoint	roll;

	check_angles(data);
	yaw = (t_fpoint){cosf(data->win.yaw), sinf(data->win.yaw)};
	pitch = (t_fpoint){cosf(data->win.pitch), sinf(data->win.pitch)};
	roll = (t_fpoint){cosf(data->win.roll), sinf(data->win.roll)};
	mat[0] = yaw.x * pitch.x;
	mat[1] = yaw.x * pitch.y * roll.y - yaw.y * roll.x;
	mat[2] = yaw.x * pitch.y * roll.x + yaw.y * roll.y;
	mat[3] = yaw.y * pitch.x;
	mat[4] = yaw.y * pitch.y * roll.y + yaw.x * roll.x;
	mat[5] = yaw.y * pitch.y * roll.x - yaw.x * roll.y;
	mat[6] = -pitch.y;
	mat[7] = pitch.x * roll.y;
	mat[8] = pitch.x * roll.x;
}

void	update_rot(t_data *data, t_point delta)
{
	float	scale;

	if (data->keydown & SHIFT)
		scale = 0.0005f;
	else
		scale = 0.005f;
	if (data->win.proj == 0)
	{
		data->win.yaw -= delta.x * scale;
		data->win.pitch += delta.y * scale * .5f * cosf(data->win.yaw - PI_1_4);
		data->win.roll += delta.y * scale * .5f * sinf(data->win.yaw - PI_1_4);
	}
	else
	{
		data->win.yaw -= delta.x * scale;
		data->win.pitch += delta.y * scale * .5f * cosf(data->win.yaw);
		data->win.roll += delta.y * scale * .5f * sinf(data->win.yaw);
	}
	compute_mat(data, data->win.rotmat);
	if (delta.x || delta.y)
		data->keydown |= RENDER;
}
