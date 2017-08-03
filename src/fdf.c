/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <pbernier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:01:07 by pbernier          #+#    #+#             */
/*   Updated: 2017/08/03 15:50:15 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_nbr(t_fdf *e)
{
	e->amp = 0.7;
	e->hor = 0;
	e->ver = 0;
	e->res = (X > Y) ?
	Y / sqrt(pow(e->y_max, 2) + pow(e->x_max, 2)) :
	X / sqrt(pow(e->y_max, 2) + pow(e->x_max, 2));
	e->add = e->res / 3;
}

int		key(int key, t_fdf *e)
{
	int			i;
	static int	space = 1;

	if (key == 53)
		exit(0);
	space *= (key == 49) ? -1 : 1;
	if (space == -1)
		return (0);
	if (key == 15)
		init_nbr(e);
	e->add += (key == 124) ? 1 : 0;
	e->add -= (key == 123) ? 1 : 0;
	e->amp += (key == 126) ? 0.2 : 0;
	e->amp -= (key == 125) ? 0.2 : 0;
	e->hor += (key == 1) ? 15 : 0;
	e->hor -= (key == 13) ? 15 : 0;
	e->ver += (key == 2) ? 15 : 0;
	e->ver -= (key == 0) ? 15 : 0;
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, X, Y);
	e->data = mlx_get_data_addr(e->img, &i, &i, &i);
	place_point(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

t_color	get_color(int r, int g, int b, int a)
{
	t_color	color;

	color.blue = b;
	color.green = g;
	color.red = r;
	color.alpha = a;
	return (color);
}

void	init(t_fdf *e, char *name, int fd)
{
	int		i;

	e->nb = stock_nbr(fd, e);
	init_nbr(e);
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, X, Y, name);
	e->img = mlx_new_image(e->mlx, X, Y);
	e->data = mlx_get_data_addr(e->img, &i, &i, &i);
	e->pix = get_color(244, 131, 66, 0);
}

int		main(int ac, char **av)
{
	int			fd;
	t_fdf		e;

	if (ac != 2)
		ft_putstr("usage : ./fdf file\n");
	if (ac != 2)
		return (-1);
	if ((fd = open(av[1], O_RDONLY)) <= 0)
	{
		ft_putstr("file can't be open: malloc error\n");
		return (-1);
	}
	init(&e, av[1], fd);
	place_point(&e);
	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
	mlx_hook(e.win, 2, 3, key, &e);
	mlx_loop(e.mlx);
	return (0);
}
