#include "object_definition.h"

const char 			*object_translate(t_object_type type)
{
	if (type == object_light_ambient)
		return ("Ambient light");
	else if (type == object_light_point)
		return ("Point light");
	else if (type == object_light_direct)
		return ("Direct light");
	else if (type == object_sphere)
		return ("Sphere");
	else if (type == object_plane)
		return ("Plane");
	else if (type == object_cone)
		return ("Cone");
	else if (type == object_cylinder)
		return ("Cylinder");
	else if (type == object_box)
		return ("Box");
	else if (type == object_paraboloid)
		return ("Paraboloid");
	else if (type == object_moebius)
		return ("Moebius strip");
	else if (type == object_torus)
		return ("Torus");
	else if (type == object_mandelbulb)
		return ("Mandelbulb");
	else if (type == object_julia)
		return ("Julia");
	else if (type == object_csg)
		return ("CSG");
	return ("Unknown");
}