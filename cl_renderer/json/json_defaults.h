#ifndef JSON_DEFAULTS_H
# define JSON_DEFAULTS_H

# include "json_parse.h"

# define GLOBAL_MATERIAL MATERIAL_WHITE
# define GLOBAL_POSITION (t_vector3){0., 0., 0.}

# define CAMERA_POS (RT_F4_API){0., 0., -30.}
# define CAMERA_ROT (RT_F4_API){0., 0., 0.}

# define AMBIENT_NAME "Ambient light"
# define AMBIENT_MATERIAL GLOBAL_MATERIAL

# define POINT_NAME "Point light"
# define POINT_MATERIAL GLOBAL_MATERIAL
# define POINT_POSITION GLOBAL_POSITION

# define DIRECT_NAME "Direct light"
# define DIRECT_MATERIAL GLOBAL_MATERIAL
# define DIRECT_DIRECTION (t_vector3){0., -1., 0.}

# define SPHERE_NAME "Sphere"
# define SPHERE_MATERIAL GLOBAL_MATERIAL
# define SPHERE_POSITION GLOBAL_POSITION
# define SPHERE_RADIUS 1.

# define PLANE_NAME "Plane"
# define PLANE_MATERIAL GLOBAL_MATERIAL
# define PLANE_POSITION GLOBAL_POSITION
# define PLANE_NORMAL (t_vector3){0., 1., 0.}

# define CONE_NAME "Cone"
# define CONE_MATERIAL GLOBAL_MATERIAL
# define CONE_TOP (t_vector3){0., -.5f, 0.}
# define CONE_BOTTOM (t_vector3){0., .5f, 0.}
# define CONE_RADIUS 1.

# define CYLINDER_NAME "Cylinder"
# define CYLINDER_MATERIAL GLOBAL_MATERIAL
# define CYLINDER_TOP (t_vector3){0., -.5f, 0.}
# define CYLINDER_BOTTOM (t_vector3){0., .5f, 0.}
# define CYLINDER_RADIUS 1.

# define BOX_NAME "Box"
# define BOX_MATERIAL GLOBAL_MATERIAL
# define BOX_POSITION GLOBAL_POSITION
# define BOX_SIZE (t_vector3){1., 1., 1.}

# define PARABOLOID_NAME "Paraboloid"
# define PARABOLOID_MATERIAL GLOBAL_MATERIAL
# define PARABOLOID_EXTREMUM (t_vector3){0., 2., 0.}
# define PARABOLOID_AXIS (t_vector3){0., 1., 0.}
# define PARABOLOID_RADIUS 1.

# define MOEBIUS_NAME "Moebius strip"
# define MOEBIUS_MATERIAL GLOBAL_MATERIAL
# define MOEBIUS_POSITION GLOBAL_POSITION
# define MOEBIUS_RADIUS 1.
# define MOEBIUS_HALFWIDTH .5f

# define TORUS_NAME "Torus"
# define TORUS_MATERIAL GLOBAL_MATERIAL
# define TORUS_POSITION GLOBAL_POSITION
# define TORUS_RADIUS 1.
# define TORUS_WIDTH .5f

# define MANDELBULB_NAME "Mandelbulb"
# define MANDELBULB_MATERIAL GLOBAL_MATERIAL
# define MANDELBULB_POSITION GLOBAL_POSITION
# define MANDELBULB_ITERATIONS 4
# define MANDELBULB_POWER 1.1f

# define JULIA_NAME "Julia"
# define JULIA_MATERIAL GLOBAL_MATERIAL
# define JULIA_POSITION GLOBAL_POSITION
# define JULIA_ITERATIONS 4
# define JULIA_VALUE (t_vector3){1., 1., 1.}

# define CSG_NAME "CSG"
# define CSG_MATERIAL GLOBAL_MATERIAL
# define CSG_POSITIVE 0
# define CSG_NEGATIVE 1

#endif