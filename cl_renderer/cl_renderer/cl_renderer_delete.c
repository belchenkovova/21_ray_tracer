#include "cl_renderer.h"

void				cl_renderer_delete(t_cl_renderer **renderer)
{
	cl_builder_delete(&(*renderer)->builder);
	cl_arg_list_delete(&(*renderer)->args);
	camera_delete(&(*renderer)->data.camera);
	scene_delete(&(*renderer)->data.scene);
	cl_rng_state_delete(&(*renderer)->data.rng_state);
	free(*renderer);
	*renderer = NULL;
}