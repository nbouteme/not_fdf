#include "mat.h"

t_vec3 vec3_copy(const t_vec3 rhs)
{
	t_vec3 ret;

	ret = malloc(sizeof(*rhs));
	ft_memcpy(ret, rhs, sizeof(*rhs));
	return ret;
}

float vec3_norme(const t_vec3 rhs)
{
	return sqrt(((*rhs)[0] * (*rhs)[0]) +
				((*rhs)[1] * (*rhs)[1]) +
				((*rhs)[2] * (*rhs)[2]));
}

t_vec3 vec3_normalize(const t_vec3 rhs)
{
	float norme;
	t_vec3 ret;

	ret = vec3_copy(rhs);
	norme = vec3_norme(rhs);
	(*ret)[0] /= norme;
	(*ret)[1] /= norme;
	(*ret)[2] /= norme;
	return ret;
}

t_vec3 vec3_cross(const t_vec3 a, const t_vec3 b)
{
	t_vec3 ret;

	ret = malloc(sizeof(*ret));
	(*ret)[0] = (*a)[1] * (*b)[2] - (*a)[2] * (*b)[1];
	(*ret)[1] = (*a)[2] * (*b)[0] - (*a)[0] * (*b)[2];
	(*ret)[2] = (*a)[0] * (*b)[1] - (*a)[1] * (*b)[0];
	return ret;
}

t_vec3 vec3_add(const t_vec3 a, const t_vec3 b)
{
	t_vec3 ret;

	ret = malloc(sizeof(*ret));
	(*ret)[0] = (*a)[0] + (*b)[0];
	(*ret)[1] = (*a)[1] + (*b)[1];
	(*ret)[2] = (*a)[2] + (*b)[2];
	return ret;
}

t_vec3 vec3_sub(const t_vec3 a, const t_vec3 b)
{
	t_vec3 ret;

	ret = malloc(sizeof(*ret));
	(*ret)[0] = (*a)[0] - (*b)[0];
	(*ret)[1] = (*a)[1] - (*b)[1];
	(*ret)[2] = (*a)[2] - (*b)[2];
	return ret;
}
