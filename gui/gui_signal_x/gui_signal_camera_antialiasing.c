#include "gui_signal_x.h"

gboolean			gui_signal_camera_antialiasing
					(GtkWidget *widget, gboolean state, gpointer ptr)
{
	t_gui			*gui;

	gui = (t_gui *)ptr;
	gui->renderer->data.camera->filter_antialiasing = state;
	cl_renderer_flag_set(gui->renderer, cl_flag_update_camera);
	cl_renderer_flag_set(gui->renderer, cl_flag_reset_samples);
	gui_queue_push(gui->queue);
	return (FALSE);
}