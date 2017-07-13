/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 11:25:06 by tle-meur          #+#    #+#             */
/*   Updated: 2016/02/04 14:20:14 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"

int	my_expose1(t_fractol *e)
{
	int	i;

	i = -1;
	while (e->wins[++i])
		if (e->wins[i]->type == FOL_JULIA)
		{
			e->id = i;
			break ;
		}
	mlx_put_image_to_window(e->mlx, e->wins[i]->win, e->wins[i]->img, 0, 0);
	return (1);
}

int	my_expose2(t_fractol *e)
{
	int	i;

	i = -1;
	while (e->wins[++i])
		if (e->wins[i]->type == FOL_MANDEL)
		{
			e->id = i;
			break ;
		}
	mlx_put_image_to_window(e->mlx, e->wins[i]->win, e->wins[i]->img, 0, 0);
	return (1);
}

int	my_expose3(t_fractol *e)
{
	int	i;

	i = -1;
	while (e->wins[++i])
		if (e->wins[i]->type == FOL_BURNI)
		{
			e->id = i;
			break ;
		}
	mlx_put_image_to_window(e->mlx, e->wins[i]->win, e->wins[i]->img, 0, 0);
	return (1);
}

int	my_key(int key, t_fractol *e)
{
	t_frac	*f;
	t_win	*win;
	double	move;

	win = e->wins[e->id];
	f = &win->frac;
	if (key == FOL_ESC || key == FOL_B)
		(key == FOL_ESC) ? free_and_quit(e) : (win->b = (win->b + 1) % 2);
	else if (key == FOL_SPACE)
		reinit(win, f);
	else if (key == FOL_PLUS)
		change_zoom(f, 1.1);
	else if (key == FOL_LESS)
		change_zoom(f, 0.91);
	else if (key == FOL_UP && (move = (f->ymax - f->ymin) / 10. / f->zoom))
		f->y = (win->type == FOL_BURNI) ? f->y + move : f->y - move;
	else if (key == FOL_DOWN && (move = (f->ymax - f->ymin) / 10. / f->zoom))
		f->y = (win->type == FOL_BURNI) ? f->y - move : f->y + move;
	else if (key == FOL_LEFT && (move = (f->xmax - f->xmin) / 10. / f->zoom))
		f->x = (win->type == FOL_BURNI) ? f->x + move : f->x - move;
	else if (key == FOL_RIGHT && (move = (f->xmax - f->xmin) / 10. / f->zoom))
		f->x = (win->type == FOL_BURNI) ? f->x - move : f->x + move;
	else if (key == FOL_COL)
		win->col = (win->col + 1) % FOL_NBCOLS;
	return (my_draw(e, win));
}

int	my_mouse(int but, int x, int y, t_fractol *e)
{
	t_frac	*f;
	t_win	*win;

	win = e->wins[e->id];
	f = &win->frac;
	if (x < 0 || y < 0 || x >= FOL_WID || y >= FOL_HIG || but < 4 || but > 5)
		return (1);
	if (but == 4)
	{
		change_zoom(f, 0.91);
		f->x -= (((e->wins[e->id]->type == FOL_BURNI) ? (FOL_WID - x) : x)
			/ (double)FOL_WID) * ((f->xmax - f->xmin) / 10. / f->zoom);
		f->y -= (((e->wins[e->id]->type == FOL_BURNI) ? (FOL_HIG - y) : y)
			/ (double)FOL_HIG) * ((f->ymax - f->ymin) / 10. / f->zoom);
	}
	else if (but == 5)
	{
		change_zoom(f, 1.1);
		f->x += (((e->wins[e->id]->type == FOL_BURNI) ? (FOL_WID - x) : x)
			/ (double)FOL_WID) * ((f->xmax - f->xmin) / 10. / f->zoom);
		f->y += (((e->wins[e->id]->type == FOL_BURNI) ? (FOL_HIG - y) : y)
			/ (double)FOL_HIG) * ((f->ymax - f->ymin) / 10. / f->zoom);
	}
	my_draw(e, win);
	return (1);
}
