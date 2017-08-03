/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <pbernier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 05:41:49 by pbernier          #+#    #+#             */
/*   Updated: 2017/08/03 15:45:04 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	erro_print(void)
{
	ft_putstr("bad wireframe\n");
	exit(-1);
}

void	error(char *str, int x, t_fdf *e)
{
	int			i;
	static int	ref_h;

	i = -1;
	ref_h = (x == 0) ? e->x_max : ref_h;
	if (ref_h != e->x_max)
		erro_print();
	while (str[++i])
		if (str[i] != '-' && str[i] != '+' && (str[i] < '0' || str[i] > '9'))
			erro_print();
}

int		**rec_coor(int len, char **split, t_fdf *e)
{
	int		i[2];
	int		**ret;
	char	**tmp;

	i[0] = -1;
	if (!(ret = (int **)malloc(sizeof(int *) * len)))
		exit(-1);
	while (split[++i[0]])
	{
		e->x_max = 0;
		i[1] = -1;
		tmp = ft_strsplit(split[i[0]], ' ');
		while (tmp[e->x_max])
			++e->x_max;
		if (!(ret[i[0]] = (int *)malloc(sizeof(int) * e->x_max)))
			exit(-1);
		while (tmp[++i[1]])
		{
			error(tmp[i[1]], i[0], e);
			ret[i[0]][i[1]] = ft_atoi(tmp[i[1]]);
			ft_strdel(&tmp[i[1]]);
		}
		free(tmp);
	}
	return (ret);
}

int		**stock_nbr(int fd, t_fdf *e)
{
	int		**ret;
	char	letter[1];
	char	*file;
	char	**split;

	file = ft_strnew(1);
	split = NULL;
	while (read(fd, letter, 1) > 0)
		file = ft_strjoin_clean_char(&file, letter[0]);
	if (!(split = ft_strsplit(file, '\n')))
		exit(-1);
	while (split[e->y_max])
		++e->y_max;
	if (e->y_max == 0)
		erro_print();
	ret = rec_coor(e->y_max, split, e);
	ft_strdel(&file);
	return (ret);
}
