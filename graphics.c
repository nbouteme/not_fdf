#include <stdlib.h>
#include "display.h"
#include "graphics.h"

t_graphics *new_graphics(t_display *d)
{
	int osef;
	t_graphics *g;

	g = malloc(sizeof(t_graphics));
	g->d = d;
	g->int_img = mlx_new_image(d->conn, d->dim.w, d->dim.h);
	g->fb = (int*) mlx_get_data_addr(g->int_img, &osef, &osef, &osef);
	g->dim.w = d->dim.w;
	g->dim.h = d->dim.h;
	g->color = 0x00FFFFFF;
	return g;
}

int is_outside(t_graphics *g, t_point a)
{
	if(g->dim.w < a.w)
		return 1;
	if(g->dim.h < a.h)
		return 2;
	return 0;
}

unsigned get_pixel(t_graphics *g, t_point pos)
{
	if(is_outside(g, pos))
		return 0;
	return g->fb[pos.h * g->dim.w + pos.w];
}

void draw_point_bare(t_graphics *g, t_point pos)
{
	g->fb[pos.h * g->dim.w + pos.w] = g->color;	
}

void draw_point(t_graphics *g, t_point pos)
{
	if(is_outside(g, pos))
		return ;
	draw_point_bare(g, pos);
}

#include <stdio.h>
#include <libft.h>

void draw_line(t_graphics *g, t_point a, t_point b)
{
	int hwg[7];

	hwg[0] = (b.w - a.w < 0 ? -b.w - a.w : b.w - a.w);
	hwg[1] = (b.h - a.h < 0 ? -b.h - a.h : b.h - a.h);
	hwg[2] = (0x80000000 & b.w - a.w ? -1 : 1);
	hwg[3] = (0x80000000 & b.h - a.h ? -1 : 1);
	if ((hwg[5] = hwg[1] > hwg[0]))
		ft_swap_any(&hwg[0], &hwg[1], sizeof(int));
	hwg[6] = 2 * (hwg[1] - hwg[0]);
	hwg[4] = -1;
	while (++hwg[4] < hwg[0])
	{
		draw_point(g, a);
		while (hwg[6] >= 0)
		{
			hwg[6] -= 2 * hwg[0];
			hwg[5] ? (a.w += hwg[2]) : (a.h += hwg[3]);
		}
		hwg[6] += 2 * hwg[1];
		hwg[5] ? (a.h += hwg[3]) : (a.w += hwg[2]);
	}
}

void present(t_graphics *g)
{
	mlx_put_image_to_window(g->d->conn, g->d->win, g->int_img, 0, 0);
}
