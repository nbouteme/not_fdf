/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:02:05 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 05:59:33 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

t_mat4	translation(t_cvec3 pos)
{
	t_mat4 reto;

	reto = new_mat4_from_a4((float[4]){ 1, 0, 0, -(*pos)[0] },
							(float[4]){ 0, 1, 0, -(*pos)[1] },
							(float[4]){ 0, 0, 1, -(*pos)[2] },
							(float[4]){ 0, 0, 0, 1 });
	return (reto);
}

float	vec3_dot(t_cvec3 a, t_cvec3 b)
{
	return ((*a)[0] * (*b)[0] +
			(*a)[1] * (*b)[1] +
			(*a)[2] * (*b)[2]);
}

t_mat4	mat4_lookat(t_cvec3 eye, t_cvec3 center, t_cvec3 up)
{
	static float look[4][4];
	static float f[3];
	static float s[3];
	static float u[3];

	vec3_normalize(vec3_sub(&f, center, eye));
	vec3_normalize(vec3_cross(&s, &f, up));
	vec3_cross(&u, &s, &f);
	ft_memcpy(look,
			  &(float[4][4])
			  {{s[0], u[0], -f[0], 0},
			   {s[1], u[1], -f[1], 0},
			   {s[2], u[2], -f[2], 0},
			   {-vec3_dot(&s, eye), -vec3_dot(&u, eye), vec3_dot(&f, eye), 1}}
			  , sizeof(look));
	return (&look);
}

t_mat4	mat4_pers(float fov, float ar, float near, float far)
{
	t_mat4	mper;
	float	dist;
	float	tanf2;

	dist = far - near;
	tanf2 = tan(fov / 2);
	mper = new_mat4_from_a4((float[4]){ 1.0f / (ar * tanf2), 0, 0, 0 },
							(float[4]){ 0, 1.0f / tanf2, 0, 0 },
							(float[4]){ 0, 0, -(near + far) / dist, -1 },
							(float[4]){ 0, 0, -(2 * near * far) / dist, 0 });
	return (mper);
}

t_vec4	project(t_mat4 mvp, t_vec4 n)
{
	t_vec4 ret;

	ret = mat4_m_vec4(mvp, n);
	vec4_sdiv(ret, (*ret)[3]);
	return (ret);
}
