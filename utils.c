/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:34:24 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/14 17:33:40 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
