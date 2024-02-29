/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:25:41 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/29 19:54:03 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

#define RED 0xFFFF0000
#define ORE 0xFFFF3300
#define ORA 0xFFFF7700
#define YEL 0xFFFFFF00
#define YGR 0xFF77FF00
#define LGR 0xFF11FF00
#define GRE 0xFF00FF00

//space because mlx
static inline void	drawfps(t_mlx *mlx, int fps_val, char draw)
{
	static char	num[8] = "fps:    ";
	static int	todraw = 0;
	static int	color[9] = {RED, ORE, ORA, YEL, YGR, LGR, GRE, GRE, GRE};

	if (draw)
	{
		mlx_string_put(mlx->mlx, mlx->win, 0, 10, 0xFF000000, num);
		if (todraw > 9)
		{
			num[6] = 0;
			num[5] = todraw % 10 + '0';
			num[4] = todraw / 10 + '0';
			mlx_string_put(mlx->mlx, mlx->win, 0, 10, color[todraw / 10], num);
			num[6] = ' ';
		}
		else
		{
			num[5] = 0;
			num[4] = todraw % 10 + '0';
			mlx_string_put(mlx->mlx, mlx->win, 0, 10, RED, num);
			num[5] = ' ';
		}
	}
	else
		todraw = fps_val;
}

int	putfps(void *mlx_)
{
	static struct timespec	past = {0, 0};
	struct timespec			curr;
	float					fps_val;
	t_mlx					*mlx;

	mlx = (t_mlx *)mlx_;
	clock_gettime(CLOCK_MONOTONIC_RAW, &curr);
	fps_val = 1.0 / ((float)(curr.tv_sec - past.tv_sec)
			+ (float)(curr.tv_nsec - past.tv_nsec) *1e-9);
	fps(1, fps_val);
	drawfps(mlx, round(fps_val), 0);
	if (curr.tv_sec > past.tv_sec)
		drawfps(mlx, 0, 1);
	printf("fps: %f\n", fps_val);
	past = curr;
	return (0);
}

float	fps(char set, float new)
{
	static float	fps = 30.0f;

	if (set)
		fps = new;
	return (fps);
}
