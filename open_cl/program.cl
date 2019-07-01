#include "parameters.h"

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							VECTOR3
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct		    	s_vector3
{
	float					x;
	float					y;
	float					z;
}					    	t_vector3;

static float				vector3_length(const t_vector3 *me)
{
	return (sqrt(me->x * me->x + me->y * me->y + me->z * me->z));
}

static float				vector3_s_length(const t_vector3 me)
{
	return (sqrt(me.x * me.x + me.y * me.y + me.z * me.z));
}

static void					vector3_normalize(t_vector3 *me)
{
	float				    length;

	length = vector3_length(me);
	me->x /= length;
	me->y /= length;
	me->z /= length;
}

static t_vector3			vector3_s_normalize(t_vector3 me)
{
	float				    length;

	length = vector3_length(&me);
	me.x /= length;
	me.y /= length;
	me.z /= length;
	return (me);
}

static t_vector3			vector3_normalized(const t_vector3 *me)
{
	t_vector3				result;

	result = *me;
	vector3_normalize(&result);
	return (result);
}

static float	 			vector3_dot(const t_vector3 *v1, const t_vector3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

static float	 			vector3_s_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}


static t_vector3	    	vector3_cross(const t_vector3 *v1, const t_vector3 *v2)
{
	t_vector3		    	result;

	result.x = v1->y * v2->z - v1->z * v2->y;
	result.y = v1->z * v2->x - v1->x * v2->z;
	result.z = v1->x * v2->y - v1->y * v2->x;
	return (result);
}

