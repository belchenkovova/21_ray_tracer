#include "gui_object_base.h"

void					gui_object_base_init
						(t_gui_object_base *gob, GtkOverlay *target)
{
	gtk_container_remove(
		GTK_CONTAINER(gob->offscreen_parent),
		GTK_WIDGET(gob->object));
	gtk_container_add(
		GTK_CONTAINER(target),
		GTK_WIDGET(gob->object));
}