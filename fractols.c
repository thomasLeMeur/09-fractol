/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 14:47:22 by tle-meur          #+#    #+#             */
/*   Updated: 2016/02/04 16:40:29 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fractol.h"
#include "mlx.h"

void	my_mandelbrot(t_win *win, t_frac *f)
{
	int		i;
	int		x;
	int		y;
	double	tmp;

	y = -1;
	while (++y < FOL_HIG && (x = -1))
	{
		f->ci = y / f->zoomy + f->y;
		while (++x < FOL_WID)
		{
			f->cr = x / f->zoomx + f->x;
			f->zr = f->cr_ref;
			f->zi = f->ci_ref;
			i = -1;
			while (++i < (int)f->max_iter && f->zr * f->zr + f->zi * f->zi < 4)
			{
				tmp = f->zr;
				f->zr = f->zr * f->zr - f->zi * f->zi + f->cr;
				f->zi = 2 * f->zi * tmp + f->ci;
			}
			*(int *)(win->buf + y * win->line + x * 4) =
				get_color(f, win->col, i, f->max_iter);
		}
	}
}

void	my_julia(t_win *win, t_frac *f)
{
	int		i;
	int		x;
	int		y;
	double	tmp;

	y = -1;
	while (++y < FOL_HIG && (x = -1))
		while (++x < FOL_WID)
		{
			f->zr = x / f->zoomx + f->x;
			f->zi = y / f->zoomy + f->y;
			f->cr = f->cr_ref;
			f->ci = f->ci_ref;
			i = -1;
			while (++i < (int)f->max_iter && f->zr * f->zr + f->zi * f->zi < 4)
			{
				tmp = f->zr;
				f->zr = f->zr * f->zr - f->zi * f->zi + f->cr;
				f->zi = 2 * f->zi * tmp + f->ci;
			}
			*(int *)(win->buf + y * win->line + x * 4) =
				get_color(f, win->col, i, f->max_iter);
		}
}

void	my_burning_ship(t_win *win, t_frac *f)
{
	int		i;
	int		x;
	int		y;
	double	tmp;

	y = -1;
	while (++y < FOL_HIG && (x = -1))
		while (++x < FOL_WID)
		{
			f->cr = x / f->zoomx + f->x;
			f->ci = y / f->zoomy + f->y;
			f->zr = f->cr_ref;
			f->zi = f->ci_ref;
			i = -1;
			while (++i < (int)f->max_iter && f->zr * f->zr + f->zi * f->zi < 10)
			{
				tmp = f->zr;
				f->zr = f->zr * f->zr - f->zi * f->zi - f->cr;
				f->zi = 2 * FT_ABS(f->zi * tmp) - f->ci;
			}
			*(int *)(win->buf + (FOL_HIG - y - 1) * win->line
			+ (FOL_WID - x - 1) * 4) = get_color(f, win->col, i, f->max_iter);
		}
}

int		my_move_julia(int x, int y, t_fractol *e)
{
	t_frac	*f;

	if (e->wins[e->id]->b || x < 0 || y < 0 || x >= FOL_WID
		|| y >= FOL_HIG || e->wins[e->id]->type != FOL_JULIA)
		return (1);
	f = &e->wins[e->id]->frac;
	f->cr_ref = -1 + (f->x - f->xmin) + ((x / (double)FOL_WID) * 2.) / f->zoom;
	f->ci_ref = 1 - (f->y - f->ymin) - ((y / (double)FOL_HIG) * 2.) / f->zoom;
	my_draw(e, e->wins[e->id]);
	return (1);
}
