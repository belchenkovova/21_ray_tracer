#ifndef GUI_OBJECT_EDIT_H
# define GUI_OBJECT_EDIT_H

# include "rt_float.h"

# include "gui_object_x.h"
# include "gui_material.h"
# include "scene.h"

# include <gtk/gtk.h>

typedef enum 					s_gui_scene_edit_list
{
	scene_edit_object_id,
	scene_edit_object_name,
	scene_edit_type_icon,
	scene_edit_type_id
}								t_gui_scene_edit_list;

typedef struct 					s_gui_scene_edit
{
	GtkEntry					*name;
	GtkEntry					*type;
	t_gui_object_sphere			sphere;
	t_gui_object_plane			plane;
	t_gui_object_cone			cone;
	t_gui_object_cylinder		cylinder;
	t_gui_material				material;
	GtkStack					*stack;
	GtkBox						*control;
	GtkBox						*info;
	GtkListStore				*list;
	GtkTreeSelection			*selection;
	int 						current_id;
	GtkTreeIter					iter;
	GtkDialog					*remove_dialog;
}								t_gui_scene_edit;

t_gui_scene_edit				*gui_scene_edit_new
								(GtkBuilder *builder);
void 							gui_scene_edit_delete
								(t_gui_scene_edit **object);

void 							gui_scene_edit_set_sphere
								(t_gui_scene_edit *edit, GtkBuilder *builder);
void 							gui_scene_edit_set_plane
								(t_gui_scene_edit *edit, GtkBuilder *builder);
void 							gui_scene_edit_set_cone
								(t_gui_scene_edit *edit, GtkBuilder *builder);
void 							gui_scene_edit_set_cylinder
								(t_gui_scene_edit *edit, GtkBuilder *builder);
void 							gui_scene_edit_set_material
								(t_gui_scene_edit *edit, GtkBuilder *builder);

void							gui_scene_edit_gen_name
								(t_object *object);
void 							gui_scene_edit_update
								(t_gui_scene_edit *edit, t_scene *scene);
void 							gui_scene_edit_show
								(t_gui_scene_edit *edit, t_object *object);
void							gui_scene_edit_apply
								(t_gui_scene_edit *edit, t_object* object);

#endif
