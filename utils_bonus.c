/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:34:24 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/01 19:10:54 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	warning_big_file(size_t n)
{
	if (n > 100000)
		put_error("file is very big\n", 17, 0);
}

void	put_error(char *s, size_t len, char error)
{
	if (error)
		write(2, "fdf: error: ", 12);
	else
		write(2, "fdf: warning: ", 14);
	if (len == (size_t)-1)
		len = ft_strlen(s);
	write(2, s, len);
}

size_t	count_words(t_str s)
{
	size_t	word_count;
	size_t	i;
	char	isword;

	word_count = 0;
	isword = 1;
	i = 0;
	while (i < s.len)
	{
		if (ft_in(s.s[i], WSPACE) != -1)
			isword = 1;
		else
		{
			word_count += isword;
			isword = 0;
		}
		i++;
	}
	return (word_count);
}

void	*new_img(t_data *data)
{
	void	*img;

	img = mlx_new_image(data->mlx.mlx, WID, HEI);
	if (img == NULL)
	{
		free(data->points.co);
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		mlx_destroy_display(data->mlx.mlx);
		put_error("MLX exploded :(\n", 16, 1);
		exit(ERR_MLX);
	}
	return (img);
}

int	win_hook(int win, void *mlx)
{
	if (win == 0)
		mlx_loop_end(mlx);
	return (0);
}
