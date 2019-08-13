#include "gui.h"

t_gui				*gui_new(int *ac, char ***av)
{
	t_gui			*new;

	gtk_disable_setlocale();
	gtk_init(ac, av);
	new = (t_gui *)malloc(sizeof(t_gui));
	new->builder = gtk_builder_new_from_file(RT_GUI_SOURCE);
	new->window = GTK_WINDOW(RT_GUI_GET(new->builder, "window"));
	new->camera = gui_camera_new(new->builder);
	new->scene = gui_scene_new(new->builder);
	new->settings = gui_settings_new(new->builder);
	new->image = gui_image_new(new->builder);
	new->renderer = cl_renderer_new(new->image);
	gui_camera_show(new->camera, new->renderer->data_host.camera);
	gtk_widget_show(GTK_WIDGET(new->window));
	return (new);
}