#include "gui_signal_x.h"

void				gui_signal_scene_add_material_color
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	t_gui_color		color;

	gui = (t_gui *)ptr;
	if (gui->scene->add->material_color_silent)
		return ;
	gtk_color_button_get_rgba(gui->scene->add->material.color_button, &color);
	gui_entry_set_f(gui->scene->add->material.color_r, color.red);
	gui_entry_set_f(gui->scene->add->material.color_g, color.green);
	gui_entry_set_f(gui->scene->add->material.color_b, color.blue);
}

void				gui_signal_scene_add_material_emission
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	t_gui_color		emission;

	gui = (t_gui *)ptr;
	gtk_color_button_get_rgba(gui->scene->add->material.emission_button,
							  &emission);
	gui_entry_set_f(gui->scene->add->material.emission_r, emission.red);
	gui_entry_set_f(gui->scene->add->material.emission_g, emission.green);
	gui_entry_set_f(gui->scene->add->material.emission_b, emission.blue);
}