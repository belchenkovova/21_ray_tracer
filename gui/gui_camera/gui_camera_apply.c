#include "gui_camera.h"

void 				gui_camera_apply(t_gui_camera *gui,t_camera *camera)
{
	camera->position.x = gui_entry_get_f(gui->position_x);
	camera->position.y = gui_entry_get_f(gui->position_y);
	camera->position.z = gui_entry_get_f(gui->position_z);
	camera->rotation.x = gui_entry_get_f(gui->rotation_x);
	camera->rotation.y = gui_entry_get_f(gui->rotation_y);
	camera->rotation.z = gui_entry_get_f(gui->rotation_z);
	camera->focal_length = gui_entry_get_f(gui->focal_length);
	camera->aperture_size = gui_entry_get_f(gui->aperture_size);
}