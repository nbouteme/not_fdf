/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 01:34:37 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 06:35:11 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

static void	clip_3d(t_vec4 v1, t_vec4 v2)
{
	float	n;

	n = ((*v1)[3] - 0.01f) / ((*v1)[3] - (*v2)[3]);
	(*v2)[0] = ((1.0f - n) * (*v1)[0]) + (n * (*v2)[0]);
	(*v2)[1] = ((1.0f - n) * (*v1)[1]) + (n * (*v2)[1]);
	(*v2)[2] = ((1.0f - n) * (*v1)[2]) + (n * (*v2)[2]);
	(*v2)[3] = 0.1f;
}

static int	clip_plane(t_display *d, t_vec4 *rarb)
{
	t_vec4	a;
	t_vec4	b;

	a = rarb[2];
	b = rarb[3];
	if (((*a)[3] <= 0.1f) && ((*b)[3] <= 0.1f))
		return (0);
	if (((*a)[3] >= 0.1f) && ((*b)[3] < 0.1f))
		clip_3d(a, b);
	else if (((*a)[3] <= 0.1f) && ((*b)[3] > 0.1f))
		clip_3d(b, a);
	rarb[2] = to_screen_space(d->dim, vec4_sdiv(a, (*a)[3]));
	rarb[3] = to_screen_space(d->dim, vec4_sdiv(b, (*b)[3]));
	return (1);
}

void		render_line(t_display *d, t_mat4 mvp, t_vertex *ptr)
{
	t_vertex	ab[2];
	t_vec4		rar[4];
	int			i;
	t_drawpara	*p;

	i = 0;
	p = draw_para_ctl();
	rar[2] = &(float[]){0, 0, 0, 0};
	rar[3] = &(float[]){0, 0, 0, 0};
	while (i < (2 * (2 * (d->model->h) * (d->model->w)
					- d->model->w - d->model->h)))
	{
		ab[0] = ptr[d->model->elements[i++]];
		ab[1] = ptr[d->model->elements[i++]];
		rar[0] = &(float[]){ab[0].x, ab[0].y, ab[0].z, 1};
		rar[1] = &(float[]){ab[1].x, ab[1].y, ab[1].z, 1};
		ft_memcpy(rar[2], mat4_m_vec4(mvp, rar[0]), 16);
		ft_memcpy(rar[3], mat4_m_vec4(mvp, rar[1]), 16);
		p->c1 = ab[0].color;
		p->c2 = ab[1].color;
		if (clip_plane(d, rar))
			draw_line(d->g, (t_point){(*rar[2])[0], (*rar[2])[1], (*rar[2])[2]},
					(t_point){(*rar[3])[0], (*rar[3])[1], (*rar[3])[2]});
	}
}
