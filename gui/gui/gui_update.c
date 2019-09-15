#include "gui.h"

void 				gui_update(t_gui *gui)
{
	gui_parser_update(gui->parser);
	gui_camera_show(gui->camera, gui->renderer->data.camera);
	gui_scene_common_update_all(gui->scene->common, gui->renderer->data.scene);
	gui_settings_show(gui->settings, &gui->renderer->data.settings);
}
