/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpham <mpham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:53:40 by minh              #+#    #+#             */
/*   Updated: 2018/02/01 18:11:55 by mpham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "mlx.h"
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "math3D.h"

# define WIN_WIDTH 2000
# define WIN_HEIGHT 1500
# define TILE_WIDTH 25
# define TILE_HEIGHT 25
# define PI 3.14159265359

# define EXIT 53
# define CLEAR 51
# define RESET 49
# define MOVE_UP 126
# define MOVE_DOWN 125
# define MOVE_RIGHT 124
# define MOVE_LEFT 123
# define SCROLL_UP 5
# define SCROLL_DOWN 7
# define ROTATE_UP 91
# define ROTATE_DOWN 84
# define ROTATE_RIGHT 88
# define ROTATE_LEFT 86

typedef struct	s_point
{
	int 		x;
	int 		y;
	int 		z;
	int			w;
	char		*color;
}			  	t_point;

typedef struct  s_line
{
	t_point	**points;
	int		len;
}				t_line;

typedef struct  s_map
{
	t_line	**lines;
	int		len;
}				t_map;

typedef struct	s_coord
{
	int 	x1;
	int		y1;
	int		z1;
	int		w1;
	int 	x2;
	int		y2;
	int		z2;
	int		w2;
}				t_coord;

typedef struct  s_algo
{
	int		x;
	int 	y;
    int     dx;
    int     dy;
    int     incX;
    int     incY;
	int		inc1;
	int		inc2;
	int		e;
}               t_algo;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			sizeline;
	int			bpp;
	int			endian;
}               t_img;

typedef struct  s_env
{
    void        *mlx;
    void        *win;
	t_map		*map;
	t_map		*map_buffer;
    t_img       img;
	int			offset_x;
	int			offset_y;
	int			zoomFactor;
	int			angle;
}               t_env;

void   	ft_parse_map(t_env *e, char **argv);
t_point     **ft_get_coord(char *line, int nb_line, t_point ***array_points);
void    	ft_print_tab(t_map *map);
int     	ft_count_column(char *line);
int     	ft_count_row(char *map);
void    	ft_init_map(t_env *e);
void    	ft_set_coord(t_env *e, mat4_t matrice);
void		ft_draw_horizontal(t_env *e);
void		ft_draw_vertical(t_env *e);
void    	ft_bresenham(t_env *e, int x1, int y1, int x2, int y2);
void    	ft_bresenham1(t_env *e, t_algo *b);
void    	ft_bresenham2(t_env *e, t_algo *b);
void    	ft_fill_pixel(t_env *e, int x, int y, int color);
void    	ft_redraw(t_env *e);
void    	ft_init_img(t_env *e);
int			move_hook(int keycode, t_env *e);
void    	ft_change_map(t_env *e);
int			rotate_hook(int keycode, t_env *e);
void		malloc_points(t_env *e);

#endif