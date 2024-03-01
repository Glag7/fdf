/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:21:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/01 17:24:58 by glag             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

//keys
# define SHIFT 1
# define LMB 2
# define RMB 4

//zoom
# define ZOOM 0.03f
# define ZOOM_F 1.03f
# define ZOOM_B 0.97f

//fps
# define MIN_FPS 8.0f
# define FPS_CAP 60

//screen
# define WID 1600 * 2 / 3
# define HEI 900 * 2 / 3
# define PAD 40

//opts
# define ALL_FILES 1
# define FUN_PARSING 2
# define DONE 2147483648

//const
# define HALF_S 0.70710678f
# define TWOTHIRD_S 0.81649658f
# define SIXTH_S 0.40824829f

# define WSPACE "\f\n\r\t\v "

//warnings
# ifndef WARN_MAX
#  define WARN_MAX 100
# endif

# define WLONG 1
# define WSHORT 2
# define WNAN 3
# define WBIG 4

//errors
# define ERR_FILE 1
# define ERR_AINTNOWAY 2
# define ERR_MLX 3

# include <time.h>
# include <fcntl.h>
# include <SDL2/SDL_scancode.h>
# include "libft/hdr/libft.h"
# include "MacroLibX/includes/mlx.h"

//structs
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

typedef struct s_data
{
	t_mlx		mlx;
	t_points	points;
	t_win		win;
	t_point		mouse;
	int		pad;//huh
	t_point		mouseold;
	unsigned char	keydown;
	float		fps;
	//rotmat
}	t_data;

//utils
void	put_error(char *s, size_t len, char error);
void	warning_big_file(size_t n);
size_t	count_words(t_str s);
void	*new_img(t_data *data);
int		win_hook(int win, void *mlx);

//parse_file
void	parse_file(int fd, t_points *points, unsigned int opt);

//parsing_errors
void	warning_parsing(char err, size_t line, t_str s, size_t n);

//display
void	display_grid(t_points points, void *mlx, void *win);

//place_points
void	place_points(t_mlx mlx, t_points points, t_win wininfo);

//loop
int		fdf_loop(void *data_);

//drag
int		mouse_hook(int key, void *data_);
int		mouse_unhook(int key, void *data_);

#endif
