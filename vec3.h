#ifndef VEC3_H
#define VEC3_H

t_vec3 vec3_copy(const t_vec3 rhs);
float vec3_norme(const t_vec3 rhs);
t_vec3 vec3_normalize(const t_vec3 rhs);
t_vec3 vec3_cross(const t_vec3 a, const t_vec3 b);
t_vec3 vec3_add(const t_vec3 a, const t_vec3 b);
t_vec3 vec3_sub(const t_vec3 a, const t_vec3 b);

#endif /* VEC3_H */
