#include "camera.h"

RT_F4_API			camera_move
					(t_camera *camera,
					 t_camera_movement direction,
					 RT_F length)
{
	RT_F4_API		step;

	if (direction == rt_movement_left)
		step = f4_mul(camera->axis_x, -1.f);
	else if (direction == rt_movement_right)
		step = f4_mul(camera->axis_x, 1.f);
	else if (direction == rt_movement_up)
		step = f4_mul(camera->axis_y, 1.f);
	else if (direction == rt_movement_down)
		step = f4_mul(camera->axis_y, -1.f);
	else if (direction == rt_movement_forward)
		step = f4_mul(camera->axis_z, -1.f);
	else if (direction == rt_movement_backward)
		step = f4_mul(camera->axis_z, 1.f);
	else
		return ((RT_F4_API){RT_INFINITY, RT_INFINITY, RT_INFINITY, 0});
	step = f4_mul(step, length);
	return (f4_add(camera->position, step));
}