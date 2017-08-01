/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbernier <pbernier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 10:01:19 by pbernier          #+#    #+#             */
/*   Updated: 2017/07/31 16:59:54 by pbernier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define X 1280
# define Y 720

# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# include <math.h>

typedef struct		s_line
{
	int				dx;
	int				sx;
	int				dy;
	int				sy;
	int				err;
	int				e2;
}					t_line;

typedef struct		s_place
{
	int			rot_h;
	int			rot_v;
	float		inc;
	int			i[2];
	int			st[2];
	int			res;
	int			sp;
}					t_place;

typedef struct		s_color
{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
	unsigned char	alpha;
}					t_color;

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				**nb;
	int				x_max;
	int				y_max;
	float			add;
	float			amp;
	t_color			pix;
}					t_fdf;

int					**stock_nbr(int fd, t_fdf *e);
void				conv_img(int x, int y, t_fdf *e);
void				place_point(t_fdf *e);
void				link_pts(int *st, int *en);

#endif
