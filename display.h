#ifndef DISPLAY_H
#define DISPLAY_H

#include <mlx.h>

typedef struct	s_display
{
	void *conn;
	void *win;
	t_model *model;
}				t_display;

t_display *new_display(t_model *m);

void run_display(t_display *d);

#endif /* DISPLAY_H */
