#include "scene.h"

t_object			*scene_find_object_by_id(t_scene *scene, int id)
{
	if (id < 0 || id >= scene->objects_length)
	{
		rt_raise_warning("Scene : Object not found (id = %i)", id);
		return (NULL);
	}
	return (scene->objects + id);
}

t_object			*scene_find_object_by_name(t_scene *scene, CHAR_REF name)
{
	int 			i;

	i = 0;
	while (i < scene->objects_length)
	{
		if (!ft_strcmp(scene->objects[i].name, name))
			return (scene->objects + i);
		i++;
	}
	rt_raise_warning("Scene : Object not found (name = '%s')", name);
	return (NULL);
}

int 				scene_find_texture_by_name(t_scene *scene, CHAR_REF name)
{
	int 			i;

	i = 0;
	while (i <= scene->texture.textures_number)
	{
		if (!ft_strcmp(scene->texture.name[i], name))
			return (i);
		i++;
	}
	rt_raise_warning("Scene : Texture not found (name = '%s')", name);
	return (-1);
}