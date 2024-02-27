/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:45:27 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/18 17:30:33 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	warning_too_short(size_t line, size_t i)
{
	static size_t	last = -1;

	if (last != line)
	{
		write(2, "fdf: warning: line ", 19);
		ft_putnbr_fd(line, 2);
		write(2, " missing ", 9);
		ft_putnbr_fd(i, 2);
		write(2, " numbers.\n", 10);
		last = line;
	}
}

static inline void	put_offset(t_str line, size_t index, size_t i)
{
	i = 0;
	while (i < index)
	{
		if (line.s[i] >= 9 && line.s[i] <= 13)
			write(2, line.s + i, 1);
		else
			write(2, " ", 1);
		i++;
	}
	write(2, "^ here\n", 7);
}

static void	warning_nan(size_t n, t_str line, size_t index)
{
	size_t	i;

	i = line.len > index + 5;
	if (i)
		line.len = index + 5;
	write(2, "fdf: warning: line ", 19);
	ft_putnbr_fd(n, 2);
	write(2, ": character is not a number:\n", 29);
	if (line.len < 70)
		write(2, line.s, line.len);
	else
	{
		write(2, "...", 3);
		index -= line.len - 70;
		write(2, line.s + line.len - 67, 67);
	}
	if (i)
		write(2, "...\n", 4);
	put_offset(line, index, i);
}

static void	warning_large(char err, size_t line, size_t n)
{
	static size_t	lasts[2] = {-1};

	if (err == WBIG && (lasts[0] != line || lasts[1] != n))
	{
		write(2, "fdf: warning: overflow on line ", 31);
		ft_putnbr_fd(line, 2);
		write(2, "\n", 1);
		lasts[0] = line;
		lasts[1] = n;
	}
	else if (err == WLONG)
	{
		write(2, "fdf: warning: too many numbers on line ", 39);
		ft_putnbr_fd(line, 2);
		write(2, "\n", 1);
	}
}

void	warning_parsing(char err, size_t line, t_str s, size_t n)
{
	static size_t	warns = 0;

	warns += 1;
	if (warns < WARN_MAX)
	{
		if (err == WLONG || err == WBIG)
			warning_large(err, line, n);
		else if (err == WSHORT)
			warning_too_short(line, n);
		else if (err == WNAN)
			warning_nan(line, s, n);
	}
	else if (warns == WARN_MAX)
		write(2, "fdf: warning: too many errors. go fix your file.\n", 49);
	else if (warns > WARN_MAX && err == -1)
	{
		write(2, "fdf: warning: ", 14);
		ft_putnbr_fd(warns - 1, 2);
		write(2, " total errors\n", 14);
	}
}
