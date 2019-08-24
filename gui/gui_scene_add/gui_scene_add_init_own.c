#include "gui_scene_add.h"

void 				gui_scene_add_init_own
					(t_gui_scene_add *add, GtkBuilder *builder)
{
	add->dialog = RT_GUI_GET(builder, "dialog");
	add->name = RT_GUI_GET(builder, "scene_add_name");
	add->type_combo = RT_GUI_GET(builder, "scene_add_type_combo");
	add->type_list = RT_GUI_GET(builder, "scene_add_list");
	add->type_entry = RT_GUI_GET(builder, "scene_add_type_entry");
	add->stack = RT_GUI_GET(builder, "scene_add_stack");
	add->material_color_box =
		RT_GUI_GET(builder, "scene_add_material_color_box");
}