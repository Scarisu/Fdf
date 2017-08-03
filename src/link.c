/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <pbernier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 00:15:50 by pbernier          #+#    #+#             */
/*   Updated: 2017/08/03 14:13:40 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	conv_img(int x, int y, t_fdf *e)
{
	int	result;

	if (x > X || y > Y || x < 0 || y < 0)
		return ;
	result = x + (X * y);
	((t_color *)e->data)[result] = e->pix;
}

void	bresenham(int st[2], int en[2], t_fdf *e)
{
	t_line	l;

	l.dx = abs(en[0] - st[0]);
	l.dy = abs(en[1] - st[1]);
	l.sx = st[0] < en[0] ? 1 : -1;
	l.sy = st[1] < en[1] ? 1 : -1;
	l.err = (l.dx > l.dy ? l.dx : -l.dy) / 2;
	while (1)
	{
		if (st[0] < X && st[0] >= 0 && st[1] < Y && st[1] >= 0)
			conv_img(st[0], st[1], e);
		if (st[0] == en[0] && st[1] == en[1])
			break ;
		l.e2 = l.err;
		if (l.e2 > -l.dx)
		{
			l.err -= l.dy;
			st[0] += l.sx;
		}
		if (l.e2 < l.dy)
		{
			l.err += l.dx;
			st[1] += l.sy;
		}
	}
}

void	place_line(t_fdf *e, t_place *l)
{
	while (++l->i[0] < e->y_max)
	{
		l->i[1] = -1;
		while (++l->i[1] < e->x_max)
		{
			if (l->i[1] + 1 < e->x_max)
				bresenham((int[2]){l->st[0] + l->i[1] * l->sp - l->rot_v,
				l->st[1] + l->i[0] * l->sp - e->nb[l->i[0]][l->i[1]] * e->amp +
				l->rot_h}, (int[2]){l->st[0] + (l->i[1] + 1) * l->sp - l->rot_v,
				l->st[1] + l->i[0] * l->sp - e->nb[l->i[0]][l->i[1] + 1] *
				e->amp + (l->rot_h + l->inc)}, e);
			if (l->i[0] + 1 < e->y_max)
				bresenham((int[2]){l->st[0] + l->i[1] * l->sp - l->rot_v,
				l->st[1] + l->i[0] * l->sp - e->nb[l->i[0]][l->i[1]] * e->amp +
				l->rot_h}, (int[2]){l->st[0] + l->i[1] * l->sp - (l->rot_v +
				l->inc), l->st[1] + (l->i[0] + 1) * l->sp -
				e->nb[l->i[0] + 1][l->i[1]] * e->amp + l->rot_h}, e);
			l->rot_h += l->inc;
		}
		l->rot_v += l->inc;
		l->rot_h = 0;
	}
}

void	place_point(t_fdf *e)
{
	t_place		l;

	l.rot_h = 0;
	l.rot_v = 0;
	ft_memcpy(l.i, ((int[2]){-1, -1}), sizeof(int[2]));
	if (e->add >= 3 * e->res)
		e->add = -e->res;
	else if (e->add <= -e->res)
		e->add = 3 * e->res;
	l.inc = (e->add);
	if (e->res >= l.inc)
		l.sp = sqrt(pow(e->res, 2) - pow(l.inc, 2));
	else
	{
		l.inc -= (l.inc - e->res) * 2;
		l.sp = -sqrt(pow(e->res, 2) - pow(l.inc, 2));
	}
	ft_memcpy(l.st, ((int[2])
	{(X - (e->x_max * l.sp) + (e->y_max - 1) * l.inc) / 2 + e->ver,
		(Y - (e->y_max * l.sp) - (e->x_max - 1) * l.inc) / 2 + e->hor}),
		sizeof(int[2]));
	place_line(e, &l);
}
