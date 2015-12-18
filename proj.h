#ifndef PROJ_H
#define PROJ_H

t_mat4 translation(t_cvec3 pos);
t_mat4 mat4_lookat(t_cvec3 eye, t_cvec3 center, t_cvec3 up);
t_mat4 mat4_pers(float fov, float ar, float near, float far);


#endif /* PROJ_H */
