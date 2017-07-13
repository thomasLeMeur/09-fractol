/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 14:50:24 by tle-meur          #+#    #+#             */
/*   Updated: 2016/02/04 14:20:56 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fractol.h"
#include "mlx.h"

int		free_and_quit(t_fractol *e)
{
	int	i;

	if (e->wins)
	{
		i = -1;
		while (e->wins[++i])
		{
			if (e->wins[i]->img)
				mlx_destroy_image(e->mlx, e->wins[i]->img);
			if (e->wins[i]->win)
				mlx_destroy_window(e->mlx, e->wins[i]->win);
			free(e->wins[i]);
		}
		free(e->wins);
	}
	if (e->mlx)
		free(e->mlx);
	exit(0);
	return (0);
}

void	change_zoom(t_frac *f, double factor)
{
	f->zoom *= factor;
	f->zoomx *= factor;
	f->zoomy *= factor;
	f->max_iter *= factor;
}

void	my_lstdel(void *content, size_t content_size)
{
	(void)content;
	(void)content_size;
}

int		my_lstsrch(const t_list *lst, const void *ptr, size_t size)
{
	(void)ptr;
	return (*(int *)(lst->content) == (int)size);
}

int		my_draw(t_fractol *e, t_win *w)
{
	if (w->type == FOL_JULIA)
		my_julia(w, &w->frac);
	else if (w->type == FOL_MANDEL)
		my_mandelbrot(w, &w->frac);
	else if (w->type == FOL_BURNI)
		my_burning_ship(w, &w->frac);
	mlx_put_image_to_window(e->mlx, w->win, w->img, 0, 0);
	return (1);
}
