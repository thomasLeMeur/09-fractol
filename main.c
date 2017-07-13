/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 14:47:22 by tle-meur          #+#    #+#             */
/*   Updated: 2016/02/03 21:10:29 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fractol.h"
#include "mlx.h"

static void	init_win(t_fractol *e, t_win *win, void (*init)(), int (*exp)())
{
	win->b = 0;
	win->col = FOL_BLUE;
	(*init)(&win->frac);
	my_draw(e, win);
	mlx_expose_hook(win->win, exp, e);
	mlx_key_hook(win->win, &my_key, e);
	mlx_mouse_hook(win->win, &my_mouse, e);
}

int			main(int ac, char **av)
{
	int			i;
	t_fractol	e;
	int			ret;

	if (!(e.mlx = mlx_init()))
		return (0);
	if ((ret = my_parse(ac, av, &e)) == 0)
		write(1, "Usage : ./fractol [julia mandelbrot burning_ship]\n", 50);
	if (ret > 0 && (i = -1))
	{
		while (e.wins[++i])
			if (e.wins[i]->type == FOL_JULIA)
			{
				init_win(&e, e.wins[i], &init_julia, &my_expose1);
				mlx_hook(e.wins[i]->win, 6, 0, &my_move_julia, &e);
			}
			else if (e.wins[i]->type == FOL_MANDEL)
				init_win(&e, e.wins[i], &init_mandelbrot, &my_expose2);
			else if (e.wins[i]->type == FOL_BURNI)
				init_win(&e, e.wins[i], &init_burning_ship, &my_expose3);
		mlx_loop(e.mlx);
	}
	return (free_and_quit(&e));
}
