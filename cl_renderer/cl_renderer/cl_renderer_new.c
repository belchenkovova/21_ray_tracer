#include "cl_renderer.h"

static void				static_data_init(t_cl_renderer *renderer)
{
	int 				i;

	renderer->data.camera =
		camera_new(&renderer->image->width, &renderer->image->height);
	renderer->data.scene = scene_new();
	renderer->data.image = renderer->image->color_buffer;
	renderer->data.texture = texture_new();
	cl_renderer_settings_init(&renderer->data.settings);
	i = 0;
	renderer->data.rng_state = malloc(sizeof(u_long) * renderer->pixel_number);
	srand(21);
	while (i < renderer->pixel_number)
		renderer->data.rng_state[i++] = rand();
}

static void				static_set_args(t_cl_renderer *renderer)
{
	// camera
	cl_arg_list_push(renderer->args, renderer->data.camera,
		sizeof(t_camera), CL_MEM_READ_WRITE);
	// scene
	cl_arg_list_push(renderer->args, renderer->data.scene,
		sizeof(t_scene), CL_MEM_READ_ONLY);
	// image
	cl_arg_list_push(renderer->args, renderer->image->color_buffer,
		sizeof(t_color) * renderer->pixel_number, CL_MEM_WRITE_ONLY);
	//samples
	cl_arg_list_push(renderer->args, NULL,
		sizeof(RT_F4_API) * renderer->pixel_number, CL_MEM_READ_WRITE);
	// settings
	cl_arg_list_push(renderer->args, &renderer->data.settings,
		sizeof(t_cl_renderer_settings), CL_MEM_READ_ONLY);
	// rng
	cl_arg_list_push(renderer->args, renderer->data.rng_state,
		sizeof(u_long) * renderer->pixel_number, CL_MEM_READ_WRITE);
	// texture_data
	cl_arg_list_push(renderer->args, renderer->data.texture->data,
					 sizeof(renderer->data.texture->data), CL_MEM_READ_WRITE);
	// texture
	cl_arg_list_push(renderer->args, renderer->data.texture,
		sizeof(t_texture), CL_MEM_READ_WRITE);
	cl_builder_set_args(renderer->builder, renderer->args);
}

t_cl_renderer			*cl_renderer_new(t_gui_image *image)
{
	t_cl_renderer		*new;

	new = malloc(sizeof(t_cl_renderer));
	new->image = image;
	new->pixel_number = image->width * image->height;
#ifndef RT_NO_OPEN_CL
	new->builder = cl_builder_new();
	new->args = cl_arg_list_new(new->builder->context, new->builder->queue);
#else
	new->builder = NULL;
	new->args = NULL;
#endif
	static_data_init(new);
#ifndef RT_NO_OPEN_CL
	static_set_args(new);
#endif
	return (new);
}