#include "gui.h"
#include "gui_signal_connect_x.h"
#include "cl_renderer.h"
#include "material_list.h"

void				scene_test_a(t_scene *scene)
{
//	object_build(scene_get_space(scene), object_sphere,
//		MATERIAL_WHITE, (RT_F4_API){0., 0., 0}, 2.);
//	object_build(scene_get_space(scene), object_plane,
//		MATERIAL_BLUE, (RT_F4_API){0., 0., 0}, (RT_F4_API){1., 0., 0.});
//    object_build(scene_get_space(scene), object_sphere,
//    	MATERIAL_WHITE, (RT_F4_API){-10., 10., -40.}, 2.);
//    object_build(scene_get_space(scene), object_sphere,
//    	MATERIAL_WHITE, (RT_F4_API){10., 10., -40.}, 2.);
//    object_build(scene_get_space(scene), object_sphere,
//    	MATERIAL_MIRROR, (RT_F4_API){-10., 2., -10.}, 3.1);
    object_build(scene_get_space(scene), object_sphere,
		MATERIAL_LIGHT, (RT_F4_API){10., 0., -10.}, 3.);
    scene_give_name(scene, "Light", scene_name_last);
    object_build(scene_get_space(scene), object_plane,
		MATERIAL_WHITE, (RT_F4_API){0., 0., -70.}, (RT_F4_API){0., 0., 1.});
	scene_give_name(scene, "Front Plane", scene_name_last);
    object_build(scene_get_space(scene), object_plane,
		MATERIAL_WHITE, (RT_F4_API){0., 0., 100.}, (RT_F4_API){0., 0., -1.});
	scene_give_name(scene, "Back Plane", scene_name_last);
    object_build(scene_get_space(scene), object_plane,
    	MATERIAL_RED, (RT_F4_API){30., 0., 0.}, (RT_F4_API){-1., 0., 0.});
	scene_give_name(scene, "Right Plane", scene_name_last);
	object_build(scene_get_space(scene), object_plane,
		MATERIAL_GREEN, (RT_F4_API){-30., 0., 0.}, (RT_F4_API){1., 0., 0.});
	scene_give_name(scene, "Left Plane", scene_name_last);
    object_build(scene_get_space(scene), object_plane,
    	MATERIAL_WHITE, (RT_F4_API){0., 50., 0.}, (RT_F4_API){0., -1., 0.});
	scene_give_name(scene, "Upper Plane", scene_name_last);
    object_build(scene_get_space(scene), object_plane,
		MATERIAL_WHITE, (RT_F4_API){0., -50., 0.}, (RT_F4_API){0., 1., 0.});
	scene_give_name(scene, "Lower Plane", scene_name_last);
}

void				scene_test_b(t_scene *scene)
{
    object_build(scene_get_space(scene), object_light_ambient,
		MATERIAL_LIGHT_AMBIENT);
    object_build(scene_get_space(scene), object_light_point,
		MATERIAL_LIGHT_BASIC, (RT_F4_API){10., -10., 10.});
	object_build(scene_get_space(scene), object_sphere,
		MATERIAL_WHITE, (RT_F4_API){-10., 10., -40.}, 2.);
	object_build(scene_get_space(scene), object_sphere,
		MATERIAL_WHITE, (RT_F4_API){10., 10., -40.}, 2.);
	object_build(scene_get_space(scene), object_sphere,
		MATERIAL_MIRROR, (RT_F4_API){-10., 0., -10.}, 3.1);
	object_build(scene_get_space(scene), object_plane,
		MATERIAL_WHITE, (RT_F4_API){0., 0., -70.}, (RT_F4_API){0., 0., 1.});
	scene_give_name(scene, "Front Plane", scene_name_last);
	object_build(scene_get_space(scene), object_plane,
		MATERIAL_WHITE, (RT_F4_API){0., 0., 100.}, (RT_F4_API){0., 0., -1.});
	scene_give_name(scene, "Back Plane", scene_name_last);
	object_build(scene_get_space(scene), object_plane,
		MATERIAL_RED, (RT_F4_API){30., 0., 0.}, (RT_F4_API){-1., 0., 0.});
	scene_give_name(scene, "Right Plane", scene_name_last);
	object_build(scene_get_space(scene), object_plane,
		MATERIAL_GREEN, (RT_F4_API){-30., 0., 0.}, (RT_F4_API){1., 0., 0.});
	scene_give_name(scene, "Left Plane", scene_name_last);
	object_build(scene_get_space(scene), object_plane,
		MATERIAL_WHITE, (RT_F4_API){0., 50., 0.}, (RT_F4_API){0., -1., 0.});
	scene_give_name(scene, "Upper Plane", scene_name_last);
	object_build(scene_get_space(scene), object_plane,
		MATERIAL_WHITE, (RT_F4_API){0., -50., 0.}, (RT_F4_API){0., 1., 0.});
	scene_give_name(scene, "Lower Plane", scene_name_last);
}

int					main(int argc, char **argv)
{
	t_gui			*gui;

	gui = gui_new(&argc, &argv);
	gui_signal_connect_all(gui);
	gui->renderer = cl_renderer_new(gui->image);
	scene_test_a(gui->renderer->data.scene);
	gui->renderer->data.camera->position.x = -1.;
	gui->renderer->data.camera->position.z = 30.;
    scene_update(gui->renderer->data.scene);
	gui_update(gui);
	gui_loop(gui);
	gui_delete(&gui);
	return (0);
}