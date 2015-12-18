#ifndef MAT_H
#define MAT_H

#include <stdlib.h>
#include <libft.h>
#include <math.h>

typedef float (*t_vec2)[2];
typedef float (*t_vec3)[3];
typedef float (*t_vec4)[4];

typedef const float (*t_cvec3)[3];

typedef float (*t_mat3)[3][3];
typedef float (*t_mat4)[4][4];

/*
** Ne pas inclure directement.
 */
#include "mat3.h"
#include "mat4.h"
#include "vec3.h"
#include "vec4.h"

#endif /* MAT_H */
