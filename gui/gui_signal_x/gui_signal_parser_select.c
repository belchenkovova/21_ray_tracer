#include "gui_signal_x.h"

void 				gui_signal_parser_select
					(GtkWidget *widget, gpointer ptr)
{
	t_gui			*gui;
	GtkTreeModel	*model;
	GtkTreeIter		iter;
	char 			*name;

	gui = (t_gui *)ptr;
	if (!gtk_tree_selection_get_selected(gui->parser->selection, &model, &iter))
		return ;
	gtk_tree_model_get(model, &iter, 0, &name, -1);
	if (!name)
		return ;
	ft_strcpy(gui->parser->final_path, RT_SOURCE_GUI_SCENES);
	ft_strcat(gui->parser->final_path, "/");
	ft_strcat(gui->parser->final_path, name);
	gtk_widget_set_opacity(GTK_WIDGET(gui->parser->load), 1.);
	gtk_button_set_label(gui->parser->dialog_run, "Choose scene file manually");
}