/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_points_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:17:44 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/12 18:43:57 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_line(int color, t_line line, int *pixels)
{
	t_fpoint	delta;
	t_fpoint	inc;
	t_fpoint	pos;
	float		steps;
	float		i;

	delta.x = line.b.x - line.a.x;
	delta.y = line.b.y - line.a.y;
	if (fabsf(delta.x) > fabsf(delta.y))
		steps = fabsf(delta.x);
	else
		steps = fabsf(delta.y);
	inc.x = delta.x / steps;
	inc.y = delta.y / steps;
	pos.x = line.a.x;
	pos.y = line.a.y;
	i = 0.0f;
	while (i < steps)
	{
		if (pos.x > 0.f && pos.x < WID && pos.y > 0.f && pos.y < HEI)
			pixels[(int)pos.y * WID + (int)pos.x] = color;
		pos.x += inc.x;
		pos.y += inc.y;
		i += 1.0f;
	}
}

static void	draw_line_wrap(int color, t_line line, int *pixels)
{
	t_fpoint	delta;

	delta = (t_fpoint){(line.a.x - line.b.x) / (line.a.y - line.b.y),
		(line.a.y - line.b.y) / (line.a.x - line.b.x)};
	if (line.a.x < 0.f)
		line.a = (t_fpoint){.y = line.a.y - delta.y * line.a.x, .x = 0.f};
	else if (line.a.x > WIDF)
		line.a = (t_fpoint){.y = line.a.y + delta.y * (WIDF - line.a.x),
			.x = WIDF};
	if (line.b.x < 0.f)
		line.b = (t_fpoint){.y = line.b.y - delta.y * line.b.x, .x = 0.f};
	else if (line.b.x > WIDF)
		line.b = (t_fpoint){.y = line.b.y + delta.y * (WIDF - line.b.x),
			.x = WIDF};
	if (line.a.y < 0.f)
		line.a = (t_fpoint){line.a.x - delta.x * line.a.y, 0.f};
	else if (line.a.y > HEIF)
		line.a = (t_fpoint){line.a.x + delta.x * (HEIF - line.a.y), HEIF};
	if (line.b.y < 0.f)
		line.b = (t_fpoint){line.b.x - delta.x * line.b.y, 0.f};
	else if (line.b.y > HEIF)
		line.b = (t_fpoint){line.b.x + delta.x * (HEIF - line.b.y), HEIF};
	draw_line(color, line, pixels);
}

static void	draw_wire_r(t_points points, t_win winfo,
		int *pixels, t_fpoint *pos)
{
	size_t	i;
	size_t	j;

	i = points.hei - 1;
	while (i != (size_t)-1)
	{
		j = 0;
		while (j < points.wid)
		{
			if (j)
				draw_line_wrap(winfo.color(points.co[i * points.wid + j],
						points.co[i * points.wid + j - 1]),
					(t_line){pos[i * points.wid + j],
					pos[i * points.wid + j - 1]}, pixels);
			if (i)
				draw_line_wrap(winfo.color(points.co[i * points.wid + j],
						points.co[i * points.wid + j - points.wid]),
					(t_line){pos[i * points.wid + j],
					pos[i * points.wid + j - points.wid]}, pixels);
			j++;
		}
		i--;
	}
}

static void	draw_wire(t_points points, t_win winfo, int *pixels, t_fpoint *pos)
{
	size_t	i;
	size_t	j;

	if ((winfo.yaw > PI_1_4 && winfo.yaw < PI_5_4))
		return (draw_wire_r(points, winfo, pixels, pos));
	i = -1;
	while (++i < points.hei)
	{
		j = 0;
		while (j < points.wid)
		{
			if (j)
				draw_line_wrap(winfo.color(points.co[i * points.wid + j],
						points.co[i * points.wid + j - 1]),
					(t_line){pos[i * points.wid + j],
					pos[i * points.wid + j - 1]}, pixels);
			if (i)
				draw_line_wrap(winfo.color(points.co[i * points.wid + j],
						points.co[i * points.wid + j - points.wid]),
					(t_line){pos[i * points.wid + j],
					pos[i * points.wid + j - points.wid]}, pixels);
			j++;
		}
	}
}

void	place_points(t_points pts, t_win win, int *pixels, t_fpoint *pos)
{
	size_t		i;
	size_t		j;
	t_f3point	co;
	t_f3point	p;

	i = -1;
	while (++i < pts.hei)
	{
		j = 0;
		while (j < pts.wid)
		{
			co = (t_f3point){(float)j - pts.wid / 2, (float)i - pts.hei
				/ 2, pts.co[i * pts.wid + j] * win.zscale};
			p = (t_f3point){win.rotmat[0] * co.x + win.rotmat[1] * co.y
				+ win.rotmat[2] * co.z, win.rotmat[3] * co.x + win.rotmat[4]
				* co.y + win.rotmat[5] * co.z, win.rotmat[6] * co.x
				+ win.rotmat[7] * co.y + win.rotmat[8] * co.z};
			pos[pts.wid * i + j] = (t_fpoint){win.scale * (win.projmat[0]
					* p.x + win.projmat[1] * p.y + win.projmat[2] * p.z)
				+ win.xoffset, win.scale * (win.projmat[3] * p.x + win.projmat
				[4] * p.y + win.projmat[5] * p.z) + win.yoffset};
			j++;
		}
	}
	draw_wire(pts, win, pixels, pos);
}
