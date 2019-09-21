#ifndef MATERIAL_H
# define MATERIAL_H

# include "rt_cl_include.h"
# include "rt_float.h"
# include "rt_parameters.h"

typedef struct 		s_material
{
	RT_F4_API		color;
	RT_F4_API		emission;
	RT_F			specular;
	RT_F			reflectance;
	RT_F			transparency;
}					t_material;

#endif
