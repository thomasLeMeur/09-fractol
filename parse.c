/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 15:09:35 by tle-meur          #+#    #+#             */
/*   Updated: 2016/02/03 18:26:07 by tle-meur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"
#include "libft/libft.h"
#include "mlx.h"

static int	lst_add_elem(t_list **lst, int type, int *nb)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew(&type, sizeof(int))))
	{
		ft_lstdel(lst, &my_lstdel);
		return (0);
	}
	ft_lstpush(lst, tmp);
	(*nb)++;
	return (1);
}

static int	init_list(int ac, char **av, t_list **lst)
{
	int		i;
	int		j;
	int		nb;

	i = 0;
	nb = 0;
	*lst = NULL;
	while (++i < ac && (j = -1))
	{
		while (av[i][++j])
			av[i][j] = (char)ft_tolower(av[i][j]);
		if (ft_strcmp(av[i], "julia") == 0
			&& !ft_lstfind(*lst, &i, FOL_JULIA, &my_lstsrch)
			&& !lst_add_elem(lst, FOL_JULIA, &nb))
			return (-1);
		else if (ft_strcmp(av[i], "mandelbrot") == 0
			&& !ft_lstfind(*lst, &i, FOL_MANDEL, &my_lstsrch)
			&& !lst_add_elem(lst, FOL_MANDEL, &nb))
			return (-1);
		else if (ft_strcmp(av[i], "burning_ship") == 0
			&& !ft_lstfind(*lst, &i, FOL_BURNI, &my_lstsrch)
			&& !lst_add_elem(lst, FOL_BURNI, &nb))
			return (-1);
	}
	return (nb);
}

static int	list_to_fractol(t_list *lst, t_fractol *e, int nb)
{
	int		i;
	int		null;

	i = nb + 1;
	while (--i >= 0)
		e->wins[i] = NULL;
	while (++i < nb)
	{
		if (!(e->wins[i] = (t_win *)malloc(sizeof(t_win))))
			return (0);
		if ((e->wins[i]->type = *(int *)(lst->content)) == FOL_JULIA)
			e->wins[i]->win = mlx_new_window(e->mlx, FOL_WID, FOL_HIG, "Julia");
		else if (*(int *)(lst->content) == FOL_MANDEL)
			e->wins[i]->win = mlx_new_window(e->mlx, FOL_WID, FOL_HIG, "Mandl");
		else if (*(int *)(lst->content) == FOL_BURNI)
			e->wins[i]->win = mlx_new_window(e->mlx, FOL_WID, FOL_HIG, "BuShp");
		lst = lst->next;
		e->wins[i]->img = NULL;
		if (!e->wins[i]->win
			|| !(e->wins[i]->img = mlx_new_image(e->mlx, FOL_WID, FOL_HIG)))
			return (0);
		e->wins[i]->buf = mlx_get_data_addr(e->wins[i]->img, &null,
			&e->wins[i]->line, &null);
	}
	return (1);
}

int			my_parse(int ac, char **av, t_fractol *e)
{
	int		nb;
	t_list	*lst;

	if (ac < 2)
		return (0);
	e->wins = NULL;
	if ((nb = init_list(ac, av, &lst)) < 1)
		return (nb);
	if (!(e->wins = (t_win**)malloc((unsigned long)(nb + 1) * sizeof(t_win *))))
		return (0);
	if (!list_to_fractol(lst, e, nb))
	{
		ft_lstdel(&lst, &my_lstdel);
		return (-1);
	}
	ft_lstdel(&lst, &my_lstdel);
	return (1);
}
