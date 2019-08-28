// cl_f4 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_float.h"

static RT_F			f4_min_component(RT_F4 vector)
{
	return (fmin(vector.x, fmin(vector.y, vector.z)));
}

static RT_F			f4_max_component(RT_F4 vector)
{
	return (fmax(vector.x, fmax(vector.y, vector.z)));
}

static RT_F4		f4_square(RT_F4 vector)
{
	return ((RT_F4)(
		vector.x * vector.x
		- vector.y * vector.y
		- vector.z * vector.z
		- vector.w * vector.w,
		2 * vector.x * vector.y,
		2 * vector.x * vector.z,
		2 * vector.x * vector.w));
}

// cl_settings /////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 		s_cl_renderer_settings
{
	int 			light_basic;
	int 			light_area;
	int 			illumination;
	RT_F 			illumination_value;
	int 			sample_count;
	int 			sample_limit;
	int 			sample_depth;
	int 			rm_mod;
	int 			rm_step_limit;
	RT_F			rm_step_part;
	int 			rm_max_distance;
}					t_cl_renderer_settings;

// cl_random ///////////////////////////////////////////////////////////////////////////////////////////////////////////

static RT_F			rng_lgc(global ulong *rng_state)
{
	int				gi;
	ulong			x;

	gi = get_global_id(0);
	x = rng_state[gi];
	x = (0x5DEECE66DL * x + 0xBL) & ((1L << 48) - 1);
	rng_state[gi] = x;
    return ((RT_F)x / (1L << 48));
}

static RT_F			rng_xor(global ulong *rng_state)
{
	int				gi;
	ulong			x;

	gi = get_global_id(0);
	x = rng_state[gi];
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
	rng_state[gi] = x;
	x %= 4294967296; // костыль
    return (x / 4294967296.0f);
}

static RT_F			rng(global ulong *rng_state)
{
	return (rng_lgc(rng_state));
}

// cl_ray //////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_float.h"

typedef	struct		s_ray
{
	RT_F4			origin;
	RT_F4			direction;
	RT_F 			t;
}					t_ray;

static RT_F4		ray_intersect(t_ray *ray)
{
	return (ray->origin + ray->direction * ray->t);
}
// cl_color ////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_color;

static t_color		color_filter_sepia(RT_F4 *source)
{
	unsigned char	sepia_color;

	sepia_color = (255 * source->x) * 0.3 + (255 * source->y) * 0.59 + (255 * source->z) * 0.11;
	return((t_color){sepia_color, sepia_color, sepia_color, 255});
}

static t_color		color_unpack(RT_F4 source, int filter_sepia)
{
	source = RT_POW(source, (RT_F).4);
	source.x = RT_MIN(source.x, (RT_F)1.);
	source.y = RT_MIN(source.y, (RT_F)1.);
	source.z = RT_MIN(source.z, (RT_F)1.);
	if (filter_sepia)
	    return(color_filter_sepia(&source));
	return ((t_color){255 * source.x, 255 * source.y, 255 * source.z, 255});
}

// cl_material /////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 		s_material
{
	RT_F4			color;
	RT_F4			emission;
	RT_F			specular;
	RT_F			reflectance;
	RT_F			transparence;
}					t_material;

// cl_intersection /////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct		s_intersection
{
	t_ray			ray;
	RT_F4			hit;
	RT_F4			normal;
	t_material		material;
	int 			object_id;
	int				cups_flag;
}					t_intersection;

static void			intersection_reset(t_intersection *intersection)
{
	intersection->ray.t = RT_INFINITY;
	intersection->object_id = -1;
}

static void			intersection_reflect(t_intersection *destination, const t_intersection *source)
{
	RT_F4			reflected;

	reflected = source->normal * ((RT_F)-2. * dot(source->normal, source->ray.direction));
	reflected += source->ray.direction;
	reflected = normalize(reflected);
	destination->ray.direction = reflected;
	destination->ray.origin = source->hit;
}

static void			intersection_refract(t_intersection *destination, const t_intersection *source)
{
	RT_F4			refracted;
	RT_F4			a, b;
	RT_F4			m;
	RT_F			sin_alpha;
	RT_F			sin_beta;
	RT_F			cos_beta;

	m = source->normal * (-1 * dot(source->normal, source->ray.direction));
	m += source->ray.direction;
	m = normalize(m);
	sin_alpha = length(cross(source->ray.direction * -1, source->normal));
	sin_beta = sin_alpha / 1.02;
	cos_beta = RT_SQRT(1 - sin_beta * sin_beta);
	a = source->normal * (-1 * cos_beta);
	b = m * sin_beta;
	refracted = a + b;
	refracted = normalize(refracted);
	destination->ray.direction = refracted;
	destination->ray.origin = source->hit;
}

// cl_object ///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef enum		e_object_type
{
	object_light_ambient,
	object_light_point,
	object_light_direct,
	object_sphere,
	object_plane,
	object_cone,
	object_cylinder,
	object_box,
	object_paraboloid,
	object_moebius,
	object_torus,
	object_mandelbulb,
	object_julia,
	object_csg,
	object_end
}					t_object_type;

typedef struct		s_object
{
	char 			name[32];
	int				id;
	t_object_type	type;
	int 			is_csg;
	t_material		material;
	char			data[RT_CL_OBJECT_CAPACITY];
}					t_object;

// cl_object_sphere ////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct					s_object_sphere
{
	RT_F4						position;
	RT_F						radius;
}								t_object_sphere;

static int     					sphere_intersect(constant t_object *object, t_intersection *intersection)
{
	t_object_sphere				data;
	RT_F						k[3];
	RT_F						t;
	RT_F						discriminant;
	RT_F4						temp;

    data = *(constant t_object_sphere *)object->data;
	k[0] = dot(intersection->ray.direction, intersection->ray.direction);
	temp = intersection->ray.origin - data.position;
	k[1] = 2 * dot(temp, intersection->ray.direction);
	k[2] = dot(temp, temp) - data.radius * data.radius;
	discriminant = k[1] * k[1] - 4 * k[0] * k[2];
	if (discriminant < 0.f)
		return (0);
	t = (-k[1] - RT_SQRT(discriminant)) / (2 * k[0]);
	if (t <= RT_EPSILON || t >= intersection->ray.t)
		return (0);
	intersection->ray.t = t;
	intersection->object_id = object->id;
	return (1);
}

static RT_F4					sphere_normal(constant t_object *object, t_intersection *intersection)
{
	return (normalize(intersection->hit - ((constant t_object_sphere *)object->data)->position));
}

