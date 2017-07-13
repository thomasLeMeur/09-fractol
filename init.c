/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 13:31:41 by tle-meur          #+#    #+#             */
/*   Updated: 2016/02/04 16:15:50 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fractol.h"

void	init_julia(t_frac *frac)
{
	frac->xmin = -1.;
	frac->xmax = 1.;
	frac->ymin = -1.2;
	frac->ymax = 1.2;
	frac->zoom = 1.;
	frac->zoomx = FOL_WID / (frac->xmax - frac->xmin);
	frac->zoomy = FOL_HIG / (frac->ymax - frac->ymin);
	frac->max_iter = 100;
	frac->x = frac->xmin;
	frac->y = frac->ymin;
	frac->cr_ref = 0.285;
	frac->ci_ref = 0.01;
}

void	init_mandelbrot(t_frac *frac)
{
	frac->xmin = -2.1;
	frac->xmax = 0.6;
	frac->ymin = -1.2;
	frac->ymax = 1.2;
	frac->zoom = 1.;
	frac->zoomx = FOL_WID / (frac->xmax - frac->xmin);
	frac->zoomy = FOL_HIG / (frac->ymax - frac->ymin);
	frac->max_iter = 30;
	frac->x = frac->xmin;
	frac->y = frac->ymin;
	frac->cr_ref = 0.;
	frac->ci_ref = 0.;
}

void	init_burning_ship(t_frac *frac)
{
	frac->xmin = -1.25;
	frac->xmax = 2.15;
	frac->ymin = -1.2;
	frac->ymax = 2.2;
	frac->zoom = 1.;
	frac->zoomx = FOL_WID / (frac->xmax - frac->xmin);
	frac->zoomy = FOL_HIG / (frac->ymax - frac->ymin);
	frac->max_iter = 30;
	frac->x = frac->xmin;
	frac->y = frac->ymin;
	frac->cr_ref = 0.;
	frac->ci_ref = 0.;
}

void	reinit(t_win *win, t_frac *f)
{
	if (win->type == FOL_JULIA)
		init_julia(f);
	else if (win->type == FOL_MANDEL)
		init_mandelbrot(f);
	else if (win->type == FOL_BURNI)
		init_burning_ship(f);
}

int		get_color(t_frac *f, int col, int nb, double max)
{
	double	tmp;

	if (col == FOL_BLUE)
		return ((nb == (int)max) ? 0 : (int)round(nb * 255. / max));
	else if (col == FOL_GREEN)
		return ((nb == (int)max) ? 0 : (int)round(nb * 255. / max) * 256);
	else if (col == FOL_RED)
		return ((nb == (int)max) ? 0 : (int)round(nb * 255. / max) * 65536);
	else if (col == FOL_WHITE)
		return ((nb == (int)max) ? 0 : (int)round(nb * 255. / max)
		+ round(nb * 255. / max) * 256 + round(nb * 255. / max) * 65536);
	else if (col == FOL_OTHER)
	{
		if (nb == (int)max)
			return (0);
		else if (((nb *= f->zoom) || 1) && nb < max / 3.)
			return ((int)round(nb * 3. * 255. / max));
		else if (nb < max / 1.5 && ((tmp = (nb - max / 3.) * 3.) || 1))
			return (255 - round(tmp * 255. / max)
					+ round(tmp * 255. / max) * 256);
		else if ((tmp = (nb - max / 1.5) * 3.) || 1)
			return (65535 - round(tmp * 255. / max) * 256.
					+ round(tmp * 255. / max) * 65536.);
	}
	return (0);
}
