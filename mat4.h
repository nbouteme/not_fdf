#ifndef MAT4_H
#define MAT4_H

t_mat4 new_mat4();
t_mat4 new_mat4_from_a4(const float x[4], const float y[4],
						const float z[4], const float w[4]);
t_mat4 new_mat4_from_data(const float *data);
t_mat4 mat4_mult(const t_mat4 a, const t_mat4 b);
t_mat4 mat4_add(t_mat4 a, t_mat4 b);

#endif /* MAT4_H */
