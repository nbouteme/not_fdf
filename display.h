#ifndef DISPLAY_H
#define DISPLAY_H

#include <mlx.h>

typedef struct	s_point
{
	int w;
	int h;
}				t_point;

typedef struct s_model t_model;
typedef struct s_graphics t_graphics;

typedef struct	s_display
{
	void *conn;
	void *win;
	t_point dim;
	t_model *model;
	t_graphics *g;
}				t_display;

t_display *new_display(t_model *m);
void run_display(t_display *d);

#endif /* DISPLAY_H */
