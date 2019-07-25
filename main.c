#include "renderer.h"
#include "shape_list.h"
#include "material_list.h"

void				cornell_box(t_renderer *renderer)
{
	renderer->camera->position = (t_vector3){0., 10., 180.};

	scene_add_shape(renderer->scene, shape_sphere((t_vector3){-10., 25., 45.}, 2.5, MATERIAL_LIGHT));
	scene_add_shape(renderer->scene, shape_sphere((t_vector3){10., 25., 25.}, 2.5, MATERIAL_LIGHT));

	scene_add_shape(renderer->scene, shape_sphere((t_vector3){-15., 0., 0.}, 7., MATERIAL_MIRROR));
	scene_add_shape(renderer->scene, shape_sphere((t_vector3){0., 0., 20.}, 7., MATERIAL_WHITE));
	scene_add_shape(renderer->scene, shape_sphere((t_vector3){5., 0., 50.}, 7., MATERIAL_GLASS));

	scene_add_shape(renderer->scene, shape_plane((t_vector3){0., -15., 0.}, (t_vector3){0., 1., 0.}, MATERIAL_WHITE)); // lower
	scene_add_shape(renderer->scene, shape_plane((t_vector3){0., 35., 0.}, (t_vector3){0., -1., 0.}, MATERIAL_WHITE)); // upper
	scene_add_shape(renderer->scene, shape_plane((t_vector3){-30, 0., 0.}, (t_vector3){1., 0., 0.}, MATERIAL_GREEN)); // left
	scene_add_shape(renderer->scene, shape_plane((t_vector3){30., 0., 0.}, (t_vector3){-1., 0., 0.}, MATERIAL_RED)); // right

	scene_add_shape(renderer->scene, shape_plane((t_vector3){0., 0., -40.}, (t_vector3){0., 0., 1.}, MATERIAL_WHITE)); // back
	scene_add_shape(renderer->scene, shape_plane((t_vector3){0., 0., 190.}, (t_vector3){0., 0., 1.}, MATERIAL_WHITE)); // front
}

void 				venus(t_renderer *renderer)
{
	renderer->camera->position = (t_vector3){0., 0., 2000.};
	renderer->scene->accelerated_mesh =	accelerated_mesh_new("../obj_tests/venus.obj", MATERIAL_GREEN);
}

void 				mesh(t_renderer *renderer)
{
	renderer->camera->position = (t_vector3){0., 5., 50.};
	renderer->scene->accelerated_mesh =	accelerated_mesh_new("../obj_tests/teapot.obj", MATERIAL_RED);

	scene_add_shape(renderer->scene, shape_sphere((t_vector3){2., 7., 25.}, .5, MATERIAL_LIGHT));

	scene_add_shape(renderer->scene, shape_plane((t_vector3){0., -2., 0.}, (t_vector3){0., 1., 0.}, MATERIAL_WHITE)); // lower
	scene_add_shape(renderer->scene, shape_plane((t_vector3){0., 12., 0.}, (t_vector3){0., -1., 0.}, MATERIAL_WHITE)); // upper
	scene_add_shape(renderer->scene, shape_plane((t_vector3){-12, 0., 0.}, (t_vector3){1., 0., 0.}, MATERIAL_WHITE)); // left
	scene_add_shape(renderer->scene, shape_plane((t_vector3){12., 0., 0.}, (t_vector3){-1., 0., 0.}, MATERIAL_WHITE)); // right

	scene_add_shape(renderer->scene, shape_plane((t_vector3){0., 0., -10.}, (t_vector3){0., 0., 1.}, MATERIAL_WHITE)); // back
	scene_add_shape(renderer->scene, shape_plane((t_vector3){0., 0., 60.}, (t_vector3){0., 0., 1.}, MATERIAL_WHITE)); // front
}

int					main()
{
	t_renderer		*renderer;

	renderer = renderer_new();

	mesh(renderer);
//	venus(renderer);
	//cornell_box(renderer);

	renderer_loop(&renderer);
	return (0);
}