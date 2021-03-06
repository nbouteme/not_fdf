/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:36:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 05:26:39 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include <libft/std.h>
# include "math.h"

# define SIGN(x) ((x > 0) ? 1 : ((x < 0)? -1 : 0))
# define ABS(x) ((x < 0) ? -(x) : (x))

typedef struct s_display	t_display;

typedef struct				s_point
{
	int						w;
	int						h;
	float					z;
}							t_point;

typedef struct				s_drawpara
{
	t_point a;
	t_point b;
	float	dist;
	int		c1;
	int		c2;
}							t_drawpara;

typedef struct				s_graphics
{
	void					*int_img;
	float					*z;
	int						*fb;
	t_display				*d;
	t_point					dim;
	unsigned				color;
}							t_graphics;

typedef struct				s_sparse_model
{
	t_dlisthead				*verts;
	int						w;
	int						h;
}							t_sparse_model;

typedef struct				s_vertex
{
	int						x;
	int						y;
	int						z;
	unsigned				color;
}							t_vertex;

typedef struct				s_model
{
	t_vertex				*verts;
	int						*elements;
	t_mat4					model;
	int						w;
	int						h;
	size_t					e_sz;
}							t_model;

void						draw_point_bare(t_graphics *g, t_point pos);
void						draw_point(t_graphics *g, t_point pos);
void						draw_nline(t_graphics *g, t_vec4 n1, t_vec4 n2);
int							clip(t_graphics *g, t_point *a, t_point *b);
t_graphics					*new_graphics(t_display *d);
unsigned					get_pixel(t_graphics *g, t_point pos);
int							is_outside(t_graphics *g, t_point a);
void						present(t_graphics *g);
void						clear_graphics(t_graphics *g);
void						draw_line(t_graphics *g, t_point a, t_point b);
int							disp_expose(t_display *d);
void						draw_line_bare(t_graphics *g, t_point a, t_point b);
void						render_line(t_display *d, t_mat4 mvp,
										t_vertex *ptr);
t_vec4						to_screen_space(t_point dim, t_vec4 n);
t_drawpara					*draw_para_ctl();
#endif
