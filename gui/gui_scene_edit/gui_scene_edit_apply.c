#include "gui_scene_edit.h"

void 				gui_scene_edit_apply
					(t_gui_scene_edit *edit, t_object* object)
{
	rt_assert_critical(edit->common != NULL, "GUI : Editor list ptr is NULL");
	ft_strcpy(object->name, gui_entry_get_str(edit->name));
	gtk_list_store_set(edit->common->full, &edit->iter,
					   gui_objects_column_name, object->name, -1);
	if (object->type == object_type_light_point)
		gui_object_light_point_set(&edit->light_point, object);
	else if (object->type == object_type_light_direct)
		gui_object_light_direct_set(&edit->light_direct, object);
	else if (object->type == object_type_sphere)
		gui_object_sphere_set(&edit->sphere, object);
	else if (object->type == object_type_plane)
		gui_object_plane_set(&edit->plane, object);
	else if (object->type == object_type_cone)
		gui_object_cone_set(&edit->cone, object);
	else if (object->type == object_type_cylinder)
		gui_object_cylinder_set(&edit->cylinder, object);
	else if (object->type == object_type_box)
		gui_object_box_set(&edit->box, object);
	else if (object->type == object_type_paraboloid)
		gui_object_paraboloid_set(&edit->paraboloid, object);
	else if (object->type == object_type_moebius)
		gui_object_moebius_set(&edit->moebius, object);
	else if (object->type == object_type_limited)
		gui_object_pair_set(&edit->limited, object);
	else if (object->type == object_type_torus)
		gui_object_torus_set(&edit->torus, object);
	else if (object->type == object_type_mandelbulb)
		gui_object_mandelbulb_set(&edit->mandelbulb, object);
	else if (object->type == object_type_julia)
		gui_object_julia_set(&edit->julia, object);
	else if (object->type == object_type_perforated_cube)
		gui_object_p_cube_set(&edit->p_cube, object);
	else if (object->type == object_type_explosion)
		gui_object_explosion_set(&edit->explosion, object);
	else if (object->type == object_type_csg)
		gui_object_pair_set(&edit->csg, object);
	gui_material_set(&edit->material, &object->material);
	gui_material_get(&edit->material, &object->material);
}