static t_vector3			vector3_s_cross(t_vector3 v1, t_vector3 v2)
{
	t_vector3		    	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

static t_vector3	    	vector3_sub(t_vector3 *v1, t_vector3 *v2)
{
	t_vector3		    	result;

	result.x = v1->x - v2->x;
	result.y = v1->y - v2->y;
	result.z = v1->z - v2->z;
	return (result);
}

static t_vector3			vector3_s_sub(t_vector3 v1, t_vector3 v2)
{
	t_vector3		    	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

static void					vector3_sub_eq(t_vector3 *v1, const t_vector3 *v2)
{
	v1->x -= v2->x;
	v1->y -= v2->y;
	v1->z -= v2->z;
}

static void			    	vector3_s_sub_eq(t_vector3 *v1, t_vector3 v2)
{
	v1->x -= v2.x;
	v1->y -= v2.y;
	v1->z -= v2.z;
}


static t_vector3			vector3_add(const t_vector3 *v1, const t_vector3 *v2)
{
	t_vector3		    	result;

	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	result.z = v1->z + v2->z;
	return (result);
}

static t_vector3			vector3_s_add(t_vector3 v1, t_vector3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

static void					vector3_add_eq(t_vector3 *v1, const t_vector3 *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
	v1->z += v2->z;
}

static void			    	vector3_s_add_eq(t_vector3 *v1, t_vector3 v2)
{
	v1->x += v2.x;
	v1->y += v2.y;
	v1->z += v2.z;
}

static t_vector3			vector3_mul(const t_vector3 *v1, float	 k)
{
	t_vector3		    	result;

	result.x = v1->x * k;
	result.y = v1->y * k;
	result.z = v1->z * k;
	return (result);
}

static t_vector3			vector3_s_mul(t_vector3 v1, float	 k)
{
	v1.x *= k;
	v1.y *= k;
	v1.z *= k;
	return (v1);
}

static void			    	vector3_mul_eq(t_vector3 *v1, float	 k)
{
	v1->x = v1->x * k;
	v1->y = v1->y * k;
	v1->z = v1->z * k;
}

static t_vector3			vector3_div(const t_vector3 *v1, float	 k)
{
	t_vector3		    	result;

	result.x = v1->x / k;
	result.y = v1->y / k;
	result.z = v1->z / k;
	return (result);
}

static t_vector3			vector3_s_div(t_vector3 v1, float	 k)
{
	t_vector3		    	result;

	result.x = v1.x / k;
	result.y = v1.y / k;
	result.z = v1.z / k;
	return (result);
}

static void					vector3_div_eq(t_vector3 *v1, float	 k)
{
	v1->x = v1->x / k;
	v1->y = v1->y / k;
	v1->z = v1->z / k;
}

static float				*vector3_iter(t_vector3 *me, int i)
{
	if (i < 0 || i > 3)
		return (0);
	return (&me->x + i);
}

static void					vector3_rotate_x(t_vector3 *me, float	 theta)
{
	t_vector3		    	copy;

	copy = *me;
	me->y = copy.y * cos(theta) + copy.z * sin(theta);
	me->z = -1 * copy.y * sin(theta) + copy.z * cos(theta);
}

static void					vector3_rotate_y(t_vector3 *me, float	 theta)
{
	t_vector3		    	copy;

	copy = *me;
	me->x = copy.x * cos(theta) + copy.z * sin(theta);
	me->z = -1 * copy.x * sin(theta) + copy.z * cos(theta);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							COLOR
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct			    s_rgb
{
	unsigned char		    b;
	unsigned char		    g;
	unsigned char		    r;
	unsigned char		    a;
}						    t_rgb;

typedef union			    u_color
{
	int					    mix;
	t_rgb				    rgb;
}						    t_color;

static int                  color_unpack(t_vector3 vector)
{
    t_color                 color;
	float	 	    	    *ptr;
	int 			        counter;
	float	 	    	    left;

	ptr = &vector.x;
	counter = 0;
	left = 0.;
	while (counter++ < 3)
	{
		if (*ptr > 1.)
		{
			left += *ptr - 1.;
			*ptr = 1.;
		}
		ptr++;
	}
	color.rgb.a = 0;
    color.rgb.r = (unsigned char)(255. * vector.x);
    color.rgb.g = (unsigned char)(255. * vector.y);
    color.rgb.b = (unsigned char)(255. * vector.z);
    return (color.mix);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							RAY
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

# define RAY_T_MIN	    	0.001
# define RAY_T_MAX	    	INFINITY

typedef	struct		    	s_ray
{
	t_vector3		    	origin;
	t_vector3		    	direction;
	float	 				t;
}					    	t_ray;

static t_vector3		    ray_intersect(const t_ray *me)
{
	t_vector3		        tmp;

	tmp = vector3_mul(&me->direction, me->t);
	return (vector3_add(&me->origin, &tmp));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//						    LIGHT
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum		        e_light_type
{
	light_ambient,
	light_point,
	light_directional
}					        t_light_type;

typedef	struct 		        s_light
{
	t_light_type	        type;
	float				    intensity;
	t_vector3		        vector;
}					        t_light;

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//						    MATERIAL
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 		        s_material
{
	t_vector3		        color;
	float	 	            diffuse;
	float	 	            specular;
	float	 	            reflect;
}					        t_material;

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//						    SHAPE
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


# define SHAPE_ID_SPHERE	0
# define SHAPE_ID_PLANE		1
# define SHAPE_ID_CYLINDER	2
# define SHAPE_ID_CONE		3
# define SHAPE_ID_AABB		4

typedef	struct 				s_shape
{
	int 					id;
	unsigned char			data[SHAPE_DATA_SIZE_RESERVE];
	t_material				material;
	int						highlight;
}							t_shape;


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//						    INTERSECTION
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct				s_intersection
{
	t_ray					ray;
	t_vector3				normal;
	float         			diffuse_intensity;
	float         			specular_intensity;
	t_vector3           	color;
	t_material				material;
	float 					shadow_ratio;
	int 					highlight;
}							t_intersection;

static void				    intersection_reset(t_intersection *me)
{
	me->ray.t = RAY_T_MAX;
	me->diffuse_intensity = 0.;
	me->specular_intensity = 0.;
	me->shadow_ratio = 1.;
}

static t_vector3        	intersection_light_direction
                        	(t_intersection *intersection,
                        	constant t_light *light)
{
	t_vector3           	temp[3];

	if (light->type == light_directional)
		temp[0] = light->vector;
	else if (light->type == light_point)
	{
		temp[1] = ray_intersect(&intersection->ray);
		temp[2] = light->vector;
		temp[0] = vector3_sub(temp + 2, temp + 1);
	}
	return (temp[0]);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							SPHERE
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 				s_sphere_data
{
	t_vector3				center;
	float	 				radius;
}							t_sphere_data;

static int     				sphere_intersect
							(constant t_shape *shape,
							t_intersection *intersection)
{
	constant t_sphere_data	*ptr;
	t_sphere_data			data;
	float					k[3];
	float					t;
	float					discriminant;
	t_vector3				temp;

    ptr = (constant t_sphere_data *)shape->data;
    data.center = ptr->center;
    data.radius = ptr->radius;
	k[0] = vector3_dot(&intersection->ray.direction, &intersection->ray.direction);
	temp = vector3_sub(&intersection->ray.origin, &data.center);
	k[1] = 2 * vector3_dot(&temp, &intersection->ray.direction);
	k[2] = vector3_dot(&temp, &temp) - data.radius * data.radius;
	discriminant = k[1] * k[1] - 4 * k[0] * k[2];
	if (discriminant < 0.f)
		return (0);
	t = (-k[1] - sqrt(discriminant)) / (2 * k[0]);
	if (t <= RAY_T_MIN || t >= intersection->ray.t)
		return (0);
	intersection->ray.t = t;
	temp = ray_intersect(&intersection->ray);
	intersection->normal = vector3_sub(&temp, &data.center);
	vector3_normalize(&intersection->normal);
	intersection->color = shape->material.color;
	intersection->material = shape->material;
	intersection->highlight = shape->highlight;
	return (1);
}

/*

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							PLANE
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 				s_plane_data
{
	t_vector3				position;
	t_vector3				normal;
}							t_plane_data;

static int 			    	cl_plane_intersect
	                    	(constant t_shape_cl *shape,
	                    	constant void *data_ptr,
	                    	t_intersection_cl *intersection)
{
	t_plane_data	    	*data;
	t_vector3		    	temp[2];
	float	 	    		value[3];

	data = (t_plane_data *)data_ptr;
	if (!(value[0] = vector3_dot(&intersection->ray.direction, &data->normal)))
		return (0);
	temp[0] = vector3_sub(&data->position, &intersection->ray.origin);
	value[1] = vector3_dot(temp, &data->normal) / value[0];
	if (value[1] <= RAY_T_MIN || value[1] >= intersection->ray.t)
		return (0);
	intersection->ray.t = value[1];
	intersection->normal = data->normal;
	intersection->color = shape->material.color;
	intersection->material = shape->material;
	intersection->highlight = shape->highlight;
	return (1);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							CYLINDER
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 				s_cylinder_data
{
	t_vector3				top;
	t_vector3				bottom;
	float 					radius;
	t_vector3				axis;
}							t_cylinder_data;

static float				cl_cylinder_caps_intersect
							(constant t_shape_cl *shape,
							constant void *data_ptr,
							t_intersection_cl *intersection)
{
	t_cylinder_data			*data;
	float					t[2];

	data = (t_cylinder_data *)data_ptr;
	if (!vector3_dot(&intersection->ray.direction, &data->axis))
		return (INFINITY);
	t[0] = vector3_s_dot(vector3_sub(&data->top, &intersection->ray.origin), data->axis) / vector3_dot(&intersection->ray.direction, &data->axis);
	if (t[0] <= RAY_T_MIN)
		return (INFINITY);
	if (vector3_s_length(vector3_s_sub(data->top, vector3_s_add(intersection->ray.origin, vector3_mul(&intersection->ray.direction, t[0])))) < data->radius)
		intersection->normal = data->axis;
	else
		t[0] = INFINITY;
	t[1] = vector3_s_dot(vector3_sub(&data->bottom, &intersection->ray.origin), data->axis) / vector3_dot(&intersection->ray.direction, &data->axis);
	if (t[1] <= RAY_T_MIN)
		return (INFINITY);
	if (vector3_s_length(vector3_s_sub(data->bottom, vector3_s_add(intersection->ray.origin, vector3_mul(&intersection->ray.direction, t[1])))) < data->radius && t[1] < t[0])
		intersection->normal = vector3_mul(&data->axis, -1);
	else
		return (t[0]);
	return (t[1]);
}

static int					cl_cylinder_intersect
							(constant t_shape_cl *shape,
							constant void *data_ptr,
							t_intersection_cl *intersection)
{
	t_cylinder_data			*data;
	float					k[3];
	float					discriminant;
	float					t[2];
	t_vector3				temp[2];
	float					angle[2];

	data = (t_cylinder_data *)data_ptr;
	temp[0] = vector3_sub(&intersection->ray.origin, &data->bottom);
	k[0] = vector3_dot(&intersection->ray.direction, &intersection->ray.direction) - pow(vector3_dot(&intersection->ray.direction, &data->axis), 2.f);
	k[1] = 2 * (vector3_dot(&intersection->ray.direction, temp) - vector3_dot(&intersection->ray.direction, &data->axis) *  vector3_dot(temp, &data->axis));
	k[2] =  vector3_dot(temp, temp) - pow(vector3_dot(temp, &data->axis), 2.f) - pow(data->radius, 2.f);
	if ((discriminant = k[1] * k[1] - 4 * k[0] * k[2]) < 0.)
		return (0);
	t[0] = (-k[1] - sqrtf(discriminant)) / (2 * k[0]);
	if (t[0] <= RAY_T_MIN || t[0] >= intersection->ray.t)
		return (0);
	temp[0] = vector3_s_add(intersection->ray.origin, vector3_mul(&intersection->ray.direction, t[0]));	// p
	angle[0] = vector3_s_dot(vector3_sub(temp, &data->top), data->axis);
	angle[1] = vector3_s_dot(vector3_sub(temp, &data->bottom), data->axis);
	t[1] = cl_cylinder_caps_intersect(shape, data_ptr, intersection);
	if ((angle[0] > 0. || angle[1] < 0.) && t[1] != INFINITY)
		t[0] = t[1];
	else if (!(angle[0] > 0. || angle[1] < 0.))
	{
		temp[1] = vector3_sub(temp, &data->bottom); // p - b
		intersection->normal = vector3_s_sub(temp[1], vector3_mul(&data->axis, vector3_dot(temp + 1, &data->axis)));
	}
	else
		return (0);
	intersection->ray.t = t[0];
	intersection->color = shape->material.color;
	intersection->material = shape->material;
	intersection->highlight = shape->highlight;
	return (1);
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							AABB
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 				s_aabb_data
{
	t_vector3				min;
	t_vector3				max;
}							t_aabb_data;


static int 					cl_aabb_intersect
							(constant t_shape_cl *shape,
							constant void *data_ptr,
							t_intersection_cl *intersection)
{
	t_aabb_data				*data;
	float					inv_dir;
	float 					t[2];
	float 					t_near;
	float 					t_far;
	float 					t_temp;
	int 					i;
	t_vector3				normal;

	normal = (t_vector3){0., 0., 0.};
	data = (t_aabb_data *)data_ptr;
	i = 0;
	t_near = RAY_T_MIN;
	t_far = RAY_T_MAX;
	while (i < 3)
	{
		inv_dir = 1. / *vector3_iter(&intersection->ray.direction, i);
		t[0] = (*vector3_iter(&data->min, i) - *vector3_iter(&intersection->ray.origin, i)) * inv_dir;
		t[1] = (*vector3_iter(&data->max, i) - *vector3_iter(&intersection->ray.origin, i)) * inv_dir;
		if (inv_dir < 0.)
		{
			t_temp = t[0];
			t[0] = t[1];
			t[1] = t_temp;
		}
		if ((t_near = fmaxf(t[0], t_near)) == t[0])
		{
			normal = (t_vector3){0., 0., 0.};
			*vector3_iter(&normal, i) = inv_dir < 0. ? 1. : -1.;
		}
		t_far = fminf(t[1], t_far);
		if (t_far <= t_near)
			return (0);
		i++;
	}
	if (t_near == RAY_T_MIN || t_near >= intersection->ray.t)
		return (0);
	intersection->ray.t = t_near;
	intersection->normal = normal;
	intersection->color = shape->material.color;
	intersection->material = shape->material;
	intersection->highlight = shape->highlight;
	return (1);

}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							CONE
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 				s_cone_data
{
	t_vector3				top;
	t_vector3				bottom;
	float 					radius;
	float          			tangens;
	t_vector3				axis;
}							t_cone_data;


static float				cl_cone_cap_intersect
							(constant t_shape_cl *shape,
							constant void *data_ptr,
							t_intersection_cl *intersection)
{
	t_cone_data				*data;
	float 					t;

	data = (t_cone_data *)data_ptr;
	if (!vector3_dot(&intersection->ray.direction, &data->axis))
		return (INFINITY);
	t = vector3_s_dot(vector3_sub(&data->bottom, &intersection->ray.origin), data->axis) / vector3_dot(&intersection->ray.direction, &data->axis);
	if (t <= RAY_T_MIN)
		return (INFINITY);
	if (vector3_s_length(vector3_s_sub(data->bottom, vector3_s_add(intersection->ray.origin, vector3_mul(&intersection->ray.direction, t)))) < data->radius)
		intersection->normal = vector3_mul(&data->axis, -1);
	else
		return (INFINITY);
	return (t);

}

int 						cl_cone_intersect
							(constant t_shape_cl *shape,
							constant void *data_ptr,
							t_intersection_cl *intersection)
{
	t_cone_data	    		*data;
	float 					k[3];
	float 					discriminant;
	float 					t[2];
	t_vector3				temp[3];
	float 					angle[2];

	data = (t_cone_data *)data_ptr;
	temp[0] = vector3_sub(&intersection->ray.origin, &data->top);
	k[0] = vector3_dot(&intersection->ray.direction, &intersection->ray.direction) - pow(vector3_dot(&intersection->ray.direction, &data->axis), 2.f) * (1 + data->tangens * data->tangens);
	k[1] = 2 * (vector3_dot(temp, &intersection->ray.direction) - (1 + data->tangens * data->tangens) * vector3_dot(&intersection->ray.direction, &data->axis) * vector3_dot(temp, &data->axis));
	k[2] = vector3_dot(temp, temp) - (1 + data->tangens * data->tangens) * pow(vector3_dot(temp, &data->axis), 2.f);
	if ((discriminant = k[1] * k[1] - 4 * k[0] * k[2]) < 0.)
		return (0);
	t[0] = (-k[1] - sqrtf(discriminant)) / (2 * k[0]);
	if (t[0] <= RAY_T_MIN || t[0] >= intersection->ray.t)
		return (0);
	temp[1] = vector3_s_add(intersection->ray.origin, vector3_mul(&intersection->ray.direction, t[0])); // p
	temp[2] = vector3_sub(temp + 1, &data->bottom);
	angle[0] = vector3_s_dot(vector3_sub(temp + 1, &data->top), data->axis);
	angle[1] = vector3_s_dot(vector3_sub(temp + 1, &data->bottom), data->axis);
	int is_inf = (vector3_s_length(temp[2]) > vector3_s_length(vector3_sub(&data->top, &data->bottom)) || vector3_dot(temp + 2, &data->axis) > 0.);
	t[1] = cl_cone_cap_intersect(shape, data_ptr, intersection);
	if (t[1] != INFINITY && is_inf)
		t[0] = t[1];
	else if (!is_inf)
	{
		t[1] = vector3_dot(&intersection->ray.direction, &data->axis) * t[0] + vector3_dot(temp, &data->axis);
		intersection->normal = vector3_s_sub(vector3_s_sub(temp[1], data->top), vector3_s_mul(data->axis, (1 + data->tangens * data->tangens) * t[1]));
		vector3_normalize(&intersection->normal);
	}
	else
		return (0);
	intersection->ray.t = t[0];
	intersection->color = shape->material.color;
	intersection->material = shape->material;
	intersection->highlight = shape->highlight;
	return (1);
}

 */

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							CAMERA
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct				s_camera
{
	t_vector3				position;
	float					direction_length;
	t_vector3				direction;
	t_vector3				axis_x;
	t_vector3				axis_y;
	t_vector3				axis_z;
	t_vector3				vp_axis_x;
	t_vector3				vp_axis_y;
	t_vector3       		angles;
}							t_camera;

static t_ray            	camera_cast_ray
                        	(constant t_camera *me,
                        	t_vector3 *vp_values)
{
	t_ray		        	tmp;
	t_vector3           	up;
	t_vector3           	right;
	t_vector3	        	point;

	right = me->vp_axis_x;
	up = me->vp_axis_y;
	vector3_mul_eq(&right, vp_values->x);
	vector3_mul_eq(&up, vp_values->y);
	point = vector3_add(&right, &up);
	tmp.origin = me->position;
	tmp.direction = me->direction;
	vector3_add_eq(&tmp.direction, &point);
	vector3_normalize(&tmp.direction);
	return (tmp);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							SCENE
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef	struct				s_scene
{
	t_camera				camera;
	t_shape					shapes[SCENE_SHAPE_CAPACITY];
	int 					shapes_length;
	t_light					lights[SCENE_LIGHT_CAPACITY];
	int 					lights_length;
	t_vector3       		background;
}							t_scene;

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							SCENE INTERSECTION
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int 					call_intersection
							(constant t_shape *shape,
							t_intersection *intersection)
{
	if (shape->id == SHAPE_ID_SPHERE)
		return (sphere_intersect(shape, intersection));
}

static int 					scene_intersect
                        	(constant t_scene *scene,
							t_intersection *intersection)
{
	int 					i;
	int 					result;

	i = 0;
	result = 0;
	while (i < scene->shapes_length)
	{
		result += call_intersection(scene->shapes + i, intersection);
		i++;
	}

	return (result != 0);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							SHADOW
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int              	scene_check_shadow
                        	(constant t_scene *scene,
                        	t_intersection *intersection,
                        	t_vector3 *light_direction)
{
	t_intersection   	shadow;

	intersection_reset(&shadow);
	shadow.ray.origin = ray_intersect(&intersection->ray);
	shadow.ray.direction = *light_direction;
	scene_intersect(scene, &shadow);
	return (shadow.ray.t >= RAY_T_MIN && shadow.ray.t <= vector3_length(light_direction));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							LIGHT TOOLS
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void             	intersection_lighting_diffuse
                        	(t_intersection *intersection,
                        	constant t_light *light,
                        	t_vector3 *light_direction)
{
float	          			dot;

	if ((dot = vector3_dot(light_direction, &intersection->normal)) > 0.)
		intersection->diffuse_intensity += intersection->shadow_ratio * intersection->material.diffuse * light->intensity * dot / vector3_length(light_direction);
}

static void             	intersection_lighting_specular
                        	(t_intersection *intersection,
                        	constant t_light *light,
                        	t_vector3 *light_direction)
{
	t_vector3            	halfway;
float	          			dot;

	halfway = vector3_add(light_direction, &intersection->ray.direction);
	vector3_normalize(&halfway);
	if ((dot = vector3_dot(&halfway, &intersection->normal)) > 0.)
		intersection->specular_intensity += intersection->shadow_ratio * intersection->material.specular * light->intensity * pow(dot, BLINN);

}

static void             	intersection_make_color
                        	(t_intersection *intersection)
{
	t_vector3		   		white;

	white = (t_vector3){1., 1., 1.};
	intersection->color = vector3_mul(&intersection->material.color, intersection->diffuse_intensity);
	vector3_mul_eq(&white, intersection->specular_intensity);
	vector3_add_eq(&intersection->color, &white);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							LIGHT
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void					scene_light_up
                        	(constant t_scene *scene,
                        	t_intersection *intersection)
{
	int                 	i;
	t_vector3           	light_direction;

	i = 0;

	while(i < scene->lights_length)
	{
		intersection->shadow_ratio = 1.;
		if (scene->lights[i].type == light_ambient)
		{
			intersection->diffuse_intensity += scene->lights[i].intensity;
			i++;
			continue ;
		}
		else
			light_direction = intersection_light_direction(intersection, scene->lights);
//		if (scene_check_shadow(scene, intersection, &light_direction))
//		{
//		    i++;
//			continue ;
//		}
		intersection_lighting_diffuse(intersection, scene->lights + i, &light_direction);
//		intersection_lighting_specular(intersection, scene->lights + i, &light_direction);
		i++;
	}
	intersection_make_color(intersection);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							REFLECTION
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void					intersection_reflect
                        	(t_intersection *target,
                        	const t_intersection *source)
{
	t_vector3		    	temp;

	temp = vector3_mul(&source->normal, -2. * vector3_dot(&source->normal, &source->ray.direction));
	vector3_add_eq(&temp, &source->ray.direction);
	vector3_normalize(&temp);
	target->ray.direction = temp;
	target->ray.origin = ray_intersect(&source->ray);
}

static void             	reflect
							(constant t_scene *scene,
							t_intersection *original)
{
    t_vector3           	result_color;
    t_intersection   		previous;
    t_intersection   		current;
	float	         		depth_ratio;
    int                 	i;

    result_color = (t_vector3){0., 0., 0.};
    previous = *original;
    depth_ratio = original->material.reflect;
    i = 0;
    while (i <= REFLECTION_DEPTH && previous.material.reflect)
    {
        intersection_reset(&current);
        intersection_reflect(&current, &previous);
        if (scene_intersect(scene, &current))
        {
            scene_light_up(scene, &current);
            vector3_mul_eq(&current.color, depth_ratio);
            vector3_add_eq(&result_color, &current.color);
        }
        else
            vector3_s_add_eq(&result_color, vector3_s_mul(scene->background, depth_ratio));
        previous = current;
        depth_ratio *= original->material.reflect;
        i++;
    }
    vector3_add_eq(&original->color, &result_color);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//							RAY_TRACER
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


kernel void					render
							(global int *image,
                        	constant t_scene *scene)
{
    int 					global_id;
    t_vector3           	screen;
    t_vector3           	vp;
    t_intersection			intersection;

	global_id = get_global_id(0);

    screen.x = global_id % WINDOW_WIDTH;
	screen.y = global_id / WINDOW_WIDTH;

	vp.x = screen.x - (WINDOW_WIDTH - 1.) / 2.;
    vp.y = -1 * screen.y + (WINDOW_HEIGHT - 1.) / 2.;

	intersection.ray = camera_cast_ray(&scene->camera, &vp);

	intersection_reset(&intersection);

   if (!scene_intersect(scene, &intersection))
	{
		image[global_id] = color_unpack((t_vector3)scene->background);
		return ;
	}

	if (intersection.highlight)
	{
		image[global_id] = color_unpack((t_vector3){1., 1., 1.});
		return ;
	}

	scene_light_up(scene, &intersection);

//	if (intersection.material.reflect)
//	   reflect(scene, &intersection);
//
    image[global_id] = color_unpack(intersection.color);

}