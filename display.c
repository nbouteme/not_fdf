/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:17:17 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 02:13:03 by nbouteme         ###   ########.fr       */
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

void		redraw(t_display *d)
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
	redraw(d);
	return (0);
}
