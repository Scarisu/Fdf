/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <pbernier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:01:07 by pbernier          #+#    #+#             */
/*   Updated: 2017/08/01 11:51:06 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		key(int key, t_fdf *e)
{
	int		i;

	if (key == 53)
		exit(0);
	else if (key == 124)
		e->add += 1;
	else if (key == 123)
		e->add -= 1;
	else if (key == 126)
		e->amp += 0.2;
	else if (key == 125)
		e->amp -= 0.2;
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

	//e->add = 24;
	e->add = 2;
	e->amp = 0.8;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, X, Y, name);
	e->nb = stock_nbr(fd, e);
	e->img = mlx_new_image(e->mlx, X, Y);
	e->data = mlx_get_data_addr(e->img, &i, &i, &i);
	e->pix = get_color(244, 131, 66, 0);
}

int		main(int ac, char **av)
{
	int			fd;
	t_fdf		e;

	if (ac != 2 || !(fd = open(av[1], O_RDONLY)))
		return (-1);
	init(&e, av[1], fd);
	place_point(&e);
	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
	mlx_key_hook(e.win, key, &e);
	mlx_loop(e.mlx);
	return (0);
}
