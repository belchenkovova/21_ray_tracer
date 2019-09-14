#include "gui_signal_x.h"

void				gui_signal_scene_edit_apply
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;

	gui = (t_gui *)ptr;
	gui_scene_edit_apply(gui->scene->edit, gui->renderer->data.scene);
	gui_scene_common_update_all(gui->scene->common, gui->renderer->data.scene,
		gui->renderer->data.settings.rm_mod);
	gui_control_hide(&gui->scene->edit->control);
	cl_renderer_flag_set(gui->renderer, cl_flag_update_scene);
	cl_renderer_flag_set(gui->renderer, cl_flag_reset_samples);
	gui_queue_push(gui->queue);
}
