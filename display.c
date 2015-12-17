#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>

#include "parser.h"
#include "display.h"
#include "graphics.h"

int disp_handle_key(int key, t_display *d)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(d->conn, d->win);
		exit(42);
	}
	return 0;
}

void draw_line(t_graphics *g, t_point a, t_point b);

int disp_expose(t_display *d)
{
	t_point arr[] = {
		(t_point){50, 50},
		(t_point){200, 50},
		(t_point){350, 50},
		(t_point){50, 200},
		(t_point){350, 200},
		(t_point){50, 350},
		(t_point){200, 350},
		(t_point){350, 350}
	};
	t_graphics *g;
	g = d->g;
	draw_line(g, arr[1], arr[6]);
	draw_line(g, arr[3], arr[4]);

	draw_line(g, arr[0], arr[3]);
	present(g);
	return 0;
}

int disp_loop(t_display *d)
{
	(void)d;
	return 0;
}

t_display *new_display(t_model *m)
{
	t_display *ret;

	ret = malloc(sizeof(*ret));
	ret->conn = mlx_init();
	ret->dim.w = 420;
	ret->dim.h = 420;
	ret->win = mlx_new_window(ret->conn, ret->dim.w, ret->dim.h, "FdF");
	ret->g = new_graphics(ret);
	ret->model = m;
	mlx_key_hook(ret->win, &disp_handle_key, ret);
	mlx_expose_hook(ret->win, &disp_expose, ret);
	mlx_loop_hook(ret->conn, &disp_expose, ret);	
	return ret;
}

void run_display(t_display *d)
{
	mlx_loop(d->conn);
}
