#include "gui_signal_x.h"

void 				gui_signal_settings_reset
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;

	gui = (t_gui *)ptr;
	gui_settings_reset(gui->settings, &gui->renderer->data.settings);
	gtk_widget_set_opacity(GTK_WIDGET(gui->settings->control), 0.);
}