static RT_F4					sphere_random(constant t_object *object, global ulong *rng_state)
{
	t_object_sphere				data;
	RT_F 						theta;
	RT_F 						phi;
	RT_F4						random;

	data = *(constant t_object_sphere *)object->data;
	theta = rng(rng_state) * RT_PI;
	phi = rng(rng_state) * 2 * RT_PI;
	random.x = 0.9 * data.radius * RT_SIN(theta) * RT_COS(phi);
	random.y = 0.9 * data.radius * RT_SIN(theta) * RT_SIN(phi);
	random.z = 0.9 * data.radius * RT_COS(theta);
	random += data.position;
	return (random);
}

static RT_F 					sphere_sdf(constant t_object *object, RT_F4 point)
{
	t_object_sphere				data;

    data = *(constant t_object_sphere *)object->data;
	return (length(data.position - point) - data.radius);
}

static RT_F						sphere_center_shift(constant t_object *object)
{
	t_object_sphere				data;

	data = *(constant t_object_sphere *)object->data;
    return (data.radius);
}
// cl_object_plane /////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct		s_object_plane
{
	RT_F4			position;
	RT_F4			normal;
}					t_object_plane;

static int			plane_intersect(constant t_object *object, t_intersection *intersection)
{
	t_object_plane	data;
	RT_F4			temp[2];
	RT_F			value[3];

	data = *(constant t_object_plane *)object->data;
	if (!(value[0] = dot(intersection->ray.direction, data.normal)))
		return (0);
	temp[0] = data.position - intersection->ray.origin;
	value[1] = dot(temp[0], data.normal) / value[0];
	if (value[1] <= RT_EPSILON || value[1] >= intersection->ray.t)
		return (0);
	intersection->ray.t = value[1];
	intersection->object_id = object->id;
	return (1);
}

static RT_F4		plane_normal(constant t_object *object, t_intersection *intersection)
{
	return (((constant t_object_plane *)object->data)->normal);
}

static RT_F 		plane_sdf(constant t_object *object, RT_F4 point)
{
	t_object_plane	data;

    data = *(constant t_object_plane *)object->data;
	return (dot(data.normal, point - data.position));
}
// cl_object_cone /////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct 		s_object_cone
{
	RT_F4   		top;
	RT_F4   		bottom;
	RT_F4   		axis;
	RT_F 			radius;
	RT_F          	tangent;
}					t_object_cone;

static RT_F         cone_cap_intersect(constant t_object *object, t_intersection *intersection)
{
    t_object_cone	data;
    RT_F            t;

    data = *(constant t_object_cone *)object->data;
    if (!dot(intersection->ray.direction, data.axis))
        return (INFINITY);
    t = dot((data.bottom - intersection->ray.origin), data.axis)
            / dot(intersection->ray.direction, data.axis);
    if (t <= RT_EPSILON)
        return (INFINITY);
    if (length(data.bottom - (intersection->ray.origin + (intersection->ray.direction * t))) < data.radius)
        intersection->cups_flag = 1;
    else
        return (INFINITY);
    return (t);
}

static int			cone_intersect(constant t_object *object, t_intersection *intersection)
{
	t_object_cone	data;
    RT_F4           temp[3];
	RT_F            discriminant;
    int             is_infinity;
    RT_F            angle[2];
	RT_F            t[2];
	RT_F            k[3];

	data = *(constant t_object_cone *)object->data;
	temp[0] = intersection->ray.origin - data.top;
	k[0] = dot(intersection->ray.direction, intersection->ray.direction)
			- pow((RT_F)dot(intersection->ray.direction, data.axis), (RT_F)2.)
			* (1 + data.tangent * data.tangent);
	k[1] = 2 * (dot(temp[0], intersection->ray.direction) - (1 + data.tangent * data.tangent)
			* dot(intersection->ray.direction, data.axis) * dot(temp[0], data.axis));
	k[2] = dot(temp[0], temp[0]) - (1 + data.tangent * data.tangent)
			* pow((RT_F)dot(temp[0], data.axis), (RT_F)2.);
	if ((discriminant = k[1] * k[1] - 4 * k[0] * k[2]) < 0.)
		return (0);
	t[0] = (-k[1] - RT_SQRT(discriminant)) / (2 * k[0]);
	if (t[0] <= RT_EPSILON || t[0] >= intersection->ray.t)
		return (0);

	temp[1] = intersection->ray.origin + (intersection->ray.direction * t[0]);
    temp[2] = temp[1] - data.bottom;
    angle[0] = dot((temp[1] - data.top), data.axis);
    angle[1] = dot((temp[1] - data.bottom), data.axis);
    is_infinity = (length(temp[2]) > length(data.top - data.bottom))
                 || (dot(temp[2], data.axis) > 0.);
    t[1] = cone_cap_intersect(object, intersection);
    if (t[1] != INFINITY && is_infinity)
	    t[0] = t[1];
    else if (!is_infinity)
        intersection->cups_flag = 0;
    else
        return (0);
	intersection->ray.t = t[0];
	intersection->object_id = object->id;
	return (1);
}

static RT_F4		calculate_cone_normal(constant t_object *object, t_intersection *intersection)
{
    t_object_cone	data;
    RT_F4			temp[2];
    RT_F            tmp_value;
    RT_F4           result;

    data = *(constant t_object_cone *)object->data;
    temp[0] = intersection->ray.origin - data.top;
    temp[1] = intersection->ray.origin + (intersection->ray.direction * intersection->ray.t);
    tmp_value = dot(intersection->ray.direction, data.axis)
                * intersection->ray.t + dot(temp[0], data.axis);
    result = (temp[1] - data.top) - (data.axis * ((1 + data.tangent * data.tangent) * tmp_value));
    return (normalize(result));
}

static RT_F4		cone_normal(constant t_object *object, t_intersection *intersection)
{
    if (!intersection->cups_flag)
        return(calculate_cone_normal(object, intersection));
    else
        return(normalize(((constant t_object_cone *)object->data)->axis * -1));
}

// cl_object_cylinder /////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct 		    s_object_cylinder
{
	RT_F4   		    top;
	RT_F4   		    bottom;
	RT_F4   		    axis;
	RT_F 			    radius;
}					    t_object_cylinder;

static RT_F             cylinder_cap_intersect(constant t_object *object, t_intersection *intersection)
{
    t_object_cylinder   data;
    RT_F                t[2];

    data = *(constant t_object_cylinder *)object->data;
    if (!dot(intersection->ray.direction, data.axis))
        return (INFINITY);
    t[0] = dot((data.top - intersection->ray.origin), data.axis)
            / dot(intersection->ray.direction, data.axis);
    if (t[0] <= RT_EPSILON)
        return (INFINITY);
    if (length(data.top - (intersection->ray.origin + (intersection->ray.direction * t[0]))) < data.radius)
        intersection->cups_flag = 1;
    else
        t[0] = INFINITY;
    t[1] = dot((data.bottom - intersection->ray.origin), data.axis)
            / dot(intersection->ray.direction, data.axis);
    if (t[1] <= RT_EPSILON)
        return (INFINITY);
    if (length(data.bottom - (intersection->ray.origin + (intersection->ray.direction * t[1]))) < data.radius
        && t[1] < t[0])
        intersection->cups_flag = -1;
    else
        return (t[0]);
    return (t[1]);
}

