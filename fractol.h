/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 18:18:04 by tle-meur          #+#    #+#             */
/*   Updated: 2016/02/04 16:36:23 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <sys/types.h>
# include "libft/libft.h"

# define FOL_NBCOLS	5
# define FOL_BLUE	0
# define FOL_WHITE	1
# define FOL_RED	2
# define FOL_GREEN	3
# define FOL_OTHER	4
# define FOL_JULIA	1
# define FOL_MANDEL	2
# define FOL_BURNI	3
# define FOL_COL	8
# define FOL_B		11
# define FOL_PLUS	24
# define FOL_LESS	27
# define FOL_SPACE	49
# define FOL_ESC	53
# define FOL_LEFT	123
# define FOL_RIGHT	124
# define FOL_DOWN	125
# define FOL_UP		126
# define FOL_WID	800
# define FOL_HIG	600

typedef struct	s_frac
{
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	zoom;
	double	zoomx;
	double	zoomy;
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	cr_ref;
	double	ci_ref;
	double	max_iter;
	double	x;
	double	y;
}				t_frac;

typedef struct	s_win
{
	void	*win;
	void	*img;
	char	*buf;
	int		line;
	int		type;
	int		col;
	t_frac	frac;
	int		b;
}				t_win;

typedef struct	s_fractol
{
	void	*mlx;
	t_win	**wins;
	int		id;
}				t_fractol;

/*
**	utilities.c
*/
int				free_and_quit(t_fractol *e);
int				my_draw(t_fractol *e, t_win *w);
void			change_zoom(t_frac *f, double factor);
void			my_lstdel(void *content, size_t content_size);
int				my_lstsrch(const t_list *lst, const void *ptr, size_t size);

/*
**	parse.c
*/
int				my_parse(int ac, char **av, t_fractol *e);

/*
**	funcions.c
*/
int				my_expose1(t_fractol *e);
int				my_expose2(t_fractol *e);
int				my_expose3(t_fractol *e);
int				my_key(int key, t_fractol *e);
int				my_mouse(int button, int x, int y, t_fractol *e);

/*
**	init.c
*/
void			init_julia(t_frac *frac);
void			init_mandelbrot(t_frac *frac);
void			init_burning_ship(t_frac *frac);
void			reinit(t_win *win, t_frac *frac);
int				get_color(t_frac *f, int col, int nb, double max);

/*
**	fractols.c
*/
void			my_julia(t_win *win, t_frac *f);
void			my_mandelbrot(t_win *win, t_frac *f);
void			my_burning_ship(t_win *win, t_frac *f);
int				my_move_julia(int x, int y, t_fractol *e);

#endif
