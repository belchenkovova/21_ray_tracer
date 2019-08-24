#include "scene.h"

t_object			*scene_get_space(t_scene *scene)
{
	if (scene->objects_length < RT_CL_SCENE_CAPACITY)
		return (scene->objects + scene->objects_length++);
	return (NULL);
}