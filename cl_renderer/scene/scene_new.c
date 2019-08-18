#include "scene.h"

t_scene				*scene_new(void)
{
	t_scene			*new;
	int 			i;

	new = malloc(sizeof(t_scene));
	new->objects_length = 0;
	i = 0;
	while (i < RT_CL_SCENE_CAPACITY)
	{
		new->objects[i].id = i;
		i++;
	}
	return (new);
}