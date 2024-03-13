/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:03:14 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/12 17:56:45 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	init_projmat(float *mat)
{
	mat[0] = HALF_S;
	mat[1] = -HALF_S;
	mat[2] = 0.f;
	mat[3] = SIXTH_S;
	mat[4] = SIXTH_S;
	mat[5] = -TWOTHIRD_S;
}

void	init_projmat_d(float *mat)
{
	mat[0] = .5f;
	mat[1] = .5f;
	mat[2] = 0.f;
	mat[3] = 0.f;
	mat[4] = 0.f;
	mat[5] = -1.f;
}

static inline void	init_rotmat(float *mat)
{
	mat[0] = 1.f;
	mat[1] = 0.f;
	mat[2] = 0.;
	mat[3] = 0.f;
	mat[4] = 1.f;
	mat[5] = 0.f;
	mat[6] = 0.f;
	mat[7] = 0.f;
	mat[8] = 1.f;
}

void	init_win(t_win *wininfo, t_points *points)
{
	float	wid;
	float	hei;
	float	scale;

	init_projmat(wininfo->projmat);
	init_rotmat(wininfo->rotmat);
	wininfo->roll = 0.f;
	wininfo->pitch = 0.f;
	wininfo->yaw = 0.f;
	wininfo->proj = 0;
	wid = (float)(points->wid + points->hei - 2) * HALF_S;
	hei = (points->max - points->min) * TWOTHIRD_S;
	if ((float)WID / wid < (float)HEI / hei)
		scale = (float)(WID - PAD) / wid;
	else
		scale = (float)(HEI - PAD) / hei;
	wininfo->xoffset = WIDF / 2.f;
	wininfo->yoffset = ((float)HEI + (points->max + points->min
				+ (points->wid + points->hei) / 2)
			* TWOTHIRD_S * scale) / 2.0f;
	wininfo->wid = wid;
	wininfo->hei = hei;
	wininfo->scale = scale;
	wininfo->zscale = 1.0f;
}

void	manage_win(t_data *data, int n, char set)
{
	static t_win	wininfo[10];

	if (set)
		wininfo[n] = data->win;
	else
		data->win = wininfo[n];
}
