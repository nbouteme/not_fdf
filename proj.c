#include "mat.h"

t_mat4 translation(const t_vec3 pos)
{
	t_mat4 reto;
	
	reto = new_mat4_from_a4((float[4]){  1,  0,  0, -(*pos)[0] },
							(float[4]){  0,  1,  0, -(*pos)[1] },
							(float[4]){  0,  0,  1, -(*pos)[2] },
							(float[4]){  0,  0,  0,          1 });
	return reto;
}

t_mat4 mat4_lookat(const t_vec3 eye, const t_vec3 center, const t_vec3 up)
{
	t_mat4 lookat;
	t_mat4 m;
	t_mat4 t;
	t_vec3 f;
	t_vec3 s;
	t_vec3 u;

	f = vec3_normalize(s = vec3_sub(eye, center));
	free(s);
	s = vec3_cross(f, up);
	u = vec3_cross(s, f);
	m = new_mat4_from_a4((float[4]){  (*s)[0],  (*s)[1],  (*s)[2], 0 },
						 (float[4]){  (*u)[0],  (*u)[1],  (*u)[2], 0 },
						 (float[4]){ -(*f)[0], -(*f)[1], -(*f)[2], 0 },
						 (float[4]){        0,        0,        0, 1 });
	t = translation(eye);
	lookat = mat4_mult(m, t);
	free(u);
	free(s);
	free(f);
	free(t);
	free(m);
	return lookat;
}

t_mat4 mat4_pers(float fov, float ar, float near, float far)
{
	t_mat4 m;
	float dist;

	dist = near - far;
	m = new_mat4_from_a4((float[4]){ 1.0f / (ar * (tan(fov/2))),  0, 0, 0 },
						 (float[4]){ 0,  1.0f / tan(fov/2),  0, 0 },
						 (float[4]){ 0, 0, -near - far / dist, (2 * near * far) / dist },
						 (float[4]){ 0, 0, 1, 0 });
	return m;
}
