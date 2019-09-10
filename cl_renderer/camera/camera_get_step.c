#include "camera.h"

RT_F4_API			camera_get_step(t_camera *camera, t_rt_movement movement)
{
	if (movement == rt_movement_left)
		return (f4_mul(camera->axis_x, -1.f));
	else if (movement == rt_movement_right)
		return (f4_mul(camera->axis_x, 1.f));
	else if (movement == rt_movement_up)
		return (f4_mul(camera->axis_y, 1.f));
	else if (movement == rt_movement_down)
		return (f4_mul(camera->axis_y, -1.f));
	else if (movement == rt_movement_forward)
		return (f4_mul(camera->axis_z, -1.f));
	else if (movement == rt_movement_backward)
		return (f4_mul(camera->axis_z, 1.f));
	rt_assert(0, "Camera : Unknown movement type");
	return ((RT_F4_API){0., 0., 0., 0.});
}