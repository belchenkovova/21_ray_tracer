#include "gui_signal_x.h"

void 				gui_signal_object_edit_sphere_name
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	t_object		*object;

	gui = (t_gui *)ptr;
	if (gui->scene->edit->current_id == -1)
		return ;
	object = gui->renderer->data.scene->objects +
			 gui->scene->edit->current_id;
	ft_strcpy(object->name, gtk_entry_get_text(GTK_ENTRY(widget)));
	gtk_list_store_set(
		gui->scene->edit->list, &gui->scene->edit->iter,
		scene_edit_object_name, object->name, -1);
	cl_renderer_flag_set(gui->renderer, cl_flag_update_scene);
}

void 				gui_signal_object_edit_sphere_position_x
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	RT_F			value;
	t_object		*object;

	gui = (t_gui *)ptr;
	if (gui->scene->edit->current_id == -1)
		return ;
	value = (RT_F)strtod(gtk_entry_get_text(GTK_ENTRY(widget)), NULL);
	object = gui->renderer->data.scene->objects +
		gui->scene->edit->current_id;
	((t_object_sphere *)object->data)->position.x = value;
	cl_renderer_flag_set(gui->renderer, cl_flag_update_scene);
	cl_renderer_flag_set(gui->renderer, cl_flag_reset_samples);
	cl_renderer_render(gui->renderer);
}

void 				gui_signal_object_edit_sphere_position_y
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	RT_F			value;
	t_object		*object;

	gui = (t_gui *)ptr;
	if (gui->scene->edit->current_id == -1)
		return ;
	value = (RT_F)strtod(gtk_entry_get_text(GTK_ENTRY(widget)), NULL);
	object = gui->renderer->data.scene->objects +
		gui->scene->edit->current_id;
	((t_object_sphere *)object->data)->position.y = value;
	cl_renderer_flag_set(gui->renderer, cl_flag_update_scene);
	cl_renderer_flag_set(gui->renderer, cl_flag_reset_samples);
	cl_renderer_render(gui->renderer);
}

void 				gui_signal_object_edit_sphere_position_z
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	RT_F			value;
	t_object		*object;

	gui = (t_gui *)ptr;
	if (gui->scene->edit->current_id == -1)
		return ;
	value = (RT_F)strtod(gtk_entry_get_text(GTK_ENTRY(widget)), NULL);
	object = gui->renderer->data.scene->objects +
		gui->scene->edit->current_id;
	((t_object_sphere *)object->data)->position.z = value;
	cl_renderer_flag_set(gui->renderer, cl_flag_update_scene);
	cl_renderer_flag_set(gui->renderer, cl_flag_reset_samples);
	cl_renderer_render(gui->renderer);
}

void 				gui_signal_object_edit_sphere_radius
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	RT_F			value;
	t_object		*object;

	gui = (t_gui *)ptr;
	if (gui->scene->edit->current_id == -1)
		return ;
	value = (RT_F)strtod(gtk_entry_get_text(GTK_ENTRY(widget)), NULL);
	object = gui->renderer->data.scene->objects +
		gui->scene->edit->current_id;
	((t_object_sphere *)object->data)->radius = value;
	cl_renderer_flag_set(gui->renderer, cl_flag_update_scene);
	cl_renderer_flag_set(gui->renderer, cl_flag_reset_samples);
	cl_renderer_render(gui->renderer);
}
