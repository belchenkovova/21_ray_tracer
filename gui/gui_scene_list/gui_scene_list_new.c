#include "gui_scene_list.h"

t_gui_scene_list		*gui_scene_list_new(void)
{
	t_gui_scene_list	*new;

	new = malloc(sizeof(t_gui_scene_list));
	new->data = NULL;
	new->view = NULL;
	new->select = NULL;
	return (new);
}