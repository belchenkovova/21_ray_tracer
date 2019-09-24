#include "gui_signal_x.h"

void 				gui_signal_scene_edit_select
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	GtkTreeModel	*model;
	t_object		*object;

	gui = (t_gui *)ptr;
	if (!gtk_tree_selection_get_selected(gui->scene->edit->selection,
		&model, &gui->scene->edit->iter))
		return ;
	gtk_widget_set_sensitive(gui->scene->edit->remove_button, TRUE);
	gtk_tree_model_get(model, &gui->scene->edit->iter,
		gui_list_column_id, &gui->scene->edit->current_id , -1);
	object = gui->renderer->data.scene->objects + gui->scene->edit->current_id;
	gui_scene_edit_show(gui->scene->edit, object);
	gui_control_hide(&gui->scene->edit->control);
	gui_queue_block(gui->queue);
	scene_select(gui->renderer->data.scene, gui->scene->edit->current_id);
	cl_renderer_flag_set(gui->renderer, cl_flag_update_scene);
	cl_renderer_flag_set(gui->renderer, cl_flag_reset_samples);
	gui_queue_execute_force(gui->queue);
	gui_queue_unblock(gui->queue);
	gtk_widget_set_sensitive(GTK_WIDGET(gui->notebook), 1);
}