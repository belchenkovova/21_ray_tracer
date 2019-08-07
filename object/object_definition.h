#ifndef OBJECT_H
# define OBJECT_H

# include "options.h"
# include "material.h"

typedef enum		e_object_type
{
	object_sphere = 0,
	object_plane
}					t_object_type;

typedef struct		s_object
{
	char			data[OBJECT_DATA_CAPACITY];
	t_object_type	type;
	t_material		material;
}					t_object;

#endif
