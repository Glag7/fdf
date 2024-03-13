/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:05:55 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/10 14:24:23 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	base_color(short z1, short z2)
{
	(void)z1;
	(void)z2;
	return (0xFFFFFFFF);
}

int	blue_gradient(short z1, short z2)
{
	int	zmax;

	if (z1 < 0)
		z1 = -z1;
	if (z2 < 0)
		z2 = -z2;
	if (z1 > z2)
		zmax = z1;
	else
		zmax = z2;
	if (zmax > 127)
		zmax = 127;
	return (0xCF000000 | (zmax << 24)
		| ((127 - zmax) << 9) | ((127 - zmax) << 17) | 0xFF);
}

int	red_gradient(short z1, short z2)
{
	int	zmax;

	if (z1 < 0)
		z1 = -z1;
	if (z2 < 0)
		z2 = -z2;
	if (z1 > z2)
		zmax = z1;
	else
		zmax = z2;
	if (zmax > 127)
		zmax = 127;
	return (0xFFBF0000 | zmax * 513);
}

int	weird_color(short z1, short z2)
{
	return (0xFF000000 | (((z1 * z2 + z1 + z2) << 8) & 0x0000FF00));
}

int	random_color(short z1, short z2)
{
	static int	notrandom = 123456;
	int			alpha;

	alpha = z1 * z2;
	if (alpha > 127 || alpha < 0)
		alpha = 127;
	notrandom += 11;
	return (0x80000000 | notrandom * 234567891 | alpha << 24);
}