static int			    cylinder_intersect(constant t_object *object, t_intersection *intersection)
{
	t_object_cylinder	data;
	RT_F4			    temp[2];
    RT_F			    angle[2];
	RT_F                discriminant;
	RT_F                t[2];
	RT_F                k[3];

	data = *(constant t_object_cylinder *)object->data;
	temp[0] = intersection->ray.origin - data.bottom;

	k[0] = dot(intersection->ray.direction, intersection->ray.direction)
			- pow((RT_F)dot(intersection->ray.direction, data.axis), (RT_F)2.);
	k[1] = 2 * (dot(intersection->ray.direction, temp[0])
			- dot(intersection->ray.direction, data.axis)
			* dot(temp[0], data.axis));
	k[2] =  dot(temp[0], temp[0]) - pow((RT_F)dot(temp[0], data.axis), (RT_F)2.)
			- pow((RT_F)data.radius, (RT_F)2.);
	if ((discriminant = k[1] * k[1] - 4 * k[0] * k[2]) < 0.)
		return (0);
	t[0] = (-k[1] - RT_SQRT(discriminant)) / (2 * k[0]);
	if (t[0] <= RT_EPSILON || t[0] >= intersection->ray.t)
		return (0);
    temp[0] = intersection->ray.origin + intersection->ray.direction * t[0];	// p
    angle[0] = dot((temp[0] - data.top), data.axis);
    angle[1] = dot(temp[0] - data.bottom, data.axis);
    t[1] = cylinder_cap_intersect(object, intersection);
    if ((angle[0] > 0. || angle[1] < 0.) && t[1] != INFINITY)
        t[0] = t[1];
    else if (!(angle[0] > 0. || angle[1] < 0.))
        intersection->cups_flag = 0;
    else
        return (0);
	intersection->ray.t = t[0];
	intersection->object_id = object->id;
	return (1);
}

static RT_F4		    calculate_cylinder_normal(constant t_object *object, t_intersection *intersection)
{
    t_object_cylinder   data;
    RT_F4			    temp[2];
    RT_F4               result;

    data = *(constant t_object_cylinder *)object->data;
    temp[0] = intersection->ray.origin + intersection->ray.direction * intersection->ray.t;
    temp[1] = temp[0] - data.bottom;
    result = temp[1] - (data.axis * dot(temp[1], data.axis));
    return (normalize(result));
}

static RT_F4		    cylinder_normal(constant t_object *object, t_intersection *intersection)
{
    if (!intersection->cups_flag)
        return (calculate_cylinder_normal(object, intersection));
    else if (intersection->cups_flag == -1)
        return (normalize(((constant t_object_cylinder *)object->data)->axis * -1));
    else
        return (normalize(((constant t_object_cylinder *)object->data)->axis));
}
// cl_object_box ///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct 		s_object_box
{
	RT_F4   		position;
	RT_F4   		size;
}					t_object_box;

static RT_F 		box_sdf(constant t_object *object, RT_F4 point)
{
	t_object_box	data;
	RT_F4			d;

	data = *(constant t_object_box *)object->data;
	point = data.position - point;
	d = RT_ABS(point) - data.size;
	return (RT_MIN((RT_F)RT_MAX((RT_F)d.x, RT_MAX(d.y, d.z)), (RT_F)0.0)
	    + length((RT_F4){RT_MAX(d.x, (RT_F)0.f), RT_MAX(d.y, (RT_F)0.f), RT_MAX(d.z, (RT_F)0.f), (RT_F)0.f}));
}

// cl_object_paraboloid ////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct 					s_object_paraboloid
{
	RT_F4						extremum_point;
	RT_F4						axis;
	RT_F 						radius;
}								t_object_paraboloid;

static int     					paraboloid_intersect(constant t_object *object, t_intersection *intersection)
{
	t_object_paraboloid			data;
	RT_F4						vector_x;
    RT_F 						t;
    RT_F 						discriminant;
    RT_F 						k[3];
    RT_F 						x_dot_axis;
    RT_F 						dir_dot_axis;

    data = *(constant t_object_paraboloid *)object->data;
    vector_x = intersection->ray.origin - data.extremum_point;
    x_dot_axis = dot(vector_x, data.axis);
    dir_dot_axis = dot(intersection->ray.direction, data.axis);
	k[0] = dot(intersection->ray.direction, intersection->ray.direction) - dir_dot_axis * dir_dot_axis;
   	k[1] = 2 * (dot(intersection->ray.direction, vector_x) - dir_dot_axis * (x_dot_axis + 2 * data.radius));
   	k[2] = dot(vector_x, vector_x) - x_dot_axis * (x_dot_axis + 4 * data.radius);
	discriminant = k[1] * k[1] - 4 * k[0] * k[2];
	if (discriminant < 0.f)
		return (0);
	t = (-k[1] - RT_SQRT(discriminant)) / (2 * k[0]);
	if (t <= RT_EPSILON || t >= intersection->ray.t)
		return (0);
	intersection->ray.t = t;
	intersection->object_id = object->id;
	return (1);
}

static RT_F4					paraboloid_normal(constant t_object *object, t_intersection *intersection)
{
	t_object_paraboloid			data;
	RT_F4						normal;
	RT_F						tmp_value;

	data = *(constant t_object_paraboloid *)object->data;
	tmp_value = dot(data.axis, intersection->hit - data.extremum_point);
	normal = (intersection->hit - data.extremum_point) - (data.axis * tmp_value);
	return (normalize(normal));
}

// cl_object_moebius ///////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct		            s_object_moebius
{
    RT_F4   		            position;
    RT_F 			            radius;
    RT_F			            half_width;
}					            t_object_moebius;

// solving cubic equation //////////////////////////////////////////////////////////////////////////////////////////////

typedef struct					s_moebius_equation
{
	RT_F						q;
	RT_F						r;
	RT_F						bq;
	RT_F						br;
	RT_F						bq3;
	RT_F						br2;
	RT_F						cr2;
	RT_F						cq3;
	RT_F						sqrt_bq;
	RT_F						sgnbr;
	RT_F						ratio;
	RT_F						theta;
	RT_F						norm;
	RT_F						r0;
	RT_F						r1;
	RT_F						r2;
	RT_F						ba;
	RT_F						bb;
	int							i;
}								t_moebius_equation;

