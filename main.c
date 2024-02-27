/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:21:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/24 17:39:26 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_file(int ac, char **av)
{
	int		fd;
	size_t	len;

	if (ac == 2)
		len = ft_strlen(av[1]);
	if (ac != 2 || len < 5 || av[1][len - 1] != 'f' || av[1][len - 2] != 'd'
		|| av[1][len - 3] != 'f' || av[1][len - 4] != '.')
	{
		put_error("usage : ./fdf [file].fdf\n", 25, 1);
		exit(ERR_FILE);
	}
	fd = open(av[1], O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		put_error("not a file\n", 11, 1);
		exit(ERR_FILE);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		put_error("cannot open file\n", 17, 1);
		exit(ERR_FILE);
	}
	return (fd);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_points	points;
	void		*mlx;
	void		*win;

	points = (t_points){0, 0, 0, -1099511627776.0f, 1099511627776.0f};
	fd = get_file(argc, argv);
	parse_file(fd, &points);
	mlx = mlx_init();
	if (mlx)
		win = mlx_new_window(mlx, WID, HEI, "fil de fdf");
	if (mlx == NULL || win == NULL)
	{
		if (mlx)
			mlx_destroy_display(mlx);
		free(points.co);
		put_error("MLX exploded :(\n", 16, 1);
		return (ERR_MLX);
	}
	display_grid(points, mlx, win);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
}
