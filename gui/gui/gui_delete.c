#include "gui.h"

void				gui_delete(t_gui **gui)
{
	gui_camera_delete(&(*gui)->camera);
	gui_scene_delete(&(*gui)->object);
	gui_settings_delete(&(*gui)->settings);
	gui_image_delete(&(*gui)->image);
	cl_renderer_delete(&(*gui)->renderer);
	free(*gui);
	*gui = NULL;
}