static void						ft_swap(RT_F *a, RT_F *b)
{
	RT_F						tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

static t_moebius_equation		init_structure(const RT_F *coefficients)
{
	t_moebius_equation			new;

	new.q = coefficients[2] * coefficients[2] - 3 * coefficients[1];
	new.r = 2 * coefficients[2] * coefficients[2] * coefficients[2]
		- 9 * coefficients[2] * coefficients[1] + 27 * coefficients[0];
	new.bq = new.q / 9;
	new.br = new.r / 54;
	new.bq3 = new.bq * new.bq * new.bq;
	new.br2 = new.br * new.br;
	new.cr2 = 729 * new.r * new.r;
	new.cq3 = 2916 * new.q * new.q * new.q;
	new.sgnbr = new.br >= 0 ? 1 : -1;
	new.i = 0;
	return (new);
}

static int						solve_second_case(t_moebius_equation c, const RT_F *coefficients, RT_F *r)
{
	c.sqrt_bq = RT_SQRT(c.bq);
	if (c.br > 0)
	{
		r[0] = -2 * c.sqrt_bq - coefficients[2] / 3;
		r[1] = c.sqrt_bq - coefficients[2] / 3;
		r[2] = c.sqrt_bq - coefficients[2] / 3;
	}
	else
	{
		r[0] = -c.sqrt_bq - coefficients[2] / 3;
		r[1] = -c.sqrt_bq - coefficients[2] / 3;
		r[2] = 2 * c.sqrt_bq - coefficients[2] / 3;
	}
	return (3);
}

static int						solve_third_case(t_moebius_equation c, const RT_F *coefficients, RT_F *r)
{
	c.ratio = c.sgnbr * RT_SQRT(c.br2 / c.bq3);
	c.theta = acos(c.ratio);
	c.norm = -2 * RT_SQRT(c.bq);
	c.r0 = c.norm * RT_COS((RT_F)c.theta / 3) - coefficients[2] / 3;
	c.r1 = c.norm * RT_COS((RT_F)(c.theta + 2.0 * RT_PI) / 3) - coefficients[2] / 3;
	c.r2 = c.norm * RT_COS((RT_F)(c.theta - 2.0 * RT_PI) / 3) - coefficients[2] / 3;
	if (c.r0 > c.r1)
		ft_swap(&c.r0, &c.r1);
	if (c.r1 > c.r2)
	{
		ft_swap(&c.r1, &c.r2);
		if (c.r0 > c.r1)
			ft_swap(&c.r0, &c.r1);
	}
	r[0] = c.r0;
	r[1] = c.r1;
	r[2] = c.r2;
	return (3);
}

static int						solve_fourth_case(t_moebius_equation c, const RT_F *coefficients, RT_F *r)
{
	c.ba = -c.sgnbr * pow((RT_F)(RT_ABS(c.br) + RT_SQRT(c.br2 - c.bq3)), (RT_F)(1.0 / 3.0));
	c.bb = c.bq / c.ba;
	r[0] = c.ba + c.bb - coefficients[2] / 3;
	return (1);
}

static int						solve_moebius_equation(RT_F *coefficients, RT_F *r)
{
	t_moebius_equation			c;

	c = init_structure(coefficients);
	if (c.br == 0 && c.bq == 0)
	{
		while (c.i++ < 3)
			r[c.i] = -coefficients[2] / 3;
		return (3);
	}
	else if (c.cr2 == c.cq3)
		return (solve_second_case(c, coefficients, r));
	else if (c.br2 < c.bq3)
		return (solve_third_case(c, coefficients, r));
	else
		return (solve_fourth_case(c, coefficients, r));
}

// calculating t ///////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct		            s_moebius_coefficients
{
	RT_F 			            radius;
	RT_F 			            ox;
	RT_F 			            dx;
	RT_F 			            oy;
	RT_F 			            dy;
	RT_F 			            oz;
	RT_F 			            dz;
	RT_F 			            max;
}					            t_moebius_coefficients;

static int						floating_point_sign(RT_F x)
{
    if (x < -RT_EPSILON)
    	return (-1);
    return (x > RT_EPSILON);
}

static int						is_inside_moebius_strip(t_moebius_coefficients *m, RT_F4 hit)
{
	RT_F						t;
	RT_F						s;

    t = atan2(hit.y, hit.x);
    if (floating_point_sign(RT_SIN(t / 2)) != 0)
    	s = hit.z / RT_SIN(t / 2);
    else
    	s = floating_point_sign(RT_COS(t)) ?
    		(hit.x / RT_COS(t) - m->radius) / RT_COS(t / 2) :
    		(hit.y / RT_SIN(t) - m->radius) / RT_COS(t / 2);
    hit.x -= (m->radius + s * RT_COS(t / 2)) * RT_COS(t);
    hit.y -= (m->radius + s * RT_COS(t / 2)) * RT_SIN(t);
    hit.z -= s * RT_SIN(t / 2);
    if (floating_point_sign(hit.x * hit.x + hit.y * hit.y + hit.z * hit.z))
    	return (0);
    return (s >= -m->max && s <= m->max);
}

static RT_F						choose_equation_root(RT_F *roots, int result, t_ray *ray, t_moebius_coefficients *m)
{
    int							i;
    RT_F4						hit;

    i = 0;
    while (i < result)
    {
    	if (roots[i] > -1.)
    	{
    		hit = ray->direction * roots[i] + ray->origin;
    		if (is_inside_moebius_strip(m, hit))
    			return (roots[i]);
    	}
    	i++;
    }
    return (INFINITY);
}

static void						init_equation_coefficients(t_moebius_coefficients *m, RT_F *coefficients)
{

    coefficients[0] = (m->ox * m->ox * m->oy + m->oy * m->oy * m->oy - 2 * m->ox * m->ox * m->oz
    	- 2 * m->oy * m->oy * m->oz + m->oy * m->oz * m->oz - 2 * m->ox * m->oz * m->radius - m->oy * m->radius * m->radius);
    coefficients[1] = (m->dy * m->ox * m->ox - 2 * m->dz * m->ox * m->ox + 2 * m->dx * m->ox * m->oy
    	+ 3 * m->dy * m->oy * m->oy - 2 * m->dz * m->oy * m->oy - 4 * m->dx * m->ox * m->oz - 4 * m->dy * m->oy * m->oz
    	+ 2 * m->dz * m->oy * m->oz + m->dy * m->oz * m->oz - 2 * m->dz * m->ox * m->radius - 2 * m->dx * m->oz * m->radius -
    	m->dy * m->radius * m->radius);
    coefficients[2] = (2 * m->dx * m->dy * m->ox - 4 * m->dx * m->dz * m->ox + m->dx * m->dx * m->oy
    	+ 3 * m->dy * m->dy * m->oy - 4 * m->dy * m->dz * m->oy + m->dz * m->dz * m->oy - 2 * m->dx * m->dx * m->oz
    	- 2 * m->dy * m->dy * m->oz + 2 * m->dy * m->dz * m->oz - 2 * m->dx * m->dz * m->radius);
    coefficients[3] = m->dx * m->dx * m->dy + m->dy * m->dy * m->dy - 2 * m->dx * m->dx * m->dz - 2 * m->dy * m->dy * m->dz + m->dy * m->dz * m->dz;
    coefficients[0] /= coefficients[3];
    coefficients[1] /= coefficients[3];
    coefficients[2] /= coefficients[3];
}

static void						init_moebius_coefficients(t_moebius_coefficients *moebius, t_object_moebius *data, t_ray *ray)
{
	moebius->radius = data->radius;
    moebius->ox = ray->origin.x;
    moebius->dx = ray->direction.x;
    moebius->oy = ray->origin.y;
    moebius->dy = ray->direction.y;
    moebius->oz = ray->origin.z;
    moebius->dz = ray->direction.z;
    moebius->max = data->half_width;
}

static RT_F						calculate_moebius_t(t_ray *ray, t_object_moebius *data, t_moebius_coefficients *moebius)
{
	RT_F						coefficients[4];
    RT_F						root[3];
    int							result;

	init_moebius_coefficients(moebius, data, ray);
    init_equation_coefficients(moebius, coefficients);
    result = solve_moebius_equation(coefficients, root);
    return (choose_equation_root(root, result, ray, moebius));
}

static int     					moebius_intersect(constant t_object *object, t_intersection *intersection)
{
	t_object_moebius			data;
	t_moebius_coefficients      moebius_coefficients;
	RT_F						t;

    data = *(constant t_object_moebius *)object->data;
	t = calculate_moebius_t(&intersection->ray, &data, &moebius_coefficients);
	if (t == RT_INFINITY)
		return (0);
	intersection->ray.t = t;
	intersection->object_id = object->id;
	return (1);
}

// calculating normal //////////////////////////////////////////////////////////////////////////////////////////////////

static RT_F4					moebius_normal(constant t_object *object, t_intersection *intersection)
{
	t_object_moebius			data;
	t_moebius_coefficients      moebius_coefficients;
	RT_F4						normal;
	RT_F4						vector_x;

	data = *(constant t_object_moebius *)object->data;
	vector_x = intersection->hit;
	init_moebius_coefficients(&moebius_coefficients, &data, &intersection->ray);

	normal.x = -2 * data.radius * vector_x.z + 2 * vector_x.x * vector_x.y - 4 * vector_x.x * vector_x.z;
	normal.y = -data.radius * data.radius + vector_x.x * vector_x.x + 3 * vector_x.y * vector_x.y
		- 4 * vector_x.y * vector_x.z + vector_x.z * vector_x.z;
    normal.z = -2 * data.radius * vector_x.x - 2 * vector_x.x * vector_x.x - 2 * vector_x.y
    	* vector_x.y + 2 * vector_x.y * vector_x.z;
	return (normalize(normal));
}

// cl_object_torus /////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct 		s_object_torus
{
	RT_F4   		position;
	RT_F 			t_0;
	RT_F          	t_1;
}					t_object_torus;

static RT_F 		torus_sdf(constant t_object *object, RT_F4 point)
{
	t_object_torus	data;
	RT_F2			q;

	data = *(constant t_object_torus *)object->data;
	point = data.position - point;
	q = (RT_F2)(length(point.xz) - data.t_0, point.y);
	return (length(q) - data.t_1);
}

// cl_object_julia /////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct		s_object_julia
{
	RT_F4			position;
	int				iterations;
	RT_F4			value;
}					t_object_julia;

static RT_F			julia_sdf(constant t_object *object, RT_F4 point)
{
	t_object_julia	data;
	RT_F			md;
	RT_F			mz;

	data = *(constant t_object_julia *)object->data;
	md = 1.;
	point = data.position - point;
	mz = dot(point, point);

	for (int iter = 0; iter < data.iterations; iter++)
	{
		md *= 4. * mz;
		point = f4_square(point);
		point += data.value;
		mz = dot(point, point);
		if (mz > 4.)
			break ;
	}
	return (.25 * RT_SQRT(mz / md) * log(mz));
}

// cl_object_mandelbulb ////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct				s_object_mandelbulb
{
	RT_F4					position;
	int						iterations;
	RT_F					power;
}							t_object_mandelbulb;

static RT_F					mandelbulb_sdf(constant t_object *object, RT_F4 point)
{
	t_object_mandelbulb		data;
	RT_F4					z;
	RT_F					zr;
	RT_F					dr;
	RT_F					r;
	RT_F					phi;
	RT_F					theta;

	data = *(constant t_object_mandelbulb *)object->data;
	point = data.position - point;
	r = 0.;
    dr = 1.;
	z = point;
	for (int iter = 0; iter < data.iterations; iter++)
	{
		r = length(z);
		if (r > 2.)
        	break ;
        theta = acos(z.z / r);
        phi = atan2(z.y, z.x);

        dr = RT_POW((RT_F)r, (RT_F)(data.power - 1.)) * data.power * dr + 1.;

        zr = RT_POW(r, data.power);
        theta *= data.power;
        phi *= data.power;

        z = (RT_F4){RT_SIN(theta) * RT_COS(phi), RT_SIN(phi) * RT_SIN(theta), RT_COS(theta), 0.} * zr;
        z += point;
	}
	return (.5 * log(r) * r / dr);
}

// cl_rm_csg ///////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 		        s_object_csg
{
    int     		        id_positive;
    int     		        id_negative;
}					        t_object_csg;

static	RT_F		        csg_sdf_difference(const RT_F distance_a, const RT_F distance_b)
{
	return (RT_MAX(distance_a, -distance_b));
}

static RT_F			        sdf_csg_compute(constant t_object *object, RT_F4 point)
{
	if (object->type == object_sphere)
		return (sphere_sdf(object, point));
	else if (object->type == object_box)
        return (box_sdf(object, point));
    return (INFINITY);
}

static RT_F 		        csg_sdf(constant t_object *object, RT_F4 point)
{
	constant t_object_csg	*data;
	constant t_object       *scene_begin;
	RT_F					sdf[2];

    data = (constant t_object_csg *)object->data;
    scene_begin = object - object->id;
    sdf[0] = sdf_csg_compute(scene_begin + data->id_positive, point);
    sdf[1] = sdf_csg_compute(scene_begin + data->id_negative, point);

    return (csg_sdf_difference(sdf[0], sdf[1]));
}

// cl_object_x /////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_control.h"
#include "rt_parameters.h"

static int			object_intersect(constant t_object *object, t_intersection *intersection)
{
	if (object->type == object_sphere)
		return (sphere_intersect(object, intersection));
	else if (object->type == object_plane)
		return (plane_intersect(object, intersection));
	else if (object->type == object_cone)
		return (cone_intersect(object, intersection));
	else if (object->type == object_cylinder)
		return (cylinder_intersect(object, intersection));
	else if (object->type == object_paraboloid)
		return (paraboloid_intersect(object, intersection));
	else if (object->type == object_moebius)
		return (moebius_intersect(object, intersection));
	return (0);
}

static RT_F			object_sdf(constant t_object *object, RT_F4 point)
{
	if (object->is_csg)
		return (RT_INFINITY);
	if (object->type == object_sphere)
	{
//		printf("a\n");
		printf("%f %f %f\n", (*(constant t_object_sphere *)object->data).position.x, (*(constant t_sphere *)object->data).position.y, (*(constant t_sphere *)object->data).position.z);
		return (sphere_sdf(object, point));}
	else if (object->type == object_plane){
//		printf("b\n");
		return (plane_sdf(object, point));}
//	else if (object->type == object_julia)
//		return (julia_sdf(object, point));
//	else if (object->type == object_mandelbulb)
//		return (mandelbulb_sdf(object, point));
//	else if (object->type == object_torus)
//		return (torus_sdf(object, point));
//	else if (object->type == object_box)
//		return (box_sdf(object, point));
//	else if (object->type == object_csg)
//		return (csg_sdf(object, point));
	return (RT_INFINITY);
}

static RT_F			object_center_shift(constant t_object *object)
{
	if (object->type == object_sphere)
		return (sphere_center_shift(object));
	return (0);
}
// cl_object_normal ////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

static RT_F4		object_normal_rm(constant t_object *object, RT_F4 hit)
{
	RT_F4			nudged_hit;
	RT_F4			normal;
	RT_F4			normal_negative;
	RT_F4			nudge;

	nudge = (RT_F4){RT_CL_RM_NORMAL_EPSILON, 0., 0., 0.};
	nudged_hit = hit + nudge;
	normal.x = object_sdf(object, nudged_hit);
	nudged_hit = hit - nudge;
	normal_negative.x = object_sdf(object, nudged_hit);
	normal.x -= normal_negative.x;

	nudge = (RT_F4){0., RT_CL_RM_NORMAL_EPSILON, 0., 0.};
	nudged_hit = hit + nudge;
	normal.y = object_sdf(object, nudged_hit);
	nudged_hit = hit - nudge;
	normal_negative.y = object_sdf(object, nudged_hit);
	normal.y -= normal_negative.y;

	nudge = (RT_F4){0., 0., RT_CL_RM_NORMAL_EPSILON, 0.};
	nudged_hit = hit + nudge;
	normal.z = object_sdf(object, nudged_hit);
	nudged_hit = hit - nudge;
	normal_negative.z = object_sdf(object, nudged_hit);
	normal.z -= normal_negative.z;

    return (normalize(normal));
}

static RT_F4		object_normal_rt(
					constant t_object *object,
                    t_intersection *intersection)
{
	if (object->type == object_sphere)
		return (sphere_normal(object, intersection));
	else if (object->type == object_plane)
		return (plane_normal(object, intersection));
	else if (object->type == object_cone)
	    return (cone_normal(object, intersection));
	else if (object->type == object_cylinder)
	    return (cylinder_normal(object, intersection));
 	return (0);
}

static RT_F4		object_normal(
					constant t_object *object,
					t_intersection *intersection,
					constant t_cl_renderer_settings *settings)
{
	return (!settings->rm_mod ?
		object_normal_rt(object, intersection) :
		object_normal_rm(object, intersection->hit));
}
// cl_scene ////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct		s_scene
{
	t_object		objects[RT_CL_SCENE_CAPACITY];
	int				objects_length;
	int				lights[RT_CL_SCENE_CAPACITY];
    int 			lights_length;
}					t_scene;

static int			scene_intersect_rt(constant t_scene *scene, t_intersection *intersection)
{
	int				result;

	result = 0;
	for (int object_i = 0; object_i < scene->objects_length; object_i++)
    	result += object_intersect(scene->objects + object_i, intersection);
    return (result != 0);
}

static int			scene_intersect_rm(
					constant t_scene *scene,
                    t_intersection *intersection,
                    constant t_cl_renderer_settings *settings)
{
	int				result;
	RT_F4			ray;
	RT_F			total_distance;
	RT_F			temp_distance;
	RT_F			current_distance;
	int				current_id;

	result = 0;
	total_distance = 0.;
	ray = intersection->ray.origin + intersection->ray.direction * 10 * RT_EPSILON;
	for (int step = 0; step < settings->rm_step_limit; step++)
    {
    	current_distance = RT_INFINITY;
    	for (int object_i = 0; object_i < scene->objects_length; object_i++)
		{
			temp_distance = object_sdf(scene->objects + object_i, ray);
			if (temp_distance < current_distance)
			{
				current_distance = temp_distance;
				current_id = object_i;
			}
		}
    	if (current_distance < RT_RM_EPSILON)
    	{
    		result = 1;
    		intersection->object_id = current_id;
    		intersection->ray.t = total_distance;
    		break ;
    	}
    	total_distance += current_distance;
		ray = ray + intersection->ray.direction * current_distance * settings->rm_step_part;
    	if (total_distance > settings->rm_max_distance)
    		break ;
    }
    if (result)
    	intersection->hit = ray;
    return (result);
}

static int			scene_intersect(
					constant t_scene *scene,
					t_intersection *intersection,
					constant t_cl_renderer_settings *settings)
{
	int				result;

	result = !settings->rm_mod ?
		scene_intersect_rt(scene, intersection) :
		scene_intersect_rm(scene, intersection, settings);
	if (result)
	{
		intersection->material = scene->objects[intersection->object_id].material;
		if (!settings->rm_mod)
			intersection->hit = ray_intersect(&intersection->ray);
		intersection->normal = object_normal(scene->objects + intersection->object_id, intersection, settings);
	}
	return (result);
}
// cl_sample_x /////////////////////////////////////////////////////////////////////////////////////////////////////////

static void			create_coordinate_system(RT_F4 *normal, RT_F4 *nt, RT_F4 *nb)
{
	if (fabs(normal->x) > fabs(normal->y))
		*nt = (RT_F4){normal->z, 0., -1.f * normal->x, 0.};
	else
		*nt = (RT_F4){0., -1.f * normal->z, normal->y, 0.};
	*nt = normalize(*nt);
	*nb = cross(*normal, *nt);
}

static RT_F4		convert_sample(RT_F4 *normal, RT_F4 *sample, RT_F4 *nt, RT_F4 *nb)
{
	return ((RT_F4)
		{
			sample->x * nb->x + sample->y * normal->x + sample->z * nt->x,
			sample->x * nb->y + sample->y * normal->y + sample->z * nt->y,
			sample->x * nb->z + sample->y * normal->z + sample->z * nt->z,
			0.
		});
}

static RT_F4		sampler_transform(RT_F4 *normal, RT_F4 *sample)
{
	RT_F4		nt;
	RT_F4		nb;

	create_coordinate_system(normal, &nt, &nb);
	return (convert_sample(normal, sample, &nt, &nb));
}

static RT_F4		sample_uniform
					(RT_F4 *normal,
					RT_F *cosine,
					global ulong *rng_state)
{
	RT_F 			r[2];
	RT_F4			sample;
	RT_F			sin_theta;
	RT_F			phi;

	r[0] = rng(rng_state);
	r[1] = rng(rng_state);
	sin_theta = RT_SQRT(RT_MAX((RT_F)0.0f , (RT_F)1.0f - r[0] * r[0]));
	phi = 2.0f * RT_PI * r[1];
	*cosine = r[0];
	sample = (RT_F4)
		{
			sin_theta * RT_COS(phi),
			r[0],
			sin_theta * RT_SIN(phi),
			0.
		};
	return (sampler_transform(normal, &sample));
}
// cl_light_basic //////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

typedef struct			s_object_light_ambient
{
}						t_object_light_ambient;

typedef struct			s_object_light_point
{
	RT_F4				position;
}						t_object_light_point;

typedef struct			s_object_light_direct
{
	RT_F4				direction;
}						t_object_light_direct;

static RT_F4			static_get_direction(
						t_intersection *intersection,
						constant t_object *object)
{
	if (object->type == object_light_direct)
		return (((constant t_object_light_direct *)object->data)->direction);
	else if (object->type == object_light_point)
		return (((constant t_object_light_point *)object->data)->position - intersection->hit);
	return (0.);
}

static RT_F4			static_get_diffuse_intensity
						(t_intersection *intersection,
						RT_F4 *light_direction)
{
    RT_F	          		dot_value;

	dot_value = dot(*light_direction, intersection->normal);
	if (dot_value > 0.)
		return (dot_value / length(*light_direction));
	return (0.);
}

static RT_F4            static_get_specular_intensity
						(t_intersection *intersection,
						RT_F4 *light_direction)
{
	RT_F4            	halfway;
    RT_F	          	dot_value;

	halfway = normalize(*light_direction + intersection->ray.direction);
	dot_value = dot(halfway, intersection->normal);
	if (dot_value > 0.)
		return (RT_POW(dot_value, RT_CL_LIGHT_BASIC_BLINN));
	return (0.);

}

static int				static_is_shadowed(
						constant t_scene *scene,
						t_intersection *intersection,
						constant t_cl_renderer_settings *settings,
						RT_F4 *light_direction)
{
	t_intersection   	shadow;

	intersection_reset(&shadow);
	shadow.ray.origin = intersection->hit;
	shadow.ray.direction = *light_direction;
	scene_intersect(scene, &shadow, settings);
	return (shadow.ray.t >= RT_EPSILON && shadow.ray.t <= 1.);
}

static RT_F4			light_basic(
						constant t_scene *scene,
						t_intersection *intersection,
						constant t_cl_renderer_settings *settings)
{
	constant t_object	*object;
	RT_F4				color_diffuse;
	RT_F4				color_specular;
	RT_F4				light_direction;

	color_diffuse = 0.;
	color_specular = 0.;
	for (int i = 0; i < scene->lights_length; i++)
	{
		object = scene->objects + scene->lights[i];
		if (object->type == object_light_ambient)
		{
			color_diffuse += object->material.emission;
			continue ;
		}
		light_direction = static_get_direction(intersection, object);
		if (static_is_shadowed(scene, intersection, settings, &light_direction))
			continue ;
		color_diffuse += object->material.emission * static_get_diffuse_intensity(intersection, &light_direction);
		color_specular += static_get_specular_intensity(intersection, &light_direction);
	}
	return (intersection->material.color * color_diffuse + (RT_F4){1., 1., 1., 1.} * intersection->material.specular * color_specular);
}
// cl_light_area ///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"

static RT_F4		light_area(
					constant t_scene *scene,
					t_intersection *intersection_object,
					constant t_cl_renderer_settings *settings,
					global ulong *rng_state)
{
	t_intersection	intersection_light;
	RT_F4			radiance;
	RT_F4			light_position;
	RT_F4			light_direction;
	RT_F			emission_intensity;
	RT_F			cos_a_max;
	RT_F			omega;
	RT_F			sphere_radius;

	radiance = 0;
	for (int i = 0; i < scene->objects_length; i++)
	{
 		if (i == intersection_object->object_id)
			continue ;
		if (scene->objects[i].type != object_sphere)
			continue ;
		if (f4_max_component(scene->objects[i].material.emission) == 0.f)
			continue ;

		light_position = sphere_random(scene->objects + i, rng_state);
		light_direction = normalize(light_position - intersection_object->hit);

		intersection_light.ray.origin = intersection_object->hit + 10 * RT_EPSILON * light_direction;
		intersection_light.ray.direction = light_direction;
		intersection_reset(&intersection_light);

		if (!scene_intersect(scene, &intersection_light, settings))
			continue ;
		if (intersection_light.object_id != i)
			continue;

		emission_intensity = dot(intersection_object->normal, intersection_light.ray.direction);
		if (emission_intensity < 0.00001f)
			continue ;

		sphere_radius = ((constant t_object_sphere *)scene->objects[intersection_light.object_id].data)->radius;
		cos_a_max = RT_SQRT(1.f - (sphere_radius * sphere_radius) / length(intersection_object->hit - light_position));
		omega = 2 * RT_PI * (1.f - cos_a_max);
		radiance += scene->objects[i].material.emission * emission_intensity * omega * RT_1_PI;
	}
	return (radiance);
}

// cl_radiance /////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "rt_parameters.h"



static void			radiance_add(
					constant t_scene *scene,
					t_intersection *intersection,
					global RT_F4 *sample,
					constant t_cl_renderer_settings *settings,
					global ulong *rng_state)
{
	RT_F4			radiance;
	RT_F4			light;
	RT_F4			mask;
	RT_F			cosine;
	RT_F			choice;

	radiance = (RT_F4){0.f, 0.f, 0.f, 1.f};
	mask = 1;
	for (int depth = 0; depth < settings->sample_depth; depth++)
	{
		if (!scene_intersect(scene, intersection, settings))
    		break;

		if (depth > settings->sample_depth / 2 + 1 && f4_max_component(intersection->material.color) < rng(rng_state))
			break ;

		radiance += mask * intersection->material.emission;

		if (settings->light_basic)
		{
			light = light_basic(scene, intersection, settings);
            radiance += light * mask;
		}

		if (settings->light_area)
		{
			light = light_area(scene, intersection, settings, rng_state);
			radiance += light * mask * intersection->material.color;
		}

        if (f4_max_component(intersection->material.reflectance) > 0.|| f4_max_component(intersection->material.transparence) > 0.)
        {
            choice = rng(rng_state);
            if (choice < intersection->material.reflectance)
                intersection_reflect(intersection, intersection);
            else
                intersection_refract(intersection, intersection);
            mask /= choice < intersection->material.reflectance ? 1 : intersection->material.transparence;
        }
        else
		{
		    intersection->ray.origin = intersection->hit;

		    intersection->ray.direction = sample_uniform(&intersection->normal, &cosine, rng_state);
		    mask *= intersection->material.color * cosine;
        }
	}

	if (settings->sample_count == 1)
		*sample = radiance;
	else
		*sample += radiance;
}

static RT_F4		radiance_get(
					global RT_F4 *sample,
					constant t_cl_renderer_settings *settings)
{
	return (*sample / settings->sample_count);
}
// cl_filter ///////////////////////////////////////////////////////////////////////////////////////////////////////////

static void			filter_jitter(RT_F *x, global ulong *rng_state)
{
	RT_F			dx;

	dx = 2. * rng(rng_state);
	if (dx < 1.)
    	dx = RT_SQRT(dx) - 1;
    else
    	dx = 1. - RT_SQRT((RT_F)2. - dx);
    *x += dx;
}

// cl_camera ///////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct 		s_camera
{
	RT_F4   		position;
	RT_F4   		rotation;
	RT_F4   		axis_x;
	RT_F4   		axis_y;
	RT_F4   		axis_z;
	RT_F4   		forward;
	RT_F4   		forward_backup;
	int				width;
	int				height;
	int 			filter_antialiasing;
	int             filter_cartoon;
	int             filter_sepia;
	int 			focus;
	RT_F			aperture_size;
	RT_F			focal_length;
	int 			focus_request;
	RT_F2			focus_request_value;
}					t_camera;

static void			camera_focus(global t_camera *camera, t_ray *ray, global ulong *rng_state)
{
	RT_F4			focal_point;

	focal_point = camera->position + ray->direction * camera->focal_length;

	ray->origin.x += (.5 - rng(rng_state)) * camera->aperture_size;
	ray->origin.y += (.5 - rng(rng_state)) * camera->aperture_size;
	ray->origin.z += (.5 - rng(rng_state)) * camera->aperture_size;

	ray->direction = normalize(focal_point - ray->origin);
}

static t_ray		camera_build_ray(global t_camera *camera, int2 *screen, global ulong *rng_state)
{
	t_ray			result;
	RT_F4			up;
	RT_F4			right;
	RT_F 			xf;
	RT_F 			yf;

	xf = (RT_F)screen->x;
	yf = (RT_F)screen->y;
	if (camera->filter_antialiasing)
	{
		filter_jitter(&xf, rng_state);
    	filter_jitter(&yf, rng_state);
	}
	result.origin = camera->position;
	up = (RT_F4)camera->axis_y * (RT_F)(-1.f * yf + (camera->height - 1.f) / 2.f);
	right = (RT_F4)camera->axis_x * (RT_F)(xf - (camera->width - 1.f) / 2.f);
	result.direction = up + right + camera->forward;
	result.direction = normalize(result.direction);
	if (camera->focus)
		camera_focus(camera, &result, rng_state);
	return (result);
}

static void			camera_auto_focus(global t_camera *camera, constant t_scene *scene, constant t_cl_renderer_settings *settings)
{
    t_intersection	intersection;
    RT_F4			up;
    RT_F4			right;

    intersection.ray.origin = camera->position;
    up = (RT_F4)camera->axis_y * (RT_F)(-1.f * camera->focus_request_value.y + (camera->height - 1.f) / 2.f);
    right = (RT_F4)camera->axis_x * (RT_F)(camera->focus_request_value.x - (camera->width - 1.f) / 2.f);
    intersection.ray.direction = up + right + camera->forward;
    intersection.ray.direction = normalize(intersection.ray.direction);

    intersection_reset(&intersection);
    if (scene_intersect(scene, &intersection, settings))
    	camera->focal_length = intersection.ray.t + object_center_shift(scene->objects + intersection.object_id);

    camera->focus_request = 0;
}
 // cl_illumination_get ////////////////////////////////////////////////////////////////////////////////////////////////

 static RT_F4					illumination(
 								constant t_scene *scene,
 								global t_camera *camera,
 								t_intersection *intersection,
 								constant t_cl_renderer_settings *settings)
 {
 	constant t_object_sphere	*sphere;
 	RT_F						x;
 	RT_F						y;
 	RT_F4						k;
 	RT_F4						illumination;
 	t_intersection              shadow;

 	illumination = 0.;
 	shadow = *intersection;
 	for (int i = 0; i < scene->objects_length; i++)
 	{
        if (scene->objects[i].type != object_sphere)
        	continue ;
        if (f4_max_component(scene->objects[i].material.emission) == (RT_F)0.f)
        	continue ;

		sphere = (constant t_object_sphere	*)scene->objects[i].data;
 		k = normalize(intersection->ray.direction - normalize(sphere->position - intersection->ray.origin));
 		x = dot(intersection->ray.origin - sphere->position, k) + sphere->radius;
 		y = length(sphere->position - intersection->ray.origin + k * x);
 		scene_intersect(scene, &shadow, settings);
         if (shadow.ray.t < y * (RT_F)0.95)
             continue;
 		illumination += RT_POW((RT_F)(settings->illumination_value * sphere->radius / x), (RT_F)5.) * scene->objects[i].material.emission;
 	}
 	return (illumination);
 }

// cl_main /////////////////////////////////////////////////////////////////////////////////////////////////////////////

kernel void			cl_main(
					global t_camera *camera,
					constant t_scene *scene,
					global t_color *image,
					global RT_F4 *sample_store,
					constant t_cl_renderer_settings *settings,
					global ulong *rng_state)
{
	int				global_id;
	int2			screen;
	t_intersection	intersection;
	RT_F4           illumination_effect;

    global_id = get_global_id(0);

	screen.x = global_id % camera->width;
	screen.y = global_id / camera->width;

	intersection.ray = camera_build_ray(camera, &screen, rng_state);
	intersection_reset(&intersection);

	if (!global_id && camera->focus_request)
		camera_auto_focus(camera, scene, settings);

	if (settings->illumination)
		illumination_effect = illumination(scene, camera, &intersection, settings);
	else
		illumination_effect = 0.;

    radiance_add(scene, &intersection, sample_store + global_id, settings, rng_state);

	image[global_id] = color_unpack(illumination_effect + radiance_get(sample_store + global_id, settings),
									camera->filter_sepia);
}


