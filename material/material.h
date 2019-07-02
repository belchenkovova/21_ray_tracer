#ifndef MATERIAL_H
# define MATERIAL_H

# include "vector3.h"

typedef struct 		s_material
{
	t_vector3		color;
	float 			diffuse;
	float 			specular;
	float 			reflect;
}					t_material;

#endif
