/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:21:17 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/12 17:17:09 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define NCOLOR 5

//pi
# define PI_2 6.283185f
# define PI 3.141592f
# define PI_1_4 0.7853981f
# define PI_2_4 1.5707963f
# define PI_3_4 2.3561944f
# define PI_5_4 3.9269908f
# define PI_6_4 4.7123889f
# define PI_7_4 5.4977871f

//colors
# define RED 0xFFFF0000
# define ORE 0xFFFF3300
# define ORA 0xFFFF7700
# define YEL 0xFFFFFF00
# define YGR 0xFF77FF00
# define LGR 0xFF11FF00
# define GRE 0xFF00FF00

//keys
# define RENDER 128
# define ANIM 64
# define SHIFT 1
# define LMB 2
# define RMB 4
# define CTRL 8

//zoom
# define ZOOM 0.03f
# define ZOOM_F 1.03f
# define ZOOM_B 0.97f

//fps
# define MIN_FPS 5.0f
# define FPS_CAP 60

//screen
# define WID 1600
# define HEI 900
# define PAD 40
# define WIDF 1600.f
# define HEIF 900.f
# define PADF 40.f

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
	float	roll;
	float	pitch;
	float	yaw;
	float	projmat[6];
	float	rotmat[9];
	float	wid;
	float	hei;
	float	xoffset;
	float	yoffset;
	float	scale;
	float	zscale;
	int		(*color)(short, short);
	int		cnum;
	char	proj;
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

typedef struct s_f3point
{
	float	x;
	float	y;
	float	z;
}	t_f3point;

typedef struct s_line
{
	t_fpoint	a;
	t_fpoint	b;
}	t_line;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
}	t_mlx;

typedef struct s_data
{
	t_mlx			mlx;
	t_points		points;
	t_win			win;
	t_point			mouse;
	t_point			mouseold;
	unsigned char	keydown;
	int				(*color[NCOLOR])(short, short);
	int				*pixels;
	t_fpoint		*pos;
	float			og_scale;
}	t_data;

//utils
void	put_error(char *s, size_t len, char error);
void	warning_big_file(size_t n);
size_t	count_words(t_str s);
void	*new_img(t_data *data);
int		win_hook(int win, void *data_);

//parse_file
void	parse_file(int fd, t_points *points, unsigned int opt);

//parsing_errors
void	warning_parsing(char err, size_t line, t_str s, size_t n);

//display
void	display_grid(t_points points, void *mlx, void *win);

//place_points
void	place_points(t_points points, t_win winfo, int *pixels, t_fpoint *pos);

//loop
int		fdf_loop(void *data_);

//mouse
int		mouse_hook(int key, void *data_);
int		mouse_unhook(int key, void *data_);

//colors
int		base_color(short z1, short z2);
int		blue_gradient(short z1, short z2);
int		red_gradient(short z1, short z2);
int		weird_color(short z1, short z2);
int		random_color(short z1, short z2);

//win
void	init_projmat_d(float *mat);
void	init_projmat(float *mat);
void	manage_win(t_data *data, int n, char set);
void	init_win(t_win *wininfo, t_points *points);

//init
int		init_data(t_data *data, t_points *points);

//rotate
void	compute_mat(t_data *data, float *mat);
void	update_rot(t_data *data, t_point delta);

#endif
