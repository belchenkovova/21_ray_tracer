#include "gui_object_x.h"

t_gui_object_light_direct		gui_object_light_direct_init
								(t_gui_init_light_direct *i,
								GtkBuilder *builder)
{
	t_gui_object_light_direct	direct;

	direct.direction_x = RT_GUI_GET(builder, i->direction_x);
	direct.direction_y = RT_GUI_GET(builder, i->direction_y);
	direct.direction_z = RT_GUI_GET(builder, i->direction_z);
	return (direct);
}

void							gui_object_light_direct_get
								(t_gui_object_light_direct *gui,
								t_object *object)
{
	t_object_light_direct		*data;

	data = (t_object_light_direct *)object->data;
	gui_entry_set_f(gui->direction_x, data->direction.x);
	gui_entry_set_f(gui->direction_y, data->direction.y);
	gui_entry_set_f(gui->direction_z, data->direction.z);
}

void 							gui_object_light_direct_set
								(t_gui_object_light_direct *gui,
								t_object *object)
{
	t_object_light_direct		*data;

	data = (t_object_light_direct *)object->data;
	data->direction.x = gui_entry_get_f(gui->direction_x);
	data->direction.y = gui_entry_get_f(gui->direction_y);
	data->direction.z = gui_entry_get_f(gui->direction_z);
}