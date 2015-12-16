#ifndef MAT3_H
#define MAT3_H

t_mat3 new_mat3();
t_mat3 new_mat3_from_data(const float *data);
t_mat3 mat3_mult(t_mat3 a, t_mat3 b);
t_mat3 mat3_add(t_mat3 a, t_mat3 b);

#endif /* MAT3_H */
