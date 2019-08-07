#include "cl_renderer.h"

static void			cl_renderer_data_size_init(t_cl_renderer *renderer)
{
	renderer->data_size.camera = sizeof(t_camera);
	renderer->data_size.scene = sizeof(t_scene);
	renderer->data_size.image =
			sizeof(t_color) * renderer->image->width * renderer->image->height;
	renderer->data_size.settings = sizeof(t_cl_settings);
	renderer->data_size.sample_store = sizeof(API_FLOAT4)
		 * renderer->image->width * renderer->image->height;
	renderer->data_size.rng_state = sizeof(unsigned int);
}

static void			cl_renderer_data_host_init(t_cl_renderer *renderer)
{
	renderer->data_host.camera =
			camera_new(&renderer->image->width, &renderer->image->height);
	renderer->data_host.scene = scene_new();
	renderer->data_host.image = renderer->image->color_buffer;
	renderer->data_host.settings.sample_count = CL_DEFAULT_SAMPLES;
	renderer->data_host.settings.sample_depth = CL_DEFAULT_PATH_DEPTH;
	renderer->data_host.settings.russian_depth = CL_DEFAULT_RUSSIAN_DEPTH;
	renderer->data_host.settings.russian_depth = CL_DEFAULT_SRGB;
	renderer->data_host.rng_seed = time(0);
}

static void			cl_renderer_data_device_init(t_cl_renderer *renderer)
{
	renderer->data_device.camera = clCreateBuffer(renderer->context,
		CL_MEM_READ_ONLY, renderer->data_size.camera, NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.scene = clCreateBuffer(renderer->context,
		CL_MEM_READ_ONLY, renderer->data_size.scene, NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.image = clCreateBuffer(renderer->context,
		CL_MEM_WRITE_ONLY, renderer->data_size.image, NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.settings = clCreateBuffer(renderer->context,
		CL_MEM_READ_ONLY, renderer->data_size.settings, NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.sample_store = clCreateBuffer(renderer->context,
		CL_MEM_WRITE_ONLY, renderer->data_size.sample_store,
		NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.rng_seed = clCreateBuffer(renderer->context,
		CL_MEM_READ_WRITE, renderer->data_size.rng_state,
		NULL, &renderer->error);
	ASSERT(renderer->error == 0)

}

void 				cl_renderer_init_data(t_cl_renderer *renderer)
{
	cl_renderer_data_size_init(renderer);
	cl_renderer_data_host_init(renderer);
	cl_renderer_data_device_init(renderer);
}