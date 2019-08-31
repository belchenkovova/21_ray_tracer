#include "cl_renderer.h"

int 				cl_renderer_camera_move
					(t_cl_renderer *renderer, t_camera_movement movement)
{
	RT_F4_API		test;

	test = camera_move(renderer->data.camera, movement, RT_CAMERA_MOVE_VALUE);
	if (scene_point_check(renderer->data.scene, &test) == SCENE_POINT_INSIDE)
		renderer->data.camera->position = test;
	else
		return (0);
	cl_renderer_flag_set(renderer, cl_flag_update_camera);
	cl_renderer_flag_set(renderer, cl_flag_reset_samples);
	return (1);
}

void 				cl_renderer_camera_rotate
					(t_cl_renderer *renderer,
					t_f4_rotation_axis axis,
					t_f4_rotation_direction direction)
{
	camera_rotate(renderer->data.camera, axis, direction, RT_CAMERA_ROTATE_VALUE);
	cl_renderer_flag_set(renderer, cl_flag_update_camera);
	cl_renderer_flag_set(renderer, cl_flag_reset_samples);
}

void				cl_renderer_camera_reset(t_cl_renderer *renderer)
{
	*renderer->data.camera = *renderer->data.camera_unmodified;
	cl_renderer_flag_set(renderer, cl_flag_update_camera);
	cl_renderer_flag_set(renderer, cl_flag_reset_samples);
}

void				cl_renderer_camera_save(t_cl_renderer *renderer)
{
	*renderer->data.camera_unmodified = *renderer->data.camera;
}
