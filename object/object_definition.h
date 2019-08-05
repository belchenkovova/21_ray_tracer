#ifndef OBJECT_H
# define OBJECT_H

# include "options.h"

typedef enum		e_object_type
{
	object_sphere = 0,
	object_plane
}					t_object_type;

typedef struct		s_object
{
	t_object_type	type;
	char			data[OBJECT_DATA_CAPACITY];
}					t_object;



#endif
