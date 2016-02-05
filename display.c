/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:17:17 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/05 07:26:14 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "mlx.h"
#include "key_defs.h"

t_vec4		to_screen_space(t_point dim, t_vec4 n)
{
	vec4_sadd(vec4_smul(n, 0.5f), 0.5f);
	(*n)[0] *= dim.w;
	(*n)[1] *= dim.h;
	return (n);
}

static void clip_3d(t_vec4 v1, t_vec4 v2)
{
	float	n;
	n = ((*v1)[3] - 0.01f) / ((*v1)[3] - (*v2)[3]);
	(*v2)[0] = ((1.0f - n) * (*v1)[0]) + (n * (*v2)[0]);
	(*v2)[1] = ((1.0f - n) * (*v1)[1]) + (n * (*v2)[1]);
	(*v2)[2] = ((1.0f - n) * (*v1)[2]) + (n * (*v2)[2]);
	(*v2)[3] = ((1.0f - n) * (*v1)[3]) + (n * (*v2)[3]);
	//(*v2)[3] = 0.1f;
}

static void clip_3d2(t_vec4 v1, t_vec4 v2)
{
	float	n;
	n = ((*v2)[3] - 0.01f) / ((*v2)[3] - (*v1)[3]);
	(*v2)[0] = ((1.0f - n) * (*v2)[0]) + (n * (*v1)[0]);
	(*v2)[1] = ((1.0f - n) * (*v2)[1]) + (n * (*v1)[1]);
	(*v2)[2] = ((1.0f - n) * (*v2)[2]) + (n * (*v1)[2]);
	(*v2)[3] = ((1.0f - n) * (*v2)[3]) + (n * (*v1)[3]);
	(*v2)[3] = 0.1f;
}

static int clip_plane(t_display *d, t_mat4 mvp, t_vec4 *rarb)
{
	t_vec4	a;
	t_vec4	b;

	a = mat4_m_vec4(mvp, rarb[0]);
	b = mat4_m_vec4(mvp, rarb[1]);
	rarb[2] = a;
	rarb[3] = b;
	if (((*a)[3] < 0.1f) && ((*b)[3] < 0.1f))
		return (0);
	if (((*a)[3] > 0.1f) && ((*b)[3] < 0.1f))
		clip_3d(a, b);
	else if (((*a)[3] < 0.1f) && ((*b)[3] > 0.1f))
		clip_3d2(b, a);
	rarb[2] = to_screen_space(d->dim, vec4_sdiv(a, (*a)[3]));
	rarb[3] = to_screen_space(d->dim, vec4_sdiv(b, (*b)[3]));
	//(void)d;
	return (1);
}

static void	render_line(t_display *d, t_mat4 mvp, t_vertex *ptr)
{
	t_vertex	a;
	t_vertex	b;
	t_vec4		papbrarb[4];
	int			i;

	i = 0;
	while (i < (2 * (2 * (d->model->h) * (d->model->w)
					- d->model->w - d->model->h)))
	{
		a = ptr[d->model->elements[i++]];
		b = ptr[d->model->elements[i++]];
		papbrarb[0] = &(float[]){a.x, a.y, a.z, 1};
		papbrarb[1] = &(float[]){b.x, b.y, b.z, 1};
		if(a.z == 50)
			putchar(0);
		if (clip_plane(d, mvp, papbrarb))
			draw_line(d->g, (t_point){(*papbrarb[2])[0], (*papbrarb[2])[1]},
					(t_point){(*papbrarb[3])[0], (*papbrarb[3])[1]});
		free(papbrarb[2]);
		free(papbrarb[3]);
	}
}

static void	redraw(t_display *d)
{
	t_mat4		tmp;
	t_mat4		mvp;
	t_vec3		tmp3;

	free(d->camera);
	tmp3 = vec3_copy(vec3_zero());
	(*tmp3)[0] = d->model->w / 2;
	(*tmp3)[1] = d->model->h / 2;
	d->camera = mat4_lookat(d->position, tmp3, vec3_up());
	free(tmp3);
	free(d->proj);
	d->proj = mat4_pers(M_PI_4, (float)d->dim.w / d->dim.h, 0.1f, 1000);
	tmp = mat4_mult(d->camera, d->model->model);
	mvp = mat4_mult(tmp, d->proj);
	render_line(d, mvp, d->model->verts);
	free(tmp);
	free(mvp);
}

int			disp_expose(t_display *d)
{
	present(d->g);
	mlx_do_sync(d->conn);
	return (0);
}

int			disp_handle_key(t_display *d)
{
	if (is_key_pressed(ESCAPE))
	{
		mlx_destroy_window(d->conn, d->win);
		exit(42);
	}
	if (is_key_pressed(LEFT))
		--(*d->position)[0];
	if (is_key_pressed(RIGHT))
		++(*d->position)[0];
	if (is_key_pressed(UP))
		--(*d->position)[1];
	if (is_key_pressed(DOWN))
		++(*d->position)[1];
	if (is_key_pressed(KP_ADD))
		--(*d->position)[2];
	if (is_key_pressed(KP_SUBTRACT))
		++(*d->position)[2];
	clear_graphics(d->g);
	//disp_expose(d);
	redraw(d);
	return (0);
}
