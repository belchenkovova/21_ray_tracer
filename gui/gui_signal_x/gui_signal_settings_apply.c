#include "gui_signal_x.h"

void 				gui_signal_settings_apply
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;

	gui = (t_gui *)ptr;
	gui_settings_apply(gui->settings, &gui->renderer->data.settings);
	gtk_widget_set_opacity(GTK_WIDGET(gui->settings->control), 0.);
	cl_renderer_flag_set(gui->renderer, cl_flag_update_settings);
	cl_renderer_flag_set(gui->renderer, cl_flag_reset_samples);
	cl_renderer_render(gui->renderer);
}