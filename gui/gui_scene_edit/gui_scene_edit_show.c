#include "gui_scene_edit.h"

void 					gui_scene_edit_show
						(t_gui_scene_edit *edit, t_object *object)
{
	const char			*type_str;

	gtk_widget_show(GTK_WIDGET(edit->info));
	type_str = object_translate(object->type);
	gui_entry_set_str(edit->name, object->name);
	gui_entry_set_str(edit->type, type_str);
	gtk_stack_set_visible_child_name(edit->stack, type_str);
	if (object->type == object_type_light_point)
		gui_object_light_point_get(&edit->light_point, object);
	else if (object->type == object_type_light_direct)
		gui_object_light_direct_get(&edit->light_direct, object);
	else if (object->type == object_type_sphere)
		gui_object_sphere_get(&edit->sphere, object);
	else if (object->type == object_type_plane)
		gui_object_plane_get(&edit->plane, object);
	else if (object->type == object_type_cone)
		gui_object_cone_get(&edit->cone, object);
	else if (object->type == object_type_cylinder)
		gui_object_cylinder_get(&edit->cylinder, object);
	else if (object->type == object_type_box)
		gui_object_box_get(&edit->box, object);
	else if (object->type == object_type_paraboloid)
		gui_object_paraboloid_get(&edit->paraboloid, object);
	else if (object->type == object_type_moebius)
		gui_object_moebius_get(&edit->moebius, object);
	else if (object->type == object_type_limited)
		gui_object_pair_get(&edit->limited, object);
	else if (object->type == object_type_torus)
		gui_object_torus_get(&edit->torus, object);
	else if (object->type == object_type_mandelbulb)
		gui_object_mandelbulb_get(&edit->mandelbulb, object);
	else if (object->type == object_type_julia)
		gui_object_julia_get(&edit->julia, object);
	else if (object->type == object_type_perforated_cube)
		gui_object_p_cube_get(&edit->p_cube, object);
	else if (object->type == object_type_explosion)
		gui_object_explosion_get(&edit->explosion, object);
	else if (object->type == object_type_csg)
		gui_object_pair_get(&edit->csg, object);
	else
		rt_raise_warning("GUI Editor : Unknown type");
	if (object_flag_get(object) & RT_OBJECT_HAS_TEXTURE)
		gui_material_texture_enable(&edit->material);
	else
		gui_material_texture_disable(&edit->material);
	gui_material_switch_mod(&edit->material, object->texture_id == -1 ?
		gui_material_material : gui_material_texture);
	gui_material_get(&edit->material, &object->material);
}