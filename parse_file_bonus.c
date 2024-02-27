/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:24:26 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/25 21:40:29 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	parse_line_fun(short *arr, t_str line, size_t len,
	t_points *pts)
{
	size_t	i;
	size_t	j;
	char	sign;

	i = -1;
	j = 0;
	while (++i < len)
	{
		arr[i] = 0;
		while (j < line.len && ft_in(line.s[j], WSPACE) != -1)
			j++;
		sign = (j < line.len && line.s[j] == '+')
			- (j < line.len && line.s[j] == '-');
		j += !!sign;
		while (j < line.len && ft_in(line.s[j], WSPACE) == -1)
		{
			pts->co[i] = pts->co[i] * 10 + (unsigned char)line.s[j] - '0';
			j++;
		}
		pts->co[i] *= (sign + !sign);
		if ((float)arr[i] - (float)(i + pts->hei - 1) / 2.0f > pts->max)
			pts->max = (float)arr[i] - (float)(i + pts->hei - 1) / 2.0f;
		if ((float)arr[i] - (float)(i + pts->hei - 1) / 2.0f < pts->min)
			pts->min = (float)arr[i] - (float)(i + pts->hei - 1) / 2.0f;
	}
}

static inline size_t	parse_line_loop(size_t j, t_str line,
		size_t i, t_points *points)
{
	char			sign;

	while (j < line.len && ft_in(line.s[j], WSPACE) != -1)
		j++;
	sign = (j < line.len && line.s[j] == '+')
		- (j < line.len && line.s[j] == '-');
	j += !!sign;
	while (j < line.len && ft_in(line.s[j], WSPACE) == -1)
	{
		if (line.s[j] < '0' || line.s[j] > '9')
		{
			warning_parsing(WNAN, points->hei, line, j);
			while (ft_in(line.s[j], WSPACE) == -1)
				j++;
			break ;
		}
		points->co[i] = points->co[i] * 10 + (unsigned char)line.s[j] - '0';
		if (points->co[i] < 0)
			warning_parsing(WBIG, points->hei, line, i);
		j++;
	}
	if (sign)
		points->co[i] *= sign;
	return (j);
}

static void	parse_line(short *arr, t_str line, size_t len,
	t_points *pts)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		arr[i] = 0;
		j = parse_line_loop(j, line, i, pts);
		if (j >= line.len)
			warning_parsing(WSHORT, pts->hei, line, len - i);
		if ((float)arr[i] - (float)(i + pts->hei - 1) / 2.0f > pts->max)
			pts->max = (float)arr[i] - (float)(i + pts->hei - 1) / 2.0f;
		if ((float)arr[i] - (float)(i + pts->hei - 1) / 2.0f < pts->min)
			pts->min = (float)arr[i] - (float)(i + pts->hei - 1) / 2.0f;
		i++;
	}
	while (j < line.len && ft_in(line.s[j], WSPACE) != -1)
		j++;
	if (j < line.len)
		warning_parsing(WLONG, pts->hei, line, 0);
}

static void	copy_lst(char *line, t_list *tmp, t_points *points, t_list *lst)
{
	size_t	i;

	ft_gnl_tstr(-1, 1);
	free(line);
	if (tmp == NULL)
		free(points->co);
	points->co = malloc(points->wid * points->hei * sizeof(short));
	if (line == NULL || tmp == NULL || tmp->content == NULL || !points->co)
	{
		free(points->co);
		ft_lstclear(&lst, &free);
		put_error("epic malloc fail\n", 17, 1);
		exit(ERR_AINTNOWAY);
	}
	tmp = lst->next;
	i = -1;
	while (++i < points->hei && points->co)
	{
		ft_memcpy(points->co + points->wid * (points->hei - i - 1),
			tmp->content, points->wid * sizeof(short));
		tmp = tmp->next;
	}
	ft_lstclear(&lst, &free);
	warning_parsing(-1, 0, (t_str){0, 0}, 0);
	warning_big_file(points->wid * points->hei);
}

void	parse_file(int fd, t_points *points, unsigned int opt)
{
	t_str	line;
	t_list	*lst;
	t_list	*tmp;

	line = ft_gnl_tstr(fd, 4096);
	points->wid = count_words(line);
	points->co = malloc(points->wid * sizeof(short));
	tmp = ft_lstnew(points->co);
	lst = tmp;
	while (line.len && tmp && tmp->content)
	{
		points->hei++;
		if (opt & FUN_PARSING)
			parse_line_fun(((short *)tmp->content), line, points->wid, points);
		else
			parse_line(((short *)tmp->content), line, points->wid, points);
		free(line.s);
		line = ft_gnl_tstr(fd, 4096);
		points->co = malloc(points->wid * sizeof(short));
		tmp = ft_lstnew(points->co);
		if (tmp)
			ft_lstadd_front(&lst, tmp);
	}
	close(fd);
	copy_lst(line.s, tmp, points, lst);
}
