#include "gui_scene_edit.h"

void 				gui_scene_edit_show
					(t_gui_scene_edit *edit, t_object *object)
{
	const char		*type_str;

	gtk_widget_show(GTK_WIDGET(edit->info));
	type_str = object_translate(object->type);
	gui_entry_set_str(edit->name, object->name);
	gui_entry_set_str(edit->type, type_str);
	gtk_stack_set_visible_child_name(edit->stack, type_str);
	if (object->type == object_light_point)
		gui_object_light_point_get(&edit->light_point, object);
	else if (object->type == object_light_direct)
		gui_object_light_direct_get(&edit->light_direct, object);
	else if (object->type == object_sphere)
		gui_object_sphere_get(&edit->sphere, object);
	else if (object->type == object_plane)
		gui_object_plane_get(&edit->plane, object);
	else if (object->type == object_cone)
		gui_object_cone_get(&edit->cone, object);
	else if (object->type == object_cylinder)
		gui_object_cylinder_get(&edit->cylinder, object);
	else if (object->type == object_box)
		gui_object_box_get(&edit->box, object);
	else if (object->type == object_paraboloid)
		gui_object_paraboloid_get(&edit->paraboloid, object);
	else if (object->type == object_moebius)
		gui_object_moebius_get(&edit->moebius, object);
	else if (object->type == object_torus)
		gui_object_torus_get(&edit->torus, object);
	else if (object->type == object_mandelbulb)
		gui_object_mandelbulb_get(&edit->mandelbulb, object);
	else if (object->type == object_julia)
		gui_object_julia_get(&edit->julia, object);
	else
		return ;
	gui_material_get(&edit->material, &object->material);
}