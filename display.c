/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:17:17 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 06:28:35 by nbouteme         ###   ########.fr       */
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
	float		tmp[4][4];
	float		mvp[4][4];

	ft_memcpy(d->camera, mat4_lookat(d->position, d->center, vec3_up()),
			sizeof(*d->camera));
	ft_memcpy(tmp, mat4_mult(d->camera, d->model->model), sizeof(tmp));
	ft_memcpy(mvp, mat4_mult(&tmp, d->proj), sizeof(mvp));
	render_line(d, &mvp, d->model->verts);
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
