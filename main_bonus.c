/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:21:59 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/13 16:33:46 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	print_help(void)
{
	ft_putstr_fd("fdf: CONTROLS:\n", 1);
	ft_putstr_fd("LMB:\t\tdrag\t\t\tR / NP .:\t\treset position\n", 1);
	ft_putstr_fd("RMB:\t\trotate\t\t\tC / NP enter:\t\tchange colors\n", 1);
	ft_putstr_fd("lshift + RMB:\trotate slower\
		F / NP +:\t\tincrease zscale\n", 1);
	ft_putstr_fd("MMB:\t\tchange projection\tV / NP -:\
		decrease zscale\n", 1);
	ft_putstr_fd("MOUSEWHEEL:\tzoom\
		\tlctrl + num:\t\tsave view\n", 1);
	ft_putstr_fd("SPACE:\t\tstart / stop anim\
	num:\t\t\tload view\n", 1);
}

static unsigned int	parse_opt(char *opt)
{
	unsigned int	res;

	if (*opt == 0)
	{
		put_error("wrong option\n", 13, 1);
		exit(ERR_FILE);
	}
	if (*opt == '-' && opt[1] == 0)
		return (DONE);
	res = 0;
	while (*opt)
	{
		if (*opt == 'a')
			res |= ALL_FILES;
		else if (*opt == 'f')
			res |= FUN_PARSING;
		else
		{
			put_error("wrong option\n", 13, 1);
			exit(ERR_FILE);
		}
		opt++;
	}
	return (res);
}

static unsigned int	parse_args(int argc, char **argv)
{
	int				i;
	unsigned int	res;
	int				file;

	res = 0;
	file = 0;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && (res & DONE) == 0)
			res |= parse_opt(argv[i] + 1);
		else
		{
			file++;
			argv[1] = argv[i];
		}
		i++;
	}
	if (file != 1)
	{
		put_error("wrong number of files\n", 22, 1);
		exit(ERR_FILE);
	}
	return (res);
}

static int	get_file(char **av, unsigned int opt)
{
	int		fd;
	size_t	len;

	len = ft_strlen(av[1]);
	if ((len < 5 || av[1][len - 1] != 'f' || av[1][len - 2] != 'd'
		|| av[1][len - 3] != 'f' || av[1][len - 4] != '.')
		&& !(opt & ALL_FILES))
	{
		put_error("file needs to end with .fdf\n", 28, 1);
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
	int				fd;
	unsigned int	opt;
	t_points		points;
	void			*mlx;
	void			*win;

	opt = parse_args(argc, argv);
	points = (t_points){0, 0, 0, -1099511627776.0f, 1099511627776.0f};
	fd = get_file(argv, opt);
	parse_file(fd, &points, opt);
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
	print_help();
	display_grid(points, mlx, win);
	mlx_destroy_window(mlx, win);
	mlx_destroy_display(mlx);
}
