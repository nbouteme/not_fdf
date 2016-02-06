/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:50:36 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 05:33:48 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/std.h>
#include "mlx.h"
#include "gfx.h"

t_drawpara	*draw_para_ctl(void)
{
	static t_drawpara d;

	return (&d);
}

int			mix(int c1, int c2, float t)
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

float dist(const t_point *a, const t_point *b)
{
	float as;
	float bs;

	as = a->w - b->w;
	bs = a->h - b->h;
	as *= as;
	bs *= bs;
	return (sqrtf(as + bs));
}

void		draw_point(t_graphics *g, t_point pos)
{
	t_drawpara	*d;
	float		pro;

	if (pos.z >= g->z[pos.h * g->dim.w + pos.w])
		return ;
	if (pos.w < 0 || g->dim.w <= pos.w || pos.h < 0 || g->dim.h <= pos.h)
		return ;
	g->z[pos.h * g->dim.w + pos.w] = pos.z;
	d = draw_para_ctl();
	pro = dist(&pos, &d->b) / d->dist;
	g->color = mix(d->c1, d->c2, d->dist > 0 ? pro : 1.0f - pro);
	g->fb[pos.h * g->dim.w + pos.w] = g->color;
}

void		draw_line(t_graphics *g, t_point a, t_point b)
{
	t_drawpara	*p;

	if (!clip(g, &a, &b))
		return ;
	p = draw_para_ctl();
	p->a = a;
	p->b = b;
	p->dist = dist(&a, &b);
	draw_line_bare(g, a, b);
}
