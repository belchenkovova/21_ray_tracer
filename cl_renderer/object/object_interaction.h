#ifndef OBJECT_INTERACTION_H
# define OBJECT_INTERACTION_H

# include "assert.h"
# include "f4.h"
# include "object_definition.h"
# include "object_x.h"
# include "rt_float.h"

# include <stdarg.h>

void				object_build(
					t_object *space,
					t_object_type type,
					t_material material,
					...);

void				object_sphere_build(t_object *space, va_list *args);
void				object_plane_build(t_object *space, va_list *args);
void				object_cone_build(t_object *space, va_list *args);
void				object_cylinder_build(t_object *space, va_list *args);
void				object_paraboloid_build(t_object *space, va_list *args);
void                object_moebius_build(t_object *space, va_list *args);

void                object_fractal_julia_build(t_object *space, va_list *args);

#endif
