/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:50:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 04:27:19 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/std.h>
#include "mlx.h"
#include "gfx.h"

t_graphics	*new_graphics(t_display *d)
{
	int			osef;
	t_graphics	*g;
	int			i;
	int			max;

	g = malloc(sizeof(t_graphics));
	g->d = d;
	g->int_img = mlx_new_image(d->conn, d->dim.w, d->dim.h);
	g->fb = (int*)mlx_get_data_addr(g->int_img, &osef, &osef, &osef);
	g->dim = d->dim;
	i = 0;
	max = g->dim.w * g->dim.h;
	ft_memset(g->fb, 0, max);
	g->z = malloc(4 * max);
	while (i < max)
		g->z[i++] = 0x3F800000;
	g->color = 0x00FFFFFF;
	return (g);
}

void		draw_line_bare(t_graphics *g, t_point a, t_point b)
{
	int oh_boy[7];

	oh_boy[0] = ABS(b.w - a.w);
	oh_boy[1] = ABS(b.h - a.h);
	oh_boy[2] = SIGN(b.w - a.w);
	oh_boy[3] = SIGN(b.h - a.h);
	if ((oh_boy[4] = oh_boy[1] > oh_boy[0]))
		ft_swap_any(&oh_boy[0], &oh_boy[1], sizeof(int));
	oh_boy[5] = 2 * oh_boy[1] - oh_boy[0];
	oh_boy[6] = -1;
	while (++oh_boy[6] < oh_boy[0])
	{
		draw_point(g, a);
		while (oh_boy[5] >= 0)
		{
			oh_boy[5] = oh_boy[5] - 2 * oh_boy[0];
			oh_boy[4] ? (a.w += oh_boy[2]) : (a.h += oh_boy[3]);
		}
		oh_boy[5] = oh_boy[5] + 2 * oh_boy[1];
		oh_boy[4] ? (a.h += oh_boy[3]) : (a.w += oh_boy[2]);
	}
}

t_point		ndc_to_screen(t_graphics *g, t_point n)
{
	int ppn;
	int xoff;
	int yoff;

	if (g->dim.w >= g->dim.h)
	{
		ppn = g->dim.h;
		xoff = (g->dim.w - g->dim.h) >> 1;
		yoff = 0;
	}
	else
	{
		ppn = g->dim.w;
		xoff = 0;
		yoff = (g->dim.h - g->dim.w) >> 1;
	}
	return (t_point){n.w * ppn + xoff, g->dim.w - (n.h * ppn) + yoff, n.z};
}

void		draw_nline(t_graphics *g, t_vec4 n1, t_vec4 n2)
{
	t_point a;
	t_point b;

	a = ndc_to_screen(g, (t_point){(*n1)[0], (*n1)[1], (*n1)[2]});
	b = ndc_to_screen(g, (t_point){(*n2)[0], (*n2)[1], (*n2)[2]});
	draw_line(g, a, b);
}
