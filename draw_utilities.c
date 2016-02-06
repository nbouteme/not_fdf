/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:50:36 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 02:39:51 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/std.h>
#include "mlx.h"
#include "gfx.h"

int			is_outside(t_graphics *g, t_point a)
{
	if (a.w < 0 || g->dim.w <= a.w)
		return (1);
	if (a.h < 0 || g->dim.h <= a.h)
		return (2);
	return (0);
}

unsigned	get_pixel(t_graphics *g, t_point pos)
{
	if (is_outside(g, pos))
		return (0);
	return (g->fb[pos.h * g->dim.w + pos.w]);
}

void		draw_point_bare(t_graphics *g, t_point pos)
{
	g->fb[pos.h * g->dim.w + pos.w] = g->color;
}

t_drawpara g_d;

//t_drawpara	*draw_para_ctl()
//{

//	return (&d);
//}

int mix(int c1, int c2, float t)
{
	int ret;
	int r;
	int g;
	int i;

	i = 0;
	ret = 0;
	while (i <= 16)
	{
		r = (c1 & (0xFF << i)) >> i;
		g = (c2 & (0xFF << i)) >> i;
		r = (t * r) + (1.0f - t) * g;
		ret |= r << i;
		i += 8;
	}
	return (ret);
}

void		draw_point(t_graphics *g, t_point pos)
{
	t_drawpara *d;

	d = &g_d;
	float pro = (float)(pos.w - d->x1) / ABS(d->dist);
	g->color = mix(d->c1, d->c2, d->dist > 0 ? pro : 1.0f - pro);
	if (is_outside(g, pos))
		return ;
	draw_point_bare(g, pos);
}

void		draw_line(t_graphics *g, t_point a, t_point b)
{
	t_drawpara	*p;

	if (clip(g, &a, &b))
	{
		p = &g_d;
		p->x1 = a.w < b.w ? a.w : b.w;
		p->dist = a.w - b.w;
		draw_line_bare(g, a, b);
	}
}
