#include "cl_renderer.h"

static void			static_run_queue(t_cl_renderer *renderer)
{
	int 			error;
	error = clEnqueueNDRangeKernel(renderer->builder->queue,
		renderer->builder->kernel, 1, NULL,
		&renderer->pixel_number, NULL, 0, NULL, NULL);
	ASSERT(error == 0)
	cl_args_list_read(renderer->args, cl_arg_image);
	if (renderer->data.camera->select_request)
	{
		cl_args_list_read(renderer->args, cl_arg_camera);
		scene_choose(renderer->data.scene, renderer->data.camera->select_request_object);
		cl_renderer_flag_set(renderer, cl_flag_update_scene);
	}
	if (renderer->data.camera->focus_request)
		cl_args_list_read(renderer->args, cl_arg_camera);
	renderer->data.settings.sample_count++;
	cl_renderer_flag_set(renderer, cl_flag_update_settings);
}

void				cl_renderer_render(t_cl_renderer *renderer)
{
#ifndef RT_OPEN_CL_DISABLED
	cl_renderer_flag_perform(renderer);
	static_run_queue(renderer);
	gtk_image_set_from_pixbuf(renderer->image->image,
		renderer->image->gdk_buffer);
#endif
}
