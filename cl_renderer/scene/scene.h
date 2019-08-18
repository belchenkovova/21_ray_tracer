#ifndef SCENE_H
# define SCENE_H

# include "rt_parameters.h"

# include "object_interaction.h"

# include <stdlib.h>

typedef struct				s_scene
{
	t_object				objects[RT_CL_SCENE_CAPACITY];
	int						objects_length;
}							t_scene;

t_scene						*scene_new(void);
void						scene_delete(t_scene **scene);

t_object					*scene_get_space(t_scene *scene);
void 						scene_remove_object(t_scene *scene, int object_id);

#endif
