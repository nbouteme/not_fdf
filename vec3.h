#ifndef VEC3_H
#define VEC3_H

t_vec3 vec3_copy(t_cvec3 rhs);
float vec3_norme(t_cvec3 rhs);
t_vec3 vec3_normalize(t_cvec3 rhs);
t_vec3 vec3_cross(t_cvec3 a, t_cvec3 b);
t_vec3 vec3_add(t_cvec3 a, t_cvec3 b);
t_vec3 vec3_sub(t_cvec3 a, t_cvec3 b);
t_cvec3 vec3_up();
t_cvec3 vec3_zero();

#endif /* VEC3_H */
