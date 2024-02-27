/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:21:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/02/25 18:37:38 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WID 1600
# define HEI 900
# define PAD 40

# define HALF_S 0.70710678f
# define TWOTHIRD_S 0.81649658f
# define SIXTH_S 0.40824829f

# define WSPACE "\f\n\r\t\v "

# ifndef WARN_MAX
#  define WARN_MAX 100
# endif

# define WLONG 1
# define WSHORT 2
# define WNAN 3
# define WBIG 4

# define ERR_FILE 1
# define ERR_AINTNOWAY 2
# define ERR_MLX 3

# include <fcntl.h>
# include <SDL2/SDL_scancode.h>
# include "libft/hdr/libft.h"
# include "MacroLibX/includes/mlx.h"

typedef struct s_win
{
	float	wid;
	float	hei;
	float	xoffset;
	float	yoffset;
	float	scale;
}	t_win;

typedef struct s_points
{
	short	*co;
	size_t	wid;
	size_t	hei;
	float	max;
	float	min;
}	t_points;

typedef struct s_point
{
	short	x;
	short	y;
}	t_point;

typedef struct s_fpoint
{
	float	x;
	float	y;
}	t_fpoint;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
}	t_mlx;

//utils
void	put_error(char *s, size_t len, char error);
size_t	count_words(t_str s);

//parse_file
void	parse_file(int fd, t_points *points);

//parsing_errors
void	warning_parsing(char err, size_t line, t_str s, size_t n);

//display
void	display_grid(t_points points, void *mlx, void *win);

//place_points
void	place_points(t_mlx mlx, t_points points);

#endif
