#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>

#include "parser.h"
#include "display.h"

int disp_handle_key(int key, t_display *d)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(d->conn, d->win);
		exit(42);
	}
	return 0;
}

int disp_expose(t_display *d)
{
	void *fb = mlx_new_image(d->conn, 420, 420);
	int osef;
	
	int *data = (int*)mlx_get_data_addr(fb, &osef, &osef, &osef);
	data[420 * 10 + 42] = 0x00FF0000;
	
	mlx_put_image_to_window(d->conn, d->win, fb, 0, 0);
	mlx_destroy_image(d->conn, fb);
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
	ret->win = mlx_new_window(ret->conn, 420, 420, "FdF");

	mlx_key_hook(ret->win, &disp_handle_key, ret);
	mlx_expose_hook(ret->win, &disp_expose, ret);
	mlx_loop_hook(ret->conn, &disp_expose, ret);
	
	ret->model = m;
	return ret;
}

void run_display(t_display *d)
{
	mlx_loop(d->conn);
}
