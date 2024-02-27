/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:49:06 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/22 19:16:42 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_hook(int key, void *mlx)
{
	if (key == SDL_SCANCODE_ESCAPE)
		mlx_loop_end(mlx);
	return (0);
}

static int	win_hook(int win, void *mlx)
{
	if (win == 0)
		mlx_loop_end(mlx);
	return (0);
}

void	display_grid(t_points points, void *mlx_, void *win)
{
	void	*img;
	t_mlx	mlx;

	img = mlx_new_image(mlx_, WID, HEI);
	if (img == NULL)
	{
		free(points.co);
		mlx_destroy_window(mlx_, win);
		mlx_destroy_display(mlx_);
		put_error("MLX exploded :(\n", 16, 1);
		exit(ERR_MLX);
	}
	mlx = (t_mlx){mlx_, win, img};
	mlx_set_fps_goal(mlx.mlx, 60);
	if (points.hei && points.wid)
		place_points(mlx, points);
	free(points.co);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_on_event(mlx.mlx, mlx.win, MLX_KEYDOWN, key_hook, mlx.mlx);
	mlx_on_event(mlx.mlx, mlx.win, MLX_WINDOW_EVENT, win_hook, mlx.mlx);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, mlx.img);
}
