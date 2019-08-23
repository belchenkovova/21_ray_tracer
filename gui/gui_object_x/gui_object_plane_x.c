#include "gui_object_x.h"

t_gui_object_plane		gui_object_plane_set
						(t_gui_init_plane *init, GtkBuilder *builder)
{
	t_gui_object_plane	plane;

	plane.box = RT_GUI_GET(builder, init->box);
	plane.position_x = RT_GUI_GET(builder, init->position_x);
	plane.position_y = RT_GUI_GET(builder, init->position_y);
	plane.position_z = RT_GUI_GET(builder, init->position_z);
	plane.normal_x = RT_GUI_GET(builder, init->normal_x);
	plane.normal_y = RT_GUI_GET(builder, init->normal_y);
	plane.normal_z = RT_GUI_GET(builder, init->normal_z);
	return (plane);
}

void 					gui_object_plane_show
						(t_gui_object_plane *gui, t_object *object)
{
	t_object_plane		*data;

	data = object ? (t_object_plane *)object->data : NULL;
	if (!data)
		return ;
	gui_entry_set_f(gui->position_x, data->position.x);
	gui_entry_set_f(gui->position_y, data->position.y);
	gui_entry_set_f(gui->position_z, data->position.z);
	gui_entry_set_f(gui->normal_x, data->normal.x);
	gui_entry_set_f(gui->normal_y, data->normal.y);
	gui_entry_set_f(gui->normal_z, data->normal.z);
}

void 					gui_object_plane_build
						(t_gui_object_plane *gui, t_object *object)
{
	t_object_plane		*data;

	data = (t_object_plane *)object->data;
	object->type = object_plane;
	data->position.x = gui_entry_get_f(gui->position_x);
	data->position.y = gui_entry_get_f(gui->position_y);
	data->position.z = gui_entry_get_f(gui->position_z);
	data->normal.x = gui_entry_get_f(gui->normal_x);
	data->normal.y = gui_entry_get_f(gui->normal_y);
	data->normal.z = gui_entry_get_f(gui->normal_z